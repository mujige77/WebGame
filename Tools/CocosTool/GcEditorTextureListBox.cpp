#include "StdAfx.h"
#include "GcEditorTextureListBox.h"

void GcEditorTextureListBox::OnBrowse()
{
	if( mEnableAddItem == false )
		return;

	int nSel = GetSelItem();

	CFileDialog dlg(true, _T("IMG"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		gsTextureFileFilter, GetParent() );
	if( dlg.DoModal() == IDOK )
	{
		if (nSel == GetCount() || nSel == -1) // New item
		{
			SetTextureInfo( dlg.GetPathName(), mDefaultStartTime, mDefaultEndTime );
			nSel = AddItem( dlg.GetPathName() );
			SelectItem( nSel );
			OnAfterAddItem(nSel);
		}
		else
		{
			RenameTexturePath( nSel, dlg.GetPathName() );
			SetItemText( nSel, dlg.GetPathName() );
			OnAfterRenameItem( nSel );
		}
	}
}

void GcEditorTextureListBox::CreateNewItem()
{
	CFileDialog dlg(true, _T("IMG"), NULL
		, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		gsTextureFileFilter, GetParent() );

	if( dlg.DoModal() == IDOK )
	{
		CString strPath;
		POSITION pos = dlg.GetStartPosition();
		while(pos)
		{
			strPath = dlg.GetNextPathName(pos);

			SetTextureInfo( strPath, mDefaultStartTime, mDefaultEndTime );

			int sel = AddItem( strPath );
			SelectItem( sel );
			OnAfterAddItem( sel );
		}
	}
}

BOOL GcEditorTextureListBox::OnBeforeRemoveItem(int iItem)
{
	if( iItem != -1 )
	{
		delete GetTextureInfos()->GetAt( iItem );
		GetTextureInfos()->RemoveAtAndFillAll( iItem );
	}	
	return GcVSListBox::OnBeforeRemoveItem( iItem );
}

void GcEditorTextureListBox::OnAfterAddItem(int iItem)
{
	GcVSListBox::OnAfterAddItem( iItem );
}

void GcEditorTextureListBox::OnAfterMoveItemUp(int iItem)
{
	GetTextureInfos()->ChangePostion( iItem, iItem + 1 );
	GcVSListBox::OnAfterMoveItemUp( iItem );
}

void GcEditorTextureListBox::OnAfterMoveItemDown(int iItem)
{
	GetTextureInfos()->ChangePostion( iItem, iItem - 1 );
	GcVSListBox::OnAfterMoveItemDown( iItem );
}

void GcEditorTextureListBox::OnEndEditLabel(LPCTSTR lpszLabel)
{
	int iSelItem = GetSelItem();
	if (iSelItem < 0)
	{
		ASSERT(FALSE);
		return;
	}

	CString strLabel = (lpszLabel != NULL) ? lpszLabel : _T("");
	if (m_bNewItem)
	{
		RemoveItem(iSelItem);
	}

	m_bNewItem = FALSE;
}

void GcEditorTextureListBox::SetTextureInfo(CString strFilePath, float fSartTime, float fEndTime)
{
	TextureListInfo::TextureInfo* info = new TextureListInfo::TextureInfo();
	info->SetTextureName( strFilePath.GetString() );
	info->SetStartTime( fSartTime );
	info->SetEndTime( fEndTime );
	GetTextureInfos()->Add( info );
}

void GcEditorTextureListBox::RenameTexturePath(int iSelItme, CString strFilePath)
{
	GetTextureInfos()->GetAt(iSelItme)->SetTextureName( strFilePath.GetString() );
}

CString GcEditorTextureListListBox::GetMakeName(int count)
{
	gtchar* format = _T("TextureAni_%0d");
	if( count > 9 )
		format = _T("TextureAni_%0d");

	CString makeName;
	makeName.Format(  format, count );
	return makeName;
}

void GcEditorTextureListListBox::CreateNewItem()
{
	int count = GetCount();
	CString makeName = GetMakeName( count );
	
	TextureListInfo* listInfo = new TextureListInfo();
	listInfo->SetTextureListInfoName( makeName );
	GetTextureLists()->Add( listInfo );

	int nSel = AddItem( makeName );
	OnAfterAddItem(nSel);
	SelectItem( nSel );
}

BOOL GcEditorTextureListListBox::OnBeforeRemoveItem(int iItem)
{
	if( iItem != -1 )
	{
		delete GetTextureLists()->GetAt( iItem );
		GetTextureLists()->RemoveAtAndFillAll( iItem );
	}

	for( int i = iItem - 1 ; i < GetCount() ; i++ )
	{
		CString makeName = GetMakeName( i );
		SetItemText( i , makeName );
	}

	return GcVSListBox::OnBeforeRemoveItem( iItem );
}

void GcEditorTextureListListBox::OnAfterAddItem(int iItem)
{
	GcVSListBox::OnAfterAddItem( iItem );
}