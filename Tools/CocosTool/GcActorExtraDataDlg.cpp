// GcActorExtraDataDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcActorExtraDataDlg.h"
#include "afxdialogex.h"


// GcActorExtraDataDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(GcActorExtraDataDlg, CDialogEx)

GcActorExtraDataDlg::GcActorExtraDataDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GcActorExtraDataDlg::IDD, pParent)
{

}

GcActorExtraDataDlg::~GcActorExtraDataDlg()
{
	mExtraDataPropEntity.SetNullProperty();
}

void GcActorExtraDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTACTOREVENT, mActorEventList);
	DDX_Control(pDX, IDC_ACTOREVENT_LOCATION, mActorEventPropLocation);
}

BEGIN_MESSAGE_MAP(GcActorExtraDataDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()



BOOL GcActorExtraDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mActorEventList.SetWindowText( _T("ExtraData List") );
	mActorEventList.SetStandardButtons( AFX_VSLISTBOX_BTN_NEW | AFX_VSLISTBOX_BTN_DELETE );
	mActorEventList.EnableBrowseButton( false );

	CRect rectPropList;
	mActorEventPropLocation.GetClientRect(&rectPropList);
	mActorEventPropLocation.MapWindowPoints(this, &rectPropList);

	mActorEventProp.Create( WS_CHILD | WS_VISIBLE , rectPropList, this, 2 );
	mActorEventProp.EnableHeaderCtrl(FALSE);
	mActorEventProp.EnableDescriptionArea();
	mActorEventProp.SetVSDotNetLook();
	mActorEventProp.MarkModifiedProperties();
	mActorEventProp.AddProperty( mExtraDataPropEntity.GetProperty() );

	mActorEventList.EnableWindow( false );
	EnablePropertyGridCtrl( false );
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void GcActorExtraDataDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (GetSafeHwnd() == NULL)
		return;	

	CRect rect;
	if( mActorEventProp.GetSafeHwnd() )
	{
		mActorEventProp.GetWindowRect( rect );
		ScreenToClient( rect );
		mActorEventProp.SetWindowPos(NULL, rect.left,  rect.top, rect.Size().cx, cy
			, SWP_NOACTIVATE | SWP_NOZORDER);
	}

	if( mActorEventList.GetSafeHwnd() )
	{
		mActorEventList.GetWindowRect( rect );
		ScreenToClient( rect );
		mActorEventList.SetWindowPos(NULL, rect.left,  rect.top, rect.Size().cx, cy
			, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

void GcActorExtraDataDlg::ResetData(GtObject* pObject, Gn2DMeshObject* pMeshObject)
{
	mpObject = pObject;
	mpMeshObject = pMeshObject;
	if( pObject == NULL || pMeshObject == NULL)
	{
		mActorEventList.EnableWindow( false );
		EnablePropertyGridCtrl( false );
	}
	mActorEventList.EnableWindow();
	mActorEventList.ResetData( pObject, pMeshObject );
}

void GcActorExtraDataDlg::EnablePropertyGridCtrl(bool bEnable)
{
	mActorEventProp.EnableWindow( bEnable );
	COLORREF color = RGB(220, 220, 220);
	if( bEnable )
	{
		color = (COLORREF)-1;
		mActorEventProp.SetCustomColors( color, color, color, color, color, color, color );
	}
	else
	{
		mActorEventProp.SetCustomColors( color, color+RGB(20, 20, 20), color+RGB(10, 10, 10)
			, color+RGB(20, 20, 20), color, color+RGB(20, 20, 20), color );
	}
	
	mActorEventProp.RedrawWindow();
}

BOOL GcActorExtraDataDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	GTVSITEMACTIVATE* item = (GTVSITEMACTIVATE*)lParam;
	switch( wParam )
	{
	case GTMG_VSLISTITEM_BEFOREREMOVE:
		{
			if( item->iItem == -1 )
				break;

			EnablePropertyGridCtrl( false );
		}
		break;
	case GTMG_VSLISTITEM_SELECTCHANGED:
		{
			if( item->iItem == -1 )
				break;

			EnablePropertyGridCtrl( true );
			GcExtraDataPropEntity::ThisEntityData data;
			data.mpObject = mpObject;
			data.mpMeshObject = mpMeshObject;
			data.mSelectRectIndex = item->iItem;
			if( item->iItem == -1 )
				break;

			mExtraDataPropEntity.ParseToEntity( &data );
		}
		break;
	case GTMG_VSLISTITEM_AFTERADD:
		{
			if( item->iItem == -1 )
				break;
		}
		break;
	}
	return CDialogEx::OnNotify(wParam, lParam, pResult);
}
