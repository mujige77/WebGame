#include "StdAfx.h"
#include "CocosTool.h"
#include "GcActorExtraDataList.h"
#include "GcCreateExtraDataDlg.h"

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
		CString str = GetMakeName( GetCount(), extra->GetType() );
		AddItem( str.GetString(), extra->GetType() );
	}
	mpMeshObject = pMeshObject;
}

void GcActorExtraDataList::CreateNewItem()
{
	GcCreateExtraDataDlg addDlg;
	INT_PTR ret = addDlg.DoModal();
	if( ret == IDCANCEL ) 
		return;

	GnExtraData* extra = NULL;
	int type = addDlg.GetSelectedExtraDataType();
	if( type == GExtraData::EXTRA_EFFECT_POSITION )
	{
		extra = GnNew GnVector2ExtraData();
		mpExtraDatas->Add( extra );		
	}	

	if( extra == NULL )
	{
		GnAssert( false );
		return;
	}
	extra->SetType( type );
	extra->SetID( 0 );

	CString str = GetMakeName( GetCount(), extra->GetType() );
	int sel = AddItem( str.GetString(), extra->GetType() );
	SelectItem( sel );
	OnAfterAddItem( sel );	
	mpGtObject->SetModifed( true );
	SendMediateMessage( GTMG_REDRAW, NULL );
}

BOOL GcActorExtraDataList::RemoveItem(int iIndex)
{
	mpGtObject->SetModifed( true );
	SendMediateMessage( GTMG_REDRAW, NULL );
	return TRUE;
}

CString GcActorExtraDataList::GetMakeName(gtuint i, int iType)
{
	GtNumberString collisionName;
	gtstring type = _T("_");
	type += gsExtraType[iType];
	collisionName.SetNumber( 2, i, NULL, type.c_str() );
	return collisionName.GetString().c_str();
}