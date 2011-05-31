// GcVSListBox.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcVSListBox.h"

static const int nListId = 1;

// GcVSListBox

IMPLEMENT_DYNAMIC(GcVSListBox, CVSListBox)

GcVSListBox::GcVSListBox(bool bSendMessageToParent) : mSendMessageToParent( bSendMessageToParent )
	,mEnableEdit(true)
{

}

GcVSListBox::~GcVSListBox()
{
}

BEGIN_MESSAGE_MAP(GcVSListBox, CVSListBox)
END_MESSAGE_MAP()

void GcVSListBox::OnSelectionChanged()
{
	SendMessageToParent( WM_NOTIFY, GTMG_VSLISTITEM_SELECTCHANGED, GetSelItem() );
}

BOOL GcVSListBox::OnBeforeRemoveItem(int iItem)
{
	SendMessageToParent( WM_NOTIFY, GTMG_VSLISTITEM_BEFOREREMOVE, iItem );
	return true;
}

void GcVSListBox::OnAfterAddItem(int iItem)
{
	SendMessageToParent( WM_NOTIFY, GTMG_VSLISTITEM_AFTERADD, iItem );
}

void GcVSListBox::OnAfterRenameItem(int iItem)
{
	SendMessageToParent( WM_NOTIFY, GTMG_VSLISTITEM_AFTERRENAME, iItem );
}

void GcVSListBox::OnAfterMoveItemUp(int iItem)
{
	SendMessageToParent( WM_NOTIFY, GTMG_VSLISTITEM_MOVEUP, iItem );
}

void GcVSListBox::OnAfterMoveItemDown(int iItem)
{
	SendMessageToParent( WM_NOTIFY, GTMG_VSLISTITEM_MOVEDOWN, iItem );
}

void GcVSListBox::SetItemText(int iIndex, const CString& strText)
{
	mBeforeEditText = GetItemText( iIndex );
	CVSListBox::SetItemText( iIndex, strText );
}

BOOL GcVSListBox::EditItem(int iIndex)
{
	if( GetEnableEdit() )
		return CVSListBox::EditItem( iIndex );

	return FALSE;
}

void GcVSListBox::RemoveAllItem(bool bSignalChildeClass)
{
	while( GetCount() )
	{
		int index = GetCount() - 1;
		if( bSignalChildeClass )
			RemoveItem( index );
		else
		{
			if (GetSafeHwnd() == NULL || m_pWndList == NULL)
			{
				ASSERT(FALSE);
				return;
			}
			ASSERT_VALID(m_pWndList);
			if (!m_pWndList->DeleteItem(index))
				return;

		}
	}
}
