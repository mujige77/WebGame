#include "StdAfx.h"
#include "CocosTool.h"
#include "GcAnimationKeyList.h"
#include "GnTegIDKey.h"
#include "CreateAnimationKeyDlg.h"
#include "GtAniKeyHelper.h"

GcAnimationKeyList::GcAnimationKeyList(void)
{
	SetEnableEdit( false );
	SetSendMessageToParent( true );
}


GcAnimationKeyList::~GcAnimationKeyList(void)
{
}

void GcAnimationKeyList::ResetData(Gt2DSequence* pSequence)
{
	mpsSequence = pSequence;
	if( pSequence == NULL )
		return;

	mpAniKeyManager = pSequence->GetSequence()->GetAnimationKeyManager();
	GnTPrimitiveArray<GnAnimationKeyManager::AniKey>* aniKeys = mpAniKeyManager->GetAnimationKeys();
	for( gtuint i = 0 ; i < aniKeys->GetSize() ; i++ )
	{
		GnAnimationKeyManager::AniKey anikey = aniKeys->GetAt( i );
		for( guint32 i = 0 ; i < anikey.mNumKey ; i++ )
		{
			CString str = GetMakeName( GetCount(), anikey.mKeyType );
			AddItem( str.GetString(), anikey.mKeyType );
		}
	}
}

gint GcAnimationKeyList::GetAniKeyIndex(int iItemIndex)
{
	gint retIndex = -1;
	for( int i = 0 ; i < GetCount() ; i++ )
	{
		if( GetItemData( iItemIndex ) == GetItemData( i ) )
			++retIndex;
		if( iItemIndex == i )
			break;
	}
	return retIndex;
}

void GcAnimationKeyList::CreateNewItem()
{
	CreateAnimationKeyDlg addAniDlg;

	INT_PTR ret = addAniDlg.DoModal();
	if( ret == IDCANCEL ) 
		return;

	switch( addAniDlg.GetSelectType() )
	{
	case GnAnimationKey::TEGIDKEY:
		CreateTegIDKey();
		break;
	default:
		return;
	}
	mpsSequence->SetModifed( true );
};	

void GcAnimationKeyList::CreateTegIDKey()
{
	CString str = GetMakeName(GetCount(), GnAnimationKey::TEGIDKEY);
	int sel = AddItem( str.GetString(), GnAnimationKey::TEGIDKEY );
	SelectItem( sel );
	OnAfterAddItem( sel );

	AddTegIDKey( GnAnimationKey::TEGIDKEY, mpAniKeyManager, GetCurrentTime(), 0 );
}

BOOL GcAnimationKeyList::RemoveItem(int iIndex)
{
	gint aniKeyIndex = GetAniKeyIndex( iIndex );
	if( aniKeyIndex != -1 )
	{
		RemoveTegIDKey( (guint)GetItemData( iIndex ), mpAniKeyManager, (guint)aniKeyIndex );
	}
	if( GcVSListBox::RemoveItem( iIndex ) == false )
		return FALSE;

	for( int i = iIndex ; i < GetCount() ; i++ )
	{
		CString makeName = GetMakeName( i, GetItemData( i ) );
		SetItemText( i , makeName );
	}
	mpsSequence->SetModifed( true );
	return TRUE;
}

CString GcAnimationKeyList::GetMakeName(int iIndex, guint aniKeyType)
{
	GnAssert( aniKeyType < GnAnimationKey::MAX_KEYTYPE );
	
	CString names[GnAnimationKey::MAX_KEYTYPE] = {
		_T("Tag Index")
	};

	GtNumberString numString;
	numString.SetNumber( 2, iIndex, names[aniKeyType].GetString(), NULL );
	return numString.GetString().c_str();
}