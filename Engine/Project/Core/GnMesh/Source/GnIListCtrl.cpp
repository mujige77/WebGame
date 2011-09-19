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
	mColumnSize = uiNumColumn;
	mRowSize = uiNumRow;
}

void GnIListCtrl::AddColumn()
{
	mListItems.Add( new GnTObjectArray<GnIListCtrlItemPtr>( mRowSize ) );
	mColumnSize = mListItems.GetSize();
}

void GnIListCtrl::AddRow()
{
	for( gtuint i = 0; i < mListItems.GetSize(); i++ )
	{
		GnTObjectArray<GnIListCtrlItemPtr>* column = mListItems.GetAt( i );
		column->Add( NULL );
	}
	mRowSize = mListItems.GetAt( 0 )->GetSize();
}

void GnIListCtrl::SetItem(gtuint uiCol, gtuint uiRow, GnIListCtrlItem* pItem)
{
	if( uiCol >= mColumnSize || uiRow >= mRowSize )
		return;
	
	GnTObjectArray<GnIListCtrlItemPtr>* columns = mListItems.GetAt( uiCol );
	GnIListCtrlItem* exitsItem = columns->GetAt( uiRow );
	if( exitsItem )
		RemoveChild( exitsItem );
	columns->SetAt( uiRow, pItem );
	
	SetItemCell( uiCol, uiRow, pItem );	
}

void GnIListCtrl::AddItem(GnIListCtrlItem* pItem)
{
	for( gtuint i = 0; i < mListItems.GetSize(); i++ )
	{
		GnTObjectArray<GnIListCtrlItemPtr>* columns = mListItems.GetAt( i );
		for ( gtuint j = 0 ; j < columns->GetSize(); j++ )
		{
			GnIListCtrlItem* item = columns->GetAt( j );
			if( item == NULL )
			{
				++mItemCount;
				SetItem( i, j, pItem );
				return;
			}
			else if( item->IsEmptyItem() )
			{
				++mItemCount;
				SetItem( i, j, pItem );
				return;
			}
		}
	}
	
	++mItemCount;
	AddRow();	
	GnTObjectArray<GnIListCtrlItemPtr>* columns = mListItems.GetAt( 0 );
	const gtuint numRow = columns->GetSize() - 1;
	SetItem( 0, numRow, pItem );
	
}

GnIListCtrlItemPtr GnIListCtrl::RemoveItem(GnIListCtrlItem* pItem)
{
	return RemoveItem( pItem->GetNumColumn(), pItem->GetNumRow(), pItem );
}

GnIListCtrlItemPtr GnIListCtrl::RemoveItem(gtuint uiCol, gtuint uiRow, GnIListCtrlItem* pItem)
{
	if( uiCol >= mColumnSize || uiRow >= mRowSize )
		return NULL;
	
	--mItemCount;
	GnTObjectArray<GnIListCtrlItemPtr>* columns = mListItems.GetAt( uiCol );
	GnIListCtrlItemPtr exitsItem = columns->GetAt( uiRow );
	if( exitsItem )
		RemoveChild( exitsItem );
	
	GnIListCtrlItem* emptyItem = NULL;
	if( mEmptyItemFileName.Exists() )
	{
		emptyItem = GnNew GnIListCtrlItem( mEmptyItemFileName );
		emptyItem->SetIsDisableCantpushBlind( true );
		emptyItem->SetIsCantPush( true );
		emptyItem->SetIsEmptyItem( true );
		SetItem( uiCol, uiRow, emptyItem );
		//emptyItem->SetPosition( pItem->GetPosition() );
		
	}
	else
		columns->SetAt( uiRow,  NULL );
	
	return exitsItem;
}

