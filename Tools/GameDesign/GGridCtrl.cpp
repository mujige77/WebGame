#include "StdAfx.h"
#include "GGridCtrl.h"

BEGIN_MESSAGE_MAP(GGridCtrl, CGridCtrl)
	//{{AFX_MSG_MAP(CGridCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

GGridCtrl::GGridCtrl(void)
{
}


GGridCtrl::~GGridCtrl(void)
{
}


BOOL GGridCtrl::Create(const RECT& rect, CWnd* parent, UINT nID, DWORD dwStyle )
{	
	RECT rc;
	parent->GetClientRect( &rc );
	rc.left += 3; rc.top += 15; rc.right -= 3; rc.bottom -= 3;
	if( !CGridCtrl::Create( rc, parent, nID, dwStyle ) )	
		return FALSE;

	EnableDragAndDrop(TRUE);
	SetFixedColumnSelection(TRUE);
	SetFixedRowSelection(TRUE);
	EnableColumnHide();
	AutoSize();
	SetCompareFunction(CGridCtrl::pfnCellNumericCompare);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);		
	EnableDragRowMode( FALSE );
	EnableDragAndDrop( FALSE );	
	SetSingleRowSelection(TRUE);
	SetFixedRowSelection( TRUE );
	SetFixedColumnSelection( TRUE );
	SetRowHeight(0,20);
	return TRUE;
}
