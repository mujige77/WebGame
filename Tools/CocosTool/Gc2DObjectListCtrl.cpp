// Gc2DObjectListCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "Gc2DObjectListCtrl.h"

// Gc2DObjectListCtrl

IMPLEMENT_DYNAMIC(Gc2DObjectListCtrl, CMFCListCtrl)

	Gc2DObjectListCtrl::Gc2DObjectListCtrl() : mSelectedItem(-1)
{

}

Gc2DObjectListCtrl::~Gc2DObjectListCtrl()
{
}


BEGIN_MESSAGE_MAP(Gc2DObjectListCtrl, CMFCListCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &Gc2DObjectListCtrl::OnLvnItemchanged)
END_MESSAGE_MAP()

int Gc2DObjectListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	InsertColumn( 0, _T("타입"), LVCFMT_LEFT, 150 );
	SendMessage( LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	EnableMarkSortedColumn();
	return 0;
}

void Gc2DObjectListCtrl::ResetData(Gt2DObject* pObject)
{
	mSelectedItem = - 1;
	mpsCurrentObject = pObject;

	if( GetSafeHwnd() )
		DeleteAllItems();
	if( pObject )
	{
		GnTimeController* controller = pObject->Get2DMeshObjecct()->GetTimeControllers();
		while( controller )
		{
			const gtchar* ctrlName = GetTimeControllerName( controller );
			AddItem( ctrlName );
			controller = controller->GetNext();
		}
	}
}

void Gc2DObjectListCtrl::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	mSelectedItem = pNMLV->iItem;
	if( mSelectedItem == -1 )
		return;
}