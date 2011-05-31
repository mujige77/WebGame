// GcTemplateDockable.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcTemplateDockable.h"
#include "GcNewObjectDlg.h"


IMPLEMENT_DYNAMIC(GcTemplateDockable, GcToolBarDockable)

GcTemplateDockable::GcTemplateDockable() : mLastSelectItem(-1)
{
}

GcTemplateDockable::~GcTemplateDockable()
{
}


BEGIN_MESSAGE_MAP(GcTemplateDockable, GcToolBarDockable)
	ON_WM_CREATE()
	ON_COMMAND(ID_BT_DELTEMPLATE, &GcTemplateDockable::OnBtDeltemplate)
	ON_COMMAND(ID_BT_NEWTEMPLATE, &GcTemplateDockable::OnBtNewtemplate)
	ON_COMMAND(ID_BT_OPENTEMPLATE, &GcTemplateDockable::OnBtOpentemplate)
END_MESSAGE_MAP()


// GcTemplateDockable 메시지 처리기입니다.
int GcTemplateDockable::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (GcToolBarDockable::OnCreate(lpCreateStruct) == -1)
		return -1;

	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//afxGlobalData.Is32BitIcons() ? IDB_AFXBARRES_NEW32 : IDB_AFXBARRES_NEW
	mToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_TEMPLATELISTVIEWTOOLBAR);
	mToolBar.LoadToolBar(IDR_TEMPLATELISTVIEWTOOLBAR, 0, 0, TRUE);	
	mToolBar.CleanUpLockedImages();	
	mToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_TEMPLATELISTVIEWTOOLBAR_HC : IDR_TEMPLATELISTVIEWTOOLBAR, 0, 0, TRUE);	
	mToolBar.SetPaneStyle(mToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	mToolBar.SetPaneStyle(mToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	mToolBar.SetOwner(this);

	
	// 모든 명령은 부모 프레임이 아닌 이 컨트롤을 통해 라우팅됩니다.
	mToolBar.SetRouteCommandsViaFrame(FALSE);
	mListCtrl.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_EDITLABELS|LVS_SINGLESEL,
		CRect(10,10,400,200), this, ID_CTRL_TEMPLATELIST);
	mListCtrl.ModifyStyle(0, LVS_SMALLICON);
	mpMainWnd = &mListCtrl;

	SetVisibleCaptionBar(true);
	mToolBar.RemoveButton(4);
	mToolBar.RemoveButton(3);

	gchar filePath[GN_MAX_PATH];
	GtToolSettings::MakeSaveFilePath( "templatelist.lst", NULL, filePath, GN_MAX_PATH );
	LoadTemplateList( filePath );
	return 0;
}

void GcTemplateDockable::OnBtOpentemplate()
{
	gchar filePath[GN_MAX_PATH];
	GtToolSettings::MakeSaveFilePath( "templatelist.lst", NULL, filePath, GN_MAX_PATH );
	SaveTemplateList( filePath );
}

void GcTemplateDockable::OnBtNewtemplate()
{	
	GcNewObjectDlg dlg;
	if( dlg.DoModal() == IDCANCEL )
		return;

	CString itemName = dlg.GetObjectName();
	if( itemName.GetLength() <= 0 )
		return;
	
	GtObject* object = GetActorObject( itemName );
	GnAssert( object );
	object->SetNewItem( true );

	AddItem( itemName, Gt2DActor::OBJECT_TYPE, true );

	GcObjectMessage info;
	info.mpObject = object;
	info.mpSender = this;
	SendMediateMessage( GTMG_NEWOBJECT, &info );
}


void GcTemplateDockable::OnBtDeltemplate()
{
	CList<int> selectList;

	POSITION p = mListCtrl.GetFirstSelectedItemPosition();
	while (p)
	{
		selectList.AddHead( mListCtrl.GetNextSelectedItem(p) );
	}

	while( selectList.IsEmpty() == false )
	{
		mListCtrl.DeleteItem( selectList.GetHead() );
		mTemplateList.RemoveAt( selectList.GetHead() );
		selectList.RemoveHead();
	}
}

