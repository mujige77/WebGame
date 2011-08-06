#include "GnInterfacePCH.h"
#include "GnIListCtrl.h"

GnIListCtrl* GnIListCtrl::CreateListCtrl(GnVector2 cStartUIPosition, gtuint uiNumColumn, gtuint uiNumRow
	, float fColumnGab, float fRowGab)
{
	GnIListCtrl* ctrl = GnNew GnIListCtrl();
	ctrl->Init( cStartUIPosition, uiNumColumn, uiNumRow, fColumnGab, fRowGab );
	return ctrl;
}

GnIListCtrl::~GnIListCtrl()
{
	for( gtuint i = 0; i < mListItems.GetAllocatedSize(); i++ )
	{
		delete mListItems.GetAt( i );
	}
}

void GnIListCtrl::SetSize(gtuint uiNumColumn, gtuint uiNumRow)
{
	mListItems.SetSize( uiNumColumn );
	for( gtuint i = 0; i < mListItems.GetAllocatedSize(); i++ )
	{
		mListItems.SetAt( i, new GnTObjectArray<GnIListCtrlItemPtr>( uiNumRow ) );		
	}
	mNumColumn = uiNumColumn;
	mNumRow = uiNumRow;
}

void GnIListCtrl::AddColumn()
{
	mListItems.Add( new GnTObjectArray<GnIListCtrlItemPtr>( mNumRow ) );
	mNumColumn = mListItems.GetSize();
}

void GnIListCtrl::AddRow()
{
	for( gtuint i = 0; i < mListItems.GetSize(); i++ )
	{
		GnTObjectArray<GnIListCtrlItemPtr>* column = mListItems.GetAt( i );
		column->Add( NULL );
	}
	mNumRow = mListItems.GetAt( 0 )->GetSize();
}

void GnIListCtrl::SetItem(gtuint uiCol, gtuint uiRow, GnIListCtrlItem* pItem)
{
	if( uiCol >= mNumColumn || uiRow >= mNumRow )
		return;
	
	GnTObjectArray<GnIListCtrlItemPtr>* column = mListItems.GetAt( uiCol );
	GnIListCtrlItem* exitsItem = column->GetAt( uiRow );
	if( exitsItem )
		RemoveChild( exitsItem );

	float pointX = mStartUIPosition.x + ( mColumnGab * uiCol );
	float pointY = mStartUIPosition.y + ( mRowGab * uiRow );
	
	pItem->SetCell( uiCol, uiRow );
	SetUIPosition( pItem, pointX, pointY );
	column->SetAt( uiRow, pItem );
	AddChild( pItem );
}

void GnIListCtrl::MoveX(float fMove)
{
	for( gtuint i = 0; i < mListItems.GetSize(); i++ )
	{
		GnTObjectArray<GnIListCtrlItemPtr>* column = mListItems.GetAt( i );
		for ( gtuint j = 0 ; j < column->GetSize(); j++ )
		{
			GnIListCtrlItem* exitsItem = column->GetAt( j );
			if( exitsItem == NULL )
				continue;
			
			GnVector2 uiPoint = exitsItem->GetUIPoint();
			uiPoint.x += fMove;
			mMovePosition.x += fMove;
			SetUIPosition( exitsItem, uiPoint.x, uiPoint.y );
		}
	}
}

void GnIListCtrl::MoveY(float fMove)
{
	for( gtuint i = 0; i < mListItems.GetSize(); i++ )
	{
		GnTObjectArray<GnIListCtrlItemPtr>* column = mListItems.GetAt( i );
		for ( gtuint j = 0 ; j < column->GetSize(); j++ )
		{
			GnIListCtrlItem* exitsItem = column->GetAt( j );
			if( exitsItem == NULL )
				continue;
			
			GnVector2 uiPoint = exitsItem->GetUIPoint();
			uiPoint.y += fMove;
			mMovePosition.y += fMove;
			SetUIPosition( exitsItem, uiPoint.x, uiPoint.y );
			
		}
	}
}

void GnIListCtrl::Init(GnVector2 cStartUIPosition, gtuint uiNumColumn, gtuint uiNumRow
	, float fColumnGab, float fRowGab)
{
	mStartUIPosition = cStartUIPosition;
	mMovePosition = GnVector2( 0.0f, 0.0f );
	mColumnGab = fColumnGab;
	mRowGab = fRowGab;
	SetSize( uiNumColumn, uiNumRow );
}