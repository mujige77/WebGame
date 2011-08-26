#include "GnGamePCH.h"
#include "GnIListPageCtrl.h"


GnIListPageCtrl* GnIListPageCtrl::CreateListCtrl(GnVector2 cStartUIPosition, GnVector2 cEndUIPosition
	, gtuint uiNumPage, gtuint numColumn, gtuint numRow, float fColumnGab, float fRowGab)
{
	GnIListPageCtrl* ctrl = GnNew GnIListPageCtrl();
	ctrl->SetNumPage( uiNumPage );
	ctrl->InitListCtrl( cStartUIPosition, cEndUIPosition, numColumn, numRow, fColumnGab, fRowGab );	
	return ctrl;
}

void GnIListPageCtrl::InitListCtrl(GnVector2 cStartUIPosition, GnVector2 cEndUIPosition
	, gtuint uiNumColumn, gtuint uiNumRow, float fColumnGab, float fRowGab)
{
	mStartUIPosition = cStartUIPosition;
	mEndUIPosition = cEndUIPosition;
	mTotalMovePosition = cEndUIPosition - cStartUIPosition;
	mColumnSize = uiNumColumn;
	mRowSize = uiNumRow;
	mPageMoveFlag = eMoveStop;
	mTimer.SetPercentTime( 0.001f );
	for ( gtuint i = 0; i < mListCtrls.GetAllocatedSize() ; i++ )
	{
		GnIListCtrl* ctrl = GnIListCtrl::CreateListCtrl( cStartUIPosition, uiNumColumn, uiNumRow
			, fColumnGab, fRowGab );
		ctrl->SetRect( cStartUIPosition.x, cStartUIPosition.y, cEndUIPosition.x, cEndUIPosition.y );
		AddChild( ctrl );
		ctrl->GetParentUseNode()->setPosition( CCPointMake( i * mTotalMovePosition.x, 0 ) );
		mListCtrls.SetAt( i , ctrl );
	}
	SetListCtrlSubscribeClickedEvent();
}

void GnIListPageCtrl::Update(float fDeltaTime)
{
	GnVector2 moveDelta( 2.0f, 0.0f );
	
	
	if( mPageMoveFlag == eMovePosNext )
	{
		if( mTimer.Update( fDeltaTime ) )
		{
			MovePosNext( moveDelta * mTimer.GetAmplify() );
			MoveAlpha();
			mTimer.Reset();
		}
	}
	else if( mPageMoveFlag == eMovePosPrevious )
	{
		if( mTimer.Update( fDeltaTime ) )
		{
			MovePosPrevious( moveDelta * mTimer.GetAmplify() );
			MoveAlpha();
			mTimer.Reset();
		}
	}
}

void GnIListPageCtrl::SubscribeClickedEvent(GnBaseSlot2<GnInterface*, GnIInputEvent*>* pSlot)
{
	//GnInterfaceGroup::SubscribeClickedEvent( pSlot );
	mSignalSet.Add( pSlot );
	for ( gtuint i = 0; i < mListCtrls.GetSize() ; i++ )
	{
		mListCtrls.GetAt( i )->SubscribeClickedEvent( pSlot );
	}
}

void GnIListPageCtrl::SetNextPage()
{
	MovingCheck();
	if( mCurrentPage < GetPageSize() - 1 )
	{		
		mPageMoveFlag = eMovePosNext;
		GnIListCtrl* nextCtrl = mListCtrls.GetAt( mCurrentPage + 1 );
		nextCtrl->SetAlpha( 0 );
		nextCtrl->SetIsVisible( true );
		mAcumMovePosition = GnVector2( 0.0f, 0.0f );
	}
}

void GnIListPageCtrl::SetPreviousPage()
{
	MovingCheck();
	if( mCurrentPage > 0 )
	{
		mPageMoveFlag = eMovePosPrevious;
		GnIListCtrl* previousCtrl = mListCtrls.GetAt( mCurrentPage - 1 );
		previousCtrl->SetAlpha( 0 );
		previousCtrl->SetIsVisible( true );
		mAcumMovePosition = GnVector2( 0.0f, 0.0f );
	}
}