void GnIListCtrl::MoveX(float fMove)
{
	for( gtuint i = 0; i < mListItems.GetSize(); i++ )
	{
		GnTObjectArray<GnIListCtrlItemPtr>* columns = mListItems.GetAt( i );
		for ( gtuint j = 0 ; j < columns->GetSize(); j++ )
		{
			GnIListCtrlItem* exitsItem = columns->GetAt( j );
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
	bool setMovePosition = false;
	for( gtuint i = 0; i < mListItems.GetSize(); i++ )
	{
		GnTObjectArray<GnIListCtrlItemPtr>* columns = mListItems.GetAt( i );
		for ( gtuint j = 0 ; j < columns->GetSize(); j++ )
		{
			GnIListCtrlItem* exitsItem = columns->GetAt( j );
			if( exitsItem == NULL )
				continue;
			
			GnVector2 uiPoint = exitsItem->GetUIPoint();
			SetUIPosition( exitsItem, uiPoint.x, uiPoint.y + fMove);
			
			if( setMovePosition == false )
			{
				setMovePosition = true;
				SetMovedPositionY( j, exitsItem->GetUIPoint() );
			}
		}
	}
}

bool GnIListCtrl::Push(float fPointX, float fPointY)
{
	mLasterMovePosition = GnVector2( fPointX, fPointY );
	return GnInterfaceGroup::Push( fPointX, fPointY );
}

void GnIListCtrl::PushUp()
{
	GnInterfaceGroup::PushUp();
	if( mMoveType == eMoveUpDown )
	{
		GnLogA( "GnIListCtrl PushUp" );
		if( mListItems.GetSize() )
		{
			GnTObjectArray<GnIListCtrlItemPtr>* columns = mListItems.GetAt( 0 );
			if( columns->GetSize() )
			{
				GnIListCtrlItem* exitsItem = columns->GetAt( 0 );
				if( exitsItem )
				{
					GnVector2 uiPoint = exitsItem->GetUIPoint();								
					mRevisionPosition = GnVector2( 0, uiPoint.y - GetRect().top );
					if( mRevisionPosition.y >= 0 )
					{
						mRevisionDelta = -3.0f;
						mIsRevision = eMoveUpDown;
					}
				}
				if( mIsRevision != eNone )
					return;
				
				gtint checkRow = columns->GetSize() - mViewRowSize;
				if( checkRow < 0 )
					checkRow = 0;
				
				exitsItem = columns->GetAt( checkRow );
				if( exitsItem )
				{
					GnVector2 uiPoint = exitsItem->GetUIPoint();								
					mRevisionPosition = GnVector2( 0, GetRect().top - uiPoint.y );
					if( mRevisionPosition.y >= 0 )
					{
						mIsRevision = eMoveUpDown;
						mRevisionDelta = 3.0f;
					}
				}
			}		
		}
	}
	else if( mMoveType == eMoveLeftRight )
	{
	}
}

bool GnIListCtrl::PushMove(float fPointX, float fPointY)
{
	if( mMoveType == eMoveUpDown )
	{
		float move = fPointY - mLasterMovePosition.y;
		MoveY( move );
	}
	else if( mMoveType == eMoveLeftRight )
	{
		float move = fPointX - mLasterMovePosition.x;
		MoveX( move );
	}
	mLasterMovePosition = GnVector2( fPointX, fPointY );
	return GnInterfaceGroup::PushMove( fPointX, fPointY );
}

void GnIListCtrl::Update(float fTime)
{
	if( mIsRevision == eMoveUpDown )
	{
		if( mTimer.Update( fTime ) )
		{
			float revision = 0.0f;
			float delta = mRevisionDelta * mTimer.GetAmplify();
			if( mRevisionDelta < 0 )
			{
				revision = mRevisionPosition.y + delta;
				if( revision < 0.0f )
				{
					revision = -mRevisionPosition.y;
					mIsRevision = eNone;
				}
				else
				{
					revision = delta;
					mRevisionPosition.y += revision;
				}
			}
			else
			{
				revision = mRevisionPosition.y - delta;
				if( revision < 0.0f )
				{
					revision = mRevisionPosition.y;
					mIsRevision = eNone;
				}
				else
				{
					revision = delta;
					mRevisionPosition.y -= revision;
				}
			}			
			
			bool setMovePosition = false;
			for( gtuint i = 0; i < mListItems.GetSize(); i++ )
			{
				GnTObjectArray<GnIListCtrlItemPtr>* column = mListItems.GetAt( i );
				for ( gtuint j = 0 ; j < column->GetSize(); j++ )
				{
					GnIListCtrlItem* exitsItem = column->GetAt( j );
					if( exitsItem == NULL )
						continue;
					
					GnVector2 uiPoint = exitsItem->GetUIPoint();
					SetUIPosition( exitsItem, uiPoint.x, uiPoint.y + revision );
					
					if( setMovePosition == false )
					{
						setMovePosition = true;
						SetMovedPositionY( j, exitsItem->GetUIPoint() );
					}
				}
			}
			mTimer.Reset();
		}
	}
	else
	{
		
	}
}

void GnIListCtrl::Init(GnVector2 cStartUIPosition, gtuint uiNumColumn, gtuint uiNumRow
	, float fColumnGab, float fRowGab)
{
	mStartUIPosition = cStartUIPosition;
	mMovePosition = GnVector2( 0.0f, 0.0f );
	mColumnGab = fColumnGab;
	mRowGab = fRowGab;
	mMoveType = eNone;
	mIsRevision = eNone;
	mItemCount = 0;
	mTimer.SetPercentTime( 0.005f );
	SetSize( uiNumColumn, uiNumRow );
}

void GnIListCtrl::SetItemCell(gtuint uiCol, gtuint uiRow, GnIListCtrlItem* pItem)
{
	float pointX = GetBasePositionX( uiCol );
	float pointY = GetBasePositionY( uiRow );
	
	pItem->SetCell( uiCol, uiRow );
	SetUIPosition( pItem, pointX, pointY );
	
	GnVector2 uiPoint = pItem->GetUIPoint() + mMovePosition;
	SetUIPosition( pItem, uiPoint.x, uiPoint.y );
	
	AddChild( pItem );
}

void GnIListCtrl::SetMovedPositionY(gtuint uiRow, GnVector2 cCurrentUIPosition)
{
	float pointY = GetBasePositionY( uiRow );
	mMovePosition.y = cCurrentUIPosition.y - pointY;
}