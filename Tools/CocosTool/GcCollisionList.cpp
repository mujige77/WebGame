#include "StdAfx.h"
#include "CocosTool.h"
#include "GcCollisionList.h"
#include "GcCreateCollisionDlg.h"

GcCollisionList::GcCollisionList(void)
{
	SetEnableEdit( false );
	SetSendMessageToParent( true );
}


GcCollisionList::~GcCollisionList(void)
{
}

void GcCollisionList::ResetData(Gt2DSequence* pSequence)
{
	mpSequence = pSequence;
	if( pSequence == NULL || pSequence->GetSequence() == NULL )
	{
		mpAVData = NULL;
		RemoveAllItem();
		return;
	}
	mpAVData = pSequence->GetSequence()->GetAVData();
	for( gtuint i = 0 ; i < mpAVData->GetCollisionCount() ; i++ )
	{
		Gn2DAVData::CollisionRect& rect = mpAVData->GetCollisionRect( i );
		AddItem( GetMakeName( i, rect.mType ), rect.mType );
	}
}

void GcCollisionList::CreateNewItem()
{
	GcCreateCollisionDlg addDlg;
	INT_PTR ret = addDlg.DoModal();
	if( ret == IDCANCEL ) 
		return;

	int type = addDlg.GetSelectedCollisionType();
	if( mpAVData )
	{		
		mpAVData->AddCollisionRect( type, GnFRect(100, 100, 150, 150) );
		AddItem( GetMakeName( GetCount(), type ), type );
	}
	mpSequence->SetModifed( true );
	SendMediateMessage( GTMG_REDRAW, NULL );
}

BOOL GcCollisionList::RemoveItem(int iIndex)
{
	mpAVData->RemoveAtAndFillAllCollisionRect( (gtuint)iIndex );
	if( GcVSListBox::RemoveItem( iIndex ) == false )
			return FALSE;

	for( int i = iIndex ; i < GetCount() ; i++ )
	{
		CString makeName = GetMakeName( i, GetItemData( i ) );
		SetItemText( i , makeName );
	}
	mpSequence->SetModifed( true );
	SendMediateMessage( GTMG_REDRAW, NULL );
	return TRUE;
}

CString GcCollisionList::GetMakeName(gtuint i, int iType)
{
	GnAssert( iType < Gg2DCollision::COLLISION_MAX );
	GtNumberString collisionName;
	gtstring type = _T("_");
	type += gsCollisionType[iType];
	collisionName.SetNumber( 2, i, NULL, type.c_str() );
	return collisionName.GetString().c_str();
}