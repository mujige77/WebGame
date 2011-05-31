// GcSequenceCollisionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcSequenceCollisionDlg.h"
#include "afxdialogex.h"


// GcSequenceCollisionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(GcSequenceCollisionDlg, CDialogEx)

GcSequenceCollisionDlg::GcSequenceCollisionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GcSequenceCollisionDlg::IDD, pParent)
{

}

GcSequenceCollisionDlg::~GcSequenceCollisionDlg()
{
	mCollisionPropEntity.SetNullProperty();
}

void GcSequenceCollisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTACOLLISION, mCollisionList);
	DDX_Control(pDX, IDC_COLLISION_LOCATION, mCollisionPropLocaton);
}


BEGIN_MESSAGE_MAP(GcSequenceCollisionDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL GcSequenceCollisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mCollisionList.SetWindowText( _T("Collision List") );
	mCollisionList.SetStandardButtons( AFX_VSLISTBOX_BTN_NEW | AFX_VSLISTBOX_BTN_DELETE );
	mCollisionList.EnableBrowseButton( false );

	CRect rectPropList;
	mCollisionPropLocaton.GetClientRect(&rectPropList);
	mCollisionPropLocaton.MapWindowPoints(this, &rectPropList);

	mCollisionProp.Create( WS_CHILD | WS_VISIBLE , rectPropList, this, 2 );
	mCollisionProp.EnableHeaderCtrl(FALSE);
	mCollisionProp.EnableDescriptionArea();
	mCollisionProp.SetVSDotNetLook();
	mCollisionProp.MarkModifiedProperties();
	mCollisionProp.AddProperty( mCollisionPropEntity.GetProperty() );
	mCollisionProp.AddProperty( mCollisionPropEntity.GetProperty2() );

	return TRUE;
}

BOOL GcSequenceCollisionDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	GTVSITEMACTIVATE* item = (GTVSITEMACTIVATE*)lParam;
	switch( wParam )
	{
	case GTMG_VSLISTITEM_SELECTCHANGED:
		{
			if( item->iItem == -1 )
				break;

			mCollisionPropEntity.GetProperty()->Show( true );
			
			Gc2DCollisionBoxPropEntity::ThisEntityData entityEata;
			entityEata.mpObject = mpActor;
			entityEata.mpSequenceObject = mpSequence;
			entityEata.mSelectRectIndex = item->iItem;
			mCollisionPropEntity.ParseToEntity( &entityEata );
			mCollisionProp.ExpandAll(TRUE);
		}
		break;
	}
	return CDialogEx::OnNotify(wParam, lParam, pResult);
}

void GcSequenceCollisionDlg::ReceiveMediateMessage(gtuint messageIndex, GcMediateObjectMessage* pMessage)
{
	//Gc2DCollisionBoxPropEntity* collisionProp = GtObjectNew<Gc2DCollisionBoxPropEntity>::Create();
	//Gc2DCollisionBoxPropEntity::ThisEntityData entityEata;
	//entityEata.mpsObject = mpsCurrentObject;
	//entityEata.mpsSequenceObjet = gtSequence;
	//collisionProp->ParseToEntity( &entityEata );
	//mpEntities->AttachEntity( collisionProp );
}

void GcSequenceCollisionDlg::ResetData(Gt2DActor* pActor, Gt2DSequence* pSequence)
{
	mpActor = pActor;
	mpSequence = pSequence;
	if( mCollisionProp.GetSafeHwnd() )
		mCollisionPropEntity.GetProperty()->Show( false, true );
	if( mCollisionList.GetSafeHwnd() )
		mCollisionList.ResetData( pSequence );
}