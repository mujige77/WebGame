//
//  GnIListPageCtrl.h
//  Core
//
//  Created by Max Yoon on 11. 7. 28..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GnIListPageCtrl_h
#define Core_GnIListPageCtrl_h

#include "GnIListCtrl.h"

class GnIListPageCtrl : public GnInterfaceGroup
{
	enum ePageMove
	{
		eMovePosNext,
		eMovePosPrevious,
		eMoveStop,
	};
public:
	gtuint mColumnSize;
	gtuint mRowSize;
	gtuint mCurrentPage;
	ePageMove mPageMoveFlag;
	GnVector2 mStartUIPosition;
	GnVector2 mEndUIPosition;
	GnVector2 mTotalMovePosition;
	GnVector2 mAcumMovePosition;
	GnTimer mTimer;
	GnTPrimitiveArray<GnIListCtrl*> mListCtrls;
	GnTPrimitiveSet< GnBaseSlot2< GnInterface*, GnIInputEvent*>* > mSignalSet;
	
public:
	static GnIListPageCtrl* CreateListCtrl(GnVector2 cStartUIPosition, GnVector2 cEndUIPosition
		, gtuint uiNumPage, gtuint numColumn, gtuint numRow, float fColumnGab, float fRowGab);
public:
	void InitListCtrl(GnVector2 cStartUIPosition, GnVector2 cEndUIPosition, gtuint uiNumColumn, gtuint uiNumRow
		, float fColumnGab, float fRowGab);
	void SetNextPage();
	void SetPreviousPage();
	void SetPage(gtuint uiNumPage);	
	void SetItem(gtuint uiNumPage, gtuint uiNumCol, gtuint uiNumRow, GnIListCtrlItem* pItem);
	
public:
	virtual void Update(float fDeltaTime);
	void SubscribeClickedEvent(GnBaseSlot2<GnInterface*, GnIInputEvent*>* pSlot);
	
public:
	inline gtuint GetColumnSize() {
		return mColumnSize;
	}
	inline gtuint GetRowSize() {
		return mRowSize;
	}
	inline gtuint GetPageSize() {
		return mListCtrls.GetAllocatedSize();
	}
	inline gtuint GetCurrentPage() {
		return mCurrentPage;
	}
	
protected:
	inline GnIListPageCtrl() : mCurrentPage( 0 ), mPageMoveFlag( eMoveStop )
	{}
	
	void MovePosNext(GnVector2 cMoveDelta);
	void MovePosPrevious(GnVector2 cMoveDelta);
	void MoveAlpha();
	void SetListCtrlSubscribeClickedEvent();
	void MovingCheck();
protected:
	inline void SetNumPage(gtuint uiPage) {
		mListCtrls.SetSize( uiPage );
	}
//	inline gtuint GetOnePageColumnCount() {
//		return GetNumColumn() / GetNumPage();
//	}
};

#endif