void GcTemplateDockable::ReciveNotiyfiMessage(WPARAM wParam, LPARAM lParam)
{
	if( wParam == ID_CTRL_TEMPLATELIST )
	{
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(lParam);
		if( pNMItemActivate == NULL )
			return;
		switch( pNMItemActivate->hdr.code )
		{
		case NM_CLICK:
			{

			}
			break;
		case LVN_ITEMCHANGING:
			{
			}
			break;
		case LVN_ITEMCHANGED:
			{
				if( pNMItemActivate->iItem == -1 || mLastSelectItem == pNMItemActivate->iItem )
					return;

				mLastSelectItem = pNMItemActivate->iItem;
				SelectItem( mLastSelectItem );
				return;
			}
			break;
		case LVN_INSERTITEM:
			{
			}
			break;
		case LVN_DELETEITEM:
			{
				if( mListCtrl.GetItemCount() == 1 )
				{
					mLastSelectItem = -1;
					GcObjectMessage info;
					info.mpObject = NULL;
					info.mpSender = this;
					SendMediateMessage( GTMG_SELECTOBJECT, &info );
				}
				else if( mListCtrl.GetItemCount() )
				{
					GcSequenceMessage sequenceMsg;
					sequenceMsg .mpObject = NULL;
					sequenceMsg .mpSender = this;
					sequenceMsg .mpSequenceInfo = NULL;
					SendMediateMessage( GTMG_SELECTSEQUENCE, &sequenceMsg );
				}				
			}
			break;
		}
	}
}

Gt2DActor* GcTemplateDockable::GetActorObject(CString itemText)
{
	GtConvertString strName = itemText.GetString();
	Gt2DActor* object = (Gt2DActor*)GetObjectFactory()->GetObject( itemText );
	if(  object == NULL )
	{
		object = (Gt2DActor*)GetObjectFactory()->CreateObject( Gt2DActor::OBJECT_TYPE, itemText );
	}
	GnAssert( object );
	object->SetObjectName( strName.GetAciiString() );
	return object;
}

void GcTemplateDockable::AddItem(CString itemName, gint8 iActortype, bool bSelected)
{
	int index = mListCtrl.GetItemCount();
	mListCtrl.InsertItem( index, itemName );
	if( bSelected )
	{
		mListCtrl.SetItemState( index, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING
			, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
	}
	mListCtrl.RedrawWindow();
	mListCtrl.RedrawItems( 0, mListCtrl.GetItemCount() );

	TemplateListData listData( itemName.GetString(), iActortype );
	mTemplateList.Add( listData );
}


void GcTemplateDockable::SaveTemplateList(const gchar* filePath)
{
	GnStream gnStream;

	if( gnStream.Save( filePath ) == false )
		return;

	guint32 count = mTemplateList.GetSize();
	gnStream.SaveStream( count );

	for( gtuint i = 0 ; i < count ; i++ )
	{
		TemplateListData listData = mTemplateList.GetAt( i );		
		gnStream.SaveStream( listData.mObjectType );
		const gtchar* objectName = listData.mObjectName.GetString();
		gnStream.SaveStream( objectName );
	}

	gnStream.Close();
}

void GcTemplateDockable::LoadTemplateList(const gchar* filePath)
{
	GnStream gnStream;
	if( gnStream.Load( filePath ) == false )
		return;

	guint32 count = 0;
	gnStream.LoadStream( count );

	for( gtuint i = 0 ; i < count ; i++ )
	{
		gint8 type;
		gnStream.LoadStream( type );
		gushort lenName = 0;
		gnStream.LoadStream( lenName );
		gtchar objectName[256] = { 0, };
		GnAssert( 256 > lenName );
		gnStream.LoadStreams( (gchar*)objectName, sizeof(gtchar) * lenName );

		AddItem( objectName, type );
	}

	gnStream.Close();
}

void GcTemplateDockable::OnSaveObjectstate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	gchar filePath[GN_MAX_PATH];
	GtToolSettings::MakeSaveFilePath( "templatelist.lst", NULL, filePath, GN_MAX_PATH );
	SaveTemplateList( filePath );
}