void GnIListPageCtrl::SetPage(gtuint uiNumPage)
{
	for ( gtuint i = 0 ; i < mListCtrls.GetSize(); i++ )
	{
		GnIListCtrl* ctrl = mListCtrls.GetAt( i );
		if( uiNumPage == i )
		{
			ctrl->SetAlpha( 255 );
			ctrl->SetIsVisible( true );
			ctrl->GetParentUseNode()->setPosition( CCPointMake( 0.0f, 0.0f ) );
			break;
		}
	}
	
	gtint numPoint = 0;
	for ( gtint i = uiNumPage - 1; i > -1; i-- )
	{
		GnIListCtrl* ctrl = mListCtrls.GetAt( i );
		ctrl->GetParentUseNode()->setPosition( CCPointMake( ( numPoint++ + 1 ) * -mTotalMovePosition.x, 0.0f ) );
		ctrl->SetIsVisible( false );
	}
	
	numPoint = 0;
	for ( gtuint i = uiNumPage + 1; i < mListCtrls.GetSize(); i++ )
	{
		GnIListCtrl* ctrl = mListCtrls.GetAt( i );
		ctrl->GetParentUseNode()->setPosition( CCPointMake( ( numPoint++ + 1 ) * mTotalMovePosition.x, 0.0f ) );
		ctrl->SetIsVisible( false );
	}
	mCurrentPage = uiNumPage;
}

void GnIListPageCtrl::SetItem(gtuint uiNumPage, gtuint uiNumCol, gtuint uiNumRow, GnIListCtrlItem* pItem)
{
	if( mListCtrls.GetAllocatedSize() > uiNumPage )
	{
		GnIListCtrl* ctrl = mListCtrls.GetAt( uiNumPage );
		ctrl->SetItem( uiNumCol, uiNumRow, pItem );
	}
}

void GnIListPageCtrl::MovePosNext(GnVector2 cMoveDelta)
{
	mAcumMovePosition += cMoveDelta;
	if( mAcumMovePosition.x >= mTotalMovePosition.x )
	{
		mPageMoveFlag = eMoveStop;
		SetPage( mCurrentPage + 1 );
		return;
	}
	
	for ( gtuint i = 0; i < mListCtrls.GetSize(); i++ )
	{
		GnIListCtrl* ctrl = mListCtrls.GetAt( i );
		CCPoint curPoint = ctrl->GetParentUseNode()->getPosition();
		curPoint.x -= cMoveDelta.x;
		ctrl->GetParentUseNode()->setPosition( curPoint );
	}
}

void GnIListPageCtrl::MovePosPrevious(GnVector2 cMoveDelta)
{
	mAcumMovePosition += cMoveDelta;
	if( mAcumMovePosition.x >= mTotalMovePosition.x )
	{
		mPageMoveFlag = eMoveStop;
		SetPage( mCurrentPage - 1 );
		return;
	}
	
	for ( gtuint i = 0; i < mListCtrls.GetSize(); i++ )
	{
		GnIListCtrl* ctrl = mListCtrls.GetAt( i );
		CCPoint curPoint = ctrl->GetParentUseNode()->getPosition();
		curPoint.x += cMoveDelta.x;
		ctrl->GetParentUseNode()->setPosition( curPoint );
	}
}

void GnIListPageCtrl::MoveAlpha()
{
	if( mPageMoveFlag == eMoveStop )
		return;
	
	guchar inAlpha = (mAcumMovePosition.x / mTotalMovePosition.x) * 255;
	guchar outAlpha = 255 - ( (mAcumMovePosition.x / mTotalMovePosition.x) * 255 );
	GnIListCtrl* ctrl = mListCtrls.GetAt( mCurrentPage );
	ctrl->SetAlpha( outAlpha );
	
	if( mPageMoveFlag == eMovePosNext )
	{
		ctrl = mListCtrls.GetAt( mCurrentPage + 1 );
		ctrl->SetAlpha( inAlpha );
	}
	else if( mPageMoveFlag == eMovePosPrevious )
	{
		ctrl = mListCtrls.GetAt( mCurrentPage - 1 );
		ctrl->SetAlpha( inAlpha );
	}
}

void GnIListPageCtrl::SetListCtrlSubscribeClickedEvent()
{
	for ( gtuint i = 0; i < mSignalSet.GetSize(); i++ )
	{
		for ( gtuint j = 0; j < mListCtrls.GetSize(); j++ )
		{
			GnIListCtrl* ctrl = mListCtrls.GetAt( j );
			ctrl->SubscribeClickedEvent( mSignalSet.GetAt( i ) );
		}
	}
}

void GnIListPageCtrl::MovingCheck()
{
	if( mPageMoveFlag == eMovePosNext )
	{
		SetPage( mCurrentPage + 1 );
		mPageMoveFlag = eMoveStop;
	}
	else if( mPageMoveFlag == eMovePosPrevious )
	{
		SetPage( mCurrentPage - 1 );
		mPageMoveFlag = eMoveStop;
	}
}