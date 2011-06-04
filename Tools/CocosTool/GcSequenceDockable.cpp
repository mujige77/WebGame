// GcSequenceDockable.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcSequenceDockable.h"
#include "GtEditorPropSheetDlg.h"
#include "GtEditorPropSheet.h"
#include "GcTextureAnimationPropEntity.h"
#include "Gc2DCollisionBoxPropEntity.h"
GcSequenceDockable::GcSequenceDockable() : mpEntities(NULL)
{

}

GcSequenceDockable::~GcSequenceDockable()
{
	if( mpEntities )
		delete mpEntities;
}


BEGIN_MESSAGE_MAP(GcSequenceDockable, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_BT_OPENTEMPLATE, &GcSequenceDockable::OnBtSavetemplate)
	ON_COMMAND(ID_BT_NEWTEMPLATE, &GcSequenceDockable::OnBtNewtemplate)	
	ON_COMMAND(ID_BT_DELTEMPLATE, &GcSequenceDockable::OnBtDeltemplate)
END_MESSAGE_MAP()



// GcSequenceDockable 메시지 처리기입니다.
int GcSequenceDockable::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (GcToolBarDockable::OnCreate(lpCreateStruct) == -1)
		return -1;


	CRect rectDummy;
	rectDummy.SetRectEmpty();
	DWORD dwViewStyle;	

	dwViewStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT;
	rectDummy.right = 50;
	rectDummy.bottom = 200;
	if ( !mSequenceListCtrl.Create( dwViewStyle, rectDummy, this, 2 ) )
	{
		TRACE0("파일 뷰를 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	if( !m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 3))
	{
		TRACE0("속성 표를 만들지 못했습니다. \n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	mpEntities = new GcCollectionEntities(&m_wndPropList);

	mToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_TEMPLATELISTVIEWTOOLBAR);
	mToolBar.LoadToolBar(IDR_TEMPLATELISTVIEWTOOLBAR, 0, 0, TRUE /* 잠금 */);	
	mToolBar.CleanUpLockedImages();
	mToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_TEMPLATELISTVIEWTOOLBAR_HC : IDR_TEMPLATELISTVIEWTOOLBAR, 0, 0, TRUE /* 잠금 */);

	mToolBar.SetPaneStyle(mToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	mToolBar.SetPaneStyle(mToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	mToolBar.SetOwner(this);
	// 모든 명령은 부모 프레임이 아닌 이 컨트롤을 통해 라우팅됩니다.
	mToolBar.SetRouteCommandsViaFrame(FALSE);
	

	mToolBar.RemoveButton(4);
	mToolBar.RemoveButton(3);

	AdjustLayout();

	AttachNeedMessage( GTMG_SELECTOBJECT );
	AttachNeedMessage( GTMG_SELECTSEQUENCE );
	AttachNeedMessage( GTMG_DESTORY );
	return 0;
}


void GcSequenceDockable::OnSize(UINT nType, int cx, int cy)
{
	GcToolBarDockable::OnSize(nType, cx, cy);
	AdjustLayout();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void GcSequenceDockable::OnSetFocus(CWnd* pOldWnd)
{
	GcToolBarDockable::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void GcSequenceDockable::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
		return;

	CRect rectClient, rectDlg;
	GetClientRect(rectClient);
	mSequenceListCtrl.GetWindowRect(&rectDlg);
	
	int cyTlb = mToolBar.CalcFixedLayout(FALSE, TRUE).cy;
	int cyDlg =  rectDlg.Size().cy;	

	m_wndPropList.SetDescriptionRows(5);	
	mToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	mSequenceListCtrl.SetWindowPos(NULL, rectClient.left, rectClient.top + cyTlb , rectClient.Width(), cyDlg, SWP_NOACTIVATE|  SWP_NOZORDER);	
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyTlb + cyDlg, rectClient.Width(), rectClient.Height() -(cyTlb+cyDlg), SWP_NOACTIVATE | SWP_NOZORDER);
}

void GcSequenceDockable::ReceiveMediateMessage(gtuint messageIndex
	, GcMediateObjectMessage* pMessage)
{
	switch( messageIndex )
	{
	case GTMG_DESTORY:
		mpsCurrentObject = NULL;
		mSequenceListCtrl.ResetData( NULL );
		break;
	case GTMG_SELECTOBJECT:
		{
			ChangeProperty( pMessage );
		}
		break;
	case GTMG_SELECTSEQUENCE:
		{
			ChangeSequence( pMessage );
		}
		break;
	}
}

void GcSequenceDockable::ChangeProperty(GcMediateObjectMessage* pMessage)
{
	mpEntities->DetachAllEntity();

	GcObjectMessage* objectMessage = (GcObjectMessage*)pMessage;
	mpsCurrentObject = (Gt2DActor*)objectMessage->mpObject;
	if( mpsCurrentObject && mpsCurrentObject->GetType() != Gt2DActor::OBJECT_TYPE )
		return;

	mSequenceListCtrl.ResetData( mpsCurrentObject );	
}

void GcSequenceDockable::ChangeSequence(GcMediateObjectMessage* pMessage)
{
	if( mpsCurrentObject )
		mpsCurrentObject->SetModifySequence( NULL );

	mpEntities->DetachAllEntity();
	GcSequenceMessage* objectInfo = (GcSequenceMessage*)pMessage;
	GnActorTool::SequenceInfo* sequenceInfo = objectInfo->mpSequenceInfo;
	if( sequenceInfo == NULL )
		return;
	
	Gt2DSequence* gtSequence = NULL;
	Gn2DSequence* gnSequence = NULL;
	if( mpsCurrentObject->GetGtSequence( sequenceInfo->GetSequenceID(), gtSequence ) == false )
	{
		gtSequence = GtObjectNew<Gt2DSequence>::Create();		
		if( mpsCurrentObject->GetActor()->GetSequence( sequenceInfo->GetSequenceID(), gnSequence )
			== false )
		{
			GnObjectStream objectStream;
			mpsCurrentObject->GetActor()->AddSequence( sequenceInfo, objectStream, false );
			mpsCurrentObject->GetActor()->GetSequence( sequenceInfo->GetSequenceID(), gnSequence );
		}
		GnAssert( gnSequence );
		gtSequence->SetSequence( gnSequence );
		gtSequence->SetFileName( sequenceInfo->GetFileName() );
		mpsCurrentObject->AddGtSequence( sequenceInfo->GetSequenceID(), gtSequence );
	}
	else
		gnSequence = gtSequence->GetSequence();
	
	if( gnSequence == NULL )
		return;

	mpsCurrentObject->SetModifySequence( gtSequence );

	//Gc2DCollisionBoxPropEntity* collisionProp = GtObjectNew<Gc2DCollisionBoxPropEntity>::Create();
	//Gc2DCollisionBoxPropEntity::ThisEntityData entityEata;
	//entityEata.mpsObject = mpsCurrentObject;
	//entityEata.mpsSequenceObjet = gtSequence;
	//collisionProp->ParseToEntity( &entityEata );
	//mpEntities->AttachEntity( collisionProp );

	for( gtuint i = 0 ; i <  gnSequence->GetTextureAnis().GetSize() ; i++ )
	{
		GcTextureAnimationPropEntity::EntityDataTextureAni data;		
		data.mpObject = mpsCurrentObject;
		data.mIndex = i;
		data.mpAni = gnSequence->GetTextureAnis().GetAt( i );
		GcTextureAnimationPropEntity* textureProp = GtObjectNew<GcTextureAnimationPropEntity>::Create();
		textureProp->ParseToEntity( &data );
		mpEntities->AttachEntity( textureProp );
	}
}

void GcSequenceDockable::OnBtSavetemplate()
{
	
}

void GcSequenceDockable::OnBtNewtemplate()
{
	if( mpsCurrentObject == NULL )
		return;

	UpdateData();

	GtEditorPropSheetDlg* editorSheetDlg = new GtEditorPropSheetDlg(this);	
	GtEditorPropSheet* sheet = editorSheetDlg->GetEditorSheet();

	Gt2DSequence* sequence = GtObjectNew<Gt2DSequence>::Create();
	Gn2DSequence* gnSequence = GtObjectNew<Gn2DSequence>::Create();
	sequence->SetSequence( gnSequence );
	sequence->SetModifed( true );
	sheet->SetObject( mpsCurrentObject, sequence );
	sheet->SetModifyMode( 0 );
	INT_PTR ret = editorSheetDlg->DoModal();
	if(  ret == IDOK )
	{
		GnVector2 max;
		for( gtuint i = 0 ; i < gnSequence->GetTextureAnis().GetSize() ; i++ )
		{
			Gn2DTextureAni* ani = gnSequence->GetTextureAnis().GetAt( i );
			ani->CreateData();
			GnVector2 tempMax = GetMaxSize( gnSequence->GetTextureAnis().GetAt( i ) );
			max.x = GnMax( max.x, tempMax.x );
			max.y = GnMax( max.y, tempMax.y );
		}
		Gn2DAVData* avData = GtObjectNew<Gn2DAVData>::Create();
		
		avData->AddCollisionRect( 0, GnIRect( 0, 0, (int)max.x, (int)max.y ) );
		gnSequence->SetAVData( avData );

		mpsCurrentObject->GetActor()->ChangeSequence( sequence->GetSequence()->GetID()
			, sequence->GetSequence() );
		mpsCurrentObject->AddGtSequence( sequence->GetSequence()->GetID(), sequence );

		mSequenceListCtrl.AddSequence( sequence->GetSequence()->GetID()
			, sequence->GetObjectName(), sequence->GetFileName().GetAciiString(), true );
	}
	else if( ret == IDCANCEL )
	{
		GtObjectNew<Gn2DSequence>::Delete( gnSequence );
		GtObjectNew<Gt2DSequence>::Delete( sequence );		
	}
	delete editorSheetDlg;
}

void GcSequenceDockable::OnBtDeltemplate()
{
	mSequenceListCtrl.RemoveCurrentSequence();
}