void GcTemplateDockable::SelectItem(int iIndex)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	if( mpsCurrentObject )
	{
		switch( mpsCurrentObject->GetType() )
		{
		case Gt2DActor::OBJECT_TYPE:
			{
				Gt2DActor* object = (Gt2DActor*)((GtObject*)mpsCurrentObject);
				object->GetActor()->StopAnimation();
				SendMediateMessage( GTMG_REDRAW, NULL );
				GnLayer* state = GetSceneManager()->GetMainGameLayer();
				state->RemoveChild( object->GetActor()->GetRootNode() );
			}
			
		}
	}
	CString itemText = mListCtrl.GetItemText( iIndex, 0 );
	Gt2DActor* object = GetActorObject(itemText);
	if( object == NULL )
		return;

	mpsCurrentObject = object;
	if( object->IsNewItem() == false )
	{
		if( object->LoadData() == false )
			GnVerify( object->CreateData() );
	}
	else
	{
		GnVerify( object->CreateData() );
	}
	object->GetRootNode()->GetMesh()->setPosition( ccp( 0, 0) );
	GnLayer* state = GetSceneManager()->GetMainGameLayer();
	state->AddChild( object->GetRootNode(), 102 );

	//GnActorTool* actorTool = object->GetActorTool();
	//GnTPrimitiveArray<GnActorTool::SequenceInfo*> infos;
	//actorTool->GetSequenceInfos( infos );
	//if( infos.GetSize() )
	//{
	//	GnActorTool::SequenceInfo* info = infos.GetAt( 0 );
	//	object->GetActor()->SetTargetAnimation( info->GetSequenceID() );
	//}

	GcObjectMessage info;
	info.mpObject = object;
	info.mpSender = this;
	SendMediateMessage( GTMG_SELECTOBJECT, &info );



	//CCSize s = CCDirector::sharedDirector()->getWinSize();
 //   
 //   CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("F:\\떡열\\타조_M\\02 걷기\\1.png");
	//CCTexture2D *texture1 = CCTextureCache::sharedTextureCache()->addImage("F:\\떡열\\타조_M\\02 걷기\\2.png");
	//CCTexture2D *texture2 = CCTextureCache::sharedTextureCache()->addImage("F:\\떡열\\타조_M\\02 걷기\\3.png");
	//CCTexture2D *texture3 = CCTextureCache::sharedTextureCache()->addImage("F:\\떡열\\타조_M\\02 걷기\\4.png");
 //   
 //   // manually add frames to the frame cache
 //   CCSpriteFrame *frame0 = CCSpriteFrame::frameWithTexture(texture,
	//	CCRectMake(0,0, texture->getContentSize().width, texture->getContentSize().height ));
	//CCSpriteFrame *frame1 = CCSpriteFrame::frameWithTexture(texture1,
	//	CCRectMake(0,0, texture1->getContentSize().width, texture1->getContentSize().height ));
	//CCSpriteFrame *frame2 = CCSpriteFrame::frameWithTexture(texture2,
	//	CCRectMake(0,0, texture2->getContentSize().width, texture2->getContentSize().height ));
	//CCSpriteFrame *frame3 = CCSpriteFrame::frameWithTexture(texture3,
	//	CCRectMake(0,0, texture3->getContentSize().width, texture3->getContentSize().height ));
 //   //
 //   // Animation using Sprite BatchNode
 //   //
 //   CCSprite* sprite = new CCSprite;//CCSprite::spriteWithSpriteFrame(frame0);
 //   sprite->setPosition( ccp( s.width/2-80, s.height/2) );
 //   state->addChild(sprite);
 //           
 //   CCMutableArray<CCSpriteFrame*> *animFrames = new CCMutableArray<CCSpriteFrame*>(4);
 //   animFrames->addObject(frame0);
 //   animFrames->addObject(frame1);
 //   animFrames->addObject(frame2);
 //   animFrames->addObject(frame3);
 //           
 //   CCAnimation *animation = CCAnimation::animationWithFrames(animFrames, 0.2f);
 //   CCAnimate *animate = CCAnimate::actionWithAnimation(animation, false);
 //   CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions( animate,/*
 //                      CCFlipX::actionWithFlipX(true),
 //                      animate->copy()->autorelease(),
 //                      CCFlipX::actionWithFlipX(false),*/
 //                      NULL) );
	//CCAction*  action2 = CCRepeatForever::actionWithAction(seq);
	////sprite->setAnchorPoint( CCPointMake(1,1) );
 //   sprite->runAction( action2 );
	////sprite->runAction( CCMoveTo::actionWithDuration(1, CCPointMake(100, 100) ) );
 //   animFrames->release();    // win32 : memory leak    2010-0415
}