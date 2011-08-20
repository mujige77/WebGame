#include "StdAfx.h"
#include "CocosTool.h"
#include "GcActorExtraDataList.h"
#include "GcCreateExtraDataDlg.h"

int GcActorExtraDataList::msLastSelectNumber = 0;


GcActorExtraDataList::GcActorExtraDataList(void)
{
	SetEnableEdit( false );
	SetSendMessageToParent( true );
}


GcActorExtraDataList::~GcActorExtraDataList(void)
{
}

void GcActorExtraDataList::ResetData(GtObject* pObject, Gn2DMeshObject* pMeshObject)
{
	mpGtObject = pObject;
	if( pMeshObject == NULL )
	{
		RemoveAllItem();
		return;
	}
	mpExtraDatas = pMeshObject->GetExtraDatas();
	for( gtuint i = 0 ; i < mpExtraDatas->GetSize() ; i++ )
	{
		GnExtraData* extra = mpExtraDatas->GetAt( i );
		int type = GetExtraDataType( extra );		
		GnAssert( type != -1 );
		if( type == -1 )
			continue;
		CString str = GetMakeExtraDataTypeName( GetCount(), type );
		AddItem( str.GetString(), type );
	}
	mpMeshObject = pMeshObject;
	if( msLastSelectNumber != -1 && msLastSelectNumber < GetCount() )
		SelectItem( msLastSelectNumber );
	else
		msLastSelectNumber = 0;
}

void GcActorExtraDataList::CreateNewItem()
{
	GcCreateExtraDataDlg addDlg;
	INT_PTR ret = addDlg.DoModal();
	if( ret == IDCANCEL ) 
		return;

	GnExtraData* extra = NULL;
	int type = addDlg.GetSelectedExtraDataType();
	if( type == GExtraData::EXTRA_POSITION_DATA )
		extra = GnNew GnVector2ExtraData();
	else if( type == GExtraData::EXTRA_INT_DATA )
		extra = GnNew GnIntExtraData();

	if( extra == NULL )
	{
		GnAssert( false );
		return;
	}
	extra->SetType( type );
	extra->SetID( 0 );
	mpExtraDatas->Add( extra );

	CString str = GetMakeExtraDataTypeName( GetCount(), type );
	int sel = AddItem( str.GetString(), type );
	SelectItem( sel );
	OnAfterAddItem( sel );	
	mpGtObject->SetModifed( true );
	SendMediateMessage( GTMG_REDRAW, NULL );
}

BOOL GcActorExtraDataList::RemoveItem(int iIndex)
{
	mpExtraDatas->RemoveAtAndFillAll( iIndex );

	if( GcVSListBox::RemoveItem( iIndex ) == false )
		return FALSE;

	for( int i = iIndex ; i < GetCount() ; i++ )
	{
		int type = GetExtraDataType( mpExtraDatas->GetAt( i ) );
		GnAssert( type != -1 );
		CString makeName = GetMakeExtraDataTypeName( i, type );
		SetItemText( i , makeName );
	}

	mpGtObject->SetModifed( true );
	SendMediateMessage( GTMG_REDRAW, NULL );
	return TRUE;
}

void GcActorExtraDataList::OnSelectionChanged()
{
	GcVSListBox::OnSelectionChanged(  );
	msLastSelectNumber = GetSelItem();
}