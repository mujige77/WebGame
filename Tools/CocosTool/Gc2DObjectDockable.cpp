// Gc2DObjectDockable.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "Gc2DObjectDockable.h"
#include "GtEditorPropSheetDlg.h"
#include "GtEditorPropSheet.h"
#include "GcTextureAnimationPropEntity.h"
#include "Gc2DCollisionBoxPropEntity.h"
Gc2DObjectDockable::Gc2DObjectDockable() : mpEntities(NULL)
{

}

Gc2DObjectDockable::~Gc2DObjectDockable()
{
	if( mpEntities )
		delete mpEntities;
}

BEGIN_MESSAGE_MAP(Gc2DObjectDockable, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_BT_OPENTEMPLATE, &Gc2DObjectDockable::OnBtSavetemplate)
	ON_COMMAND(ID_BT_NEWTEMPLATE, &Gc2DObjectDockable::OnBtNewtemplate)	
	ON_COMMAND(ID_BT_DELTEMPLATE, &Gc2DObjectDockable::OnBtDeltemplate)
END_MESSAGE_MAP()



// Gc2DObjectDockable 메시지 처리기입니다.
int Gc2DObjectDockable::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (GcToolBarDockable::OnCreate(lpCreateStruct) == -1)
		return -1;


	CRect rectDummy;
	rectDummy.SetRectEmpty();
	DWORD dwViewStyle;	

	dwViewStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT;
	rectDummy.right = 50;
	rectDummy.bottom = 150;
	if ( !mListCtrl.Create( dwViewStyle, rectDummy, this, 2 ) )
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

	AttachNeedMessage( GTMG_SELECT2DOBJECT );
	AttachNeedMessage( GTMG_DESTORY );
	return 0;
}


void Gc2DObjectDockable::OnSize(UINT nType, int cx, int cy)
{
	GcToolBarDockable::OnSize(nType, cx, cy);
	AdjustLayout();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void Gc2DObjectDockable::OnSetFocus(CWnd* pOldWnd)
{
	GcToolBarDockable::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void Gc2DObjectDockable::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
		return;

	CRect rectClient, rectDlg;
	GetClientRect(rectClient);
	mListCtrl.GetWindowRect(&rectDlg);

	int cyTlb = mToolBar.CalcFixedLayout(FALSE, TRUE).cy;
	int cyDlg =  rectDlg.Size().cy;	

	m_wndPropList.SetDescriptionRows(5);	
	mToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb
		, SWP_NOACTIVATE | SWP_NOZORDER);
	mListCtrl.SetWindowPos(NULL, rectClient.left, rectClient.top + cyTlb , rectClient.Width(), cyDlg
		, SWP_NOACTIVATE|  SWP_NOZORDER);	
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyTlb + cyDlg, rectClient.Width()
		, rectClient.Height() -(cyTlb+cyDlg), SWP_NOACTIVATE | SWP_NOZORDER);
}

void Gc2DObjectDockable::ReceiveMediateMessage(gtuint messageIndex
	, GcMediateObjectMessage* pMessage)
{
	switch( messageIndex )
	{
	case GTMG_DESTORY:
		mpsCurrentObject = NULL;
		mListCtrl.ResetData( NULL );
		break;
	case GTMG_SELECT2DOBJECT:
		{
			ChangeProperty( pMessage );
		}
		break;
	}
}

void Gc2DObjectDockable::ChangeProperty(GcMediateObjectMessage* pMessage)
{
	mpEntities->DetachAllEntity();

	GcObjectMessage* objectMessage = (GcObjectMessage*)pMessage;
	mpsCurrentObject = (Gt2DObject*)objectMessage->mpObject;
	if( mpsCurrentObject && mpsCurrentObject->GetType() != Gt2DObject::OBJECT_TYPE )
		return;

	mListCtrl.ResetData( mpsCurrentObject );
	SendMediateMessage( GTMG_REDRAW, NULL );
}

void Gc2DObjectDockable::OnBtSavetemplate()
{
	mpsCurrentObject->SetModifed( true );
}

void Gc2DObjectDockable::OnBtNewtemplate()
{
	if( mpsCurrentObject == NULL )
		return;

	UpdateData();

	GtEditorPropSheetDlg* editorSheetDlg = new GtEditorPropSheetDlg(this);	
	GtEditorPropSheet* sheet = editorSheetDlg->GetEditorSheet();
	sheet->SetModifyMode( mpsCurrentObject->GetType() );
	INT_PTR ret = editorSheetDlg->DoModal();
	if(  ret == IDOK )
	{
		GcEditorTexture* texturepage = sheet->GetTexturepage();
		AddTextureController( texturepage );
		SendMediateMessage( GTMG_REDRAW, NULL );
		mpsCurrentObject->SetModifed( true );
	}
	else if( ret == IDCANCEL )
	{	
	}
	delete editorSheetDlg;
}

void Gc2DObjectDockable::OnBtDeltemplate()
{
}

void Gc2DObjectDockable::AddTextureController(GcEditorTexture* pTexturepage)
{
	gtuint size = pTexturepage->GetTextureLists()->GetSize();
	for( gtuint i = 0 ; i < size ; i++ )
	{
		TextureListInfo* listInfo = pTexturepage->GetTextureLists()->GetAt( i );
		gtuint numTexture = listInfo->GetTextures()->GetSize();
		Gn2DTextureAniCtlr* aniCtrl = GtObjectNew<Gn2DTextureAniCtlr>::Create();
		for( gtuint j = 0 ; j < numTexture ; j++ )
		{
			TextureListInfo::TextureInfo* textureInfo = listInfo->GetTextures()->GetAt( j );			
			Gn2DTextureAniCtlr::TextureAniInfo* aniInfo 
				=  GtObjectNew<Gn2DTextureAniCtlr::TextureAniInfo>::Create();

			GtConvertString convName = textureInfo->GetTextureName().GetString();
			aniInfo->SetTextureName( convName.GetAciiString() );
			aniInfo->SetStartTime( textureInfo->GetStartTime() );
			aniInfo->SetEndTime( textureInfo->GetEndTime() );
			aniCtrl->AddAniInfo( aniInfo );
		}
		GnVerify( aniCtrl->CreateData() );
		aniCtrl->SetIsMeshStreamble( true );
		aniCtrl->SetTargetObject( mpsCurrentObject->Get2DMeshObjecct() );
		mListCtrl.ResetData( mpsCurrentObject );
		//mpsCurrentObject->Get2DMeshObjecct()->SetTimeController( aniCtrl );
	}
}