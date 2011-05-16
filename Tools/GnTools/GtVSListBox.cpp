// GtVSListBox.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtVSListBox.h"

static const int nListId = 1;

// GtVSListBox

IMPLEMENT_DYNAMIC(GtVSListBox, CVSListBox)

GtVSListBox::GtVSListBox(bool bSendMessageToParent) : mSendMessageToParent( bSendMessageToParent )
{

}

GtVSListBox::~GtVSListBox()
{
}

BEGIN_MESSAGE_MAP(GtVSListBox, CVSListBox)
END_MESSAGE_MAP()

void GtVSListBox::OnSelectionChanged()
{
	SendMessageToParent( WM_NOTIFY, GTMG_VSLISTITEM_SELECTCHANGED, GetSelItem() );
}

BOOL GtVSListBox::OnBeforeRemoveItem(int iItem)
{
	SendMessageToParent( WM_NOTIFY, GTMG_VSLISTITEM_BEFOREREMOVE, iItem );
	return true;
}

void GtVSListBox::OnAfterAddItem(int iItem)
{
	SendMessageToParent( WM_NOTIFY, GTMG_VSLISTITEM_AFTERADD, iItem );
}

void GtVSListBox::OnAfterRenameItem(int iItem)
{
	SendMessageToParent( WM_NOTIFY, GTMG_VSLISTITEM_AFTERRENAME, iItem );
}

void GtVSListBox::OnAfterMoveItemUp(int iItem)
{
	SendMessageToParent( WM_NOTIFY, GTMG_VSLISTITEM_MOVEUP, iItem );
}

void GtVSListBox::OnAfterMoveItemDown(int iItem)
{
	SendMessageToParent( WM_NOTIFY, GTMG_VSLISTITEM_MOVEDOWN, iItem );
}

void GtVSListBox::SetItemText(int iIndex, const CString& strText)
{
	mBeforeEditText = GetItemText( iIndex );
	CVSListBox::SetItemText( iIndex, strText );
}


