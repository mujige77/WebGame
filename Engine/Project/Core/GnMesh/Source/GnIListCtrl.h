//
//  GnIListCtrl.h
//  Core
//
//  Created by Max Yoon on 11. 7. 27..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GnIListCtrl_h
#define Core_GnIListCtrl_h

#include "GnInterfaceGroup.h"
#include "GnIListCtrlItem.h"

class GnIListCtrl : public GnInterfaceGroup
{
public:
	enum eMoveType
	{
		/// Horizontal Left-Right
		eMoveUpDown,
		/// Horizontal Right-Left
		eMoveLeftRight,
		/// not move
		eNone,
	};
private:
	eMoveType mMoveType;
	gtuint mColumnSize;
	gtuint mRowSize;
	float mColumnGab;
	float mRowGab;
	GnTimer mTimer;
	eMoveType mIsRevision;
	GnVector2 mStartUIPosition;
	GnVector2 mMovePosition;
	GnTPrimitiveArray< GnTObjectArray<GnIListCtrlItemPtr>* > mListItems;
	GnVector2 mLasterMovePosition;
	GnVector2 mRevisionPosition;
	gtuint mViewRowSize;
	gtuint mViewColumnSize;
	float mRevisionDelta;
	gtuint mItemCount;
	GnSimpleString mEmptyItemFileName;
	
public:
	static GnIListCtrl* CreateListCtrl(GnVector2 cStartUIPosition, gtuint numColumn, gtuint numRow
		, float fColumnGab, float fRowGab);
	
	virtual ~GnIListCtrl();
	
public:
	void SetSize(gtuint uiNumColumn, gtuint uiNumRow);
	void AddColumn();
	void AddRow();
	void SetItem(gtuint uiCol, gtuint uiRow, GnIListCtrlItem* pItem);
	void AddItem(GnIListCtrlItem* pItem);
	GnIListCtrlItemPtr RemoveItem(GnIListCtrlItem* pItem);
	GnIListCtrlItemPtr RemoveItem(gtuint uiCol, gtuint uiRow, GnIListCtrlItem* pItem);
	void MoveX(float fMove);
	void MoveY(float fMove);
	
public:
	bool Push(float fPointX, float fPointY);
	void PushUp();
	bool PushMove(float fPointX, float fPointY);	
	void Update(float fTime);
public:
	inline void SetMoveType(eMoveType eType, gtuint uiViewCountColumn, gtuint uiViewCountRow) {		
		mMoveType = eType;
		mViewRowSize = uiViewCountRow;
		mViewColumnSize = uiViewCountColumn;
	}
	inline gtuint GetColumnSize() {
		return mColumnSize;
	}
	inline gtuint GetRowSize() {
		return mRowSize;
	}
	inline 	GnIListCtrlItem* GetItem(gtuint uiCol, gtuint uiRow) {
		GnTObjectArray<GnIListCtrlItemPtr>* columns = mListItems.GetAt( uiCol );
		if( columns )
			return columns->GetAt( uiRow );
		return NULL;
	};
	inline void SetEmptyItemFileName(const gchar* pcName) {
		mEmptyItemFileName = pcName;
	}
	inline gtuint GetItemCount() {
		return mItemCount;
	}
protected:
	void Init(GnVector2 cStartUIPosition, gtuint numColumn, gtuint numRow
		, float fColumnGab, float fRowGab);	
	void SetItemCell(gtuint uiCol, gtuint uiRow, GnIListCtrlItem* pItem);
	
private:
	void SetMovedPositionY(gtuint uiRow, GnVector2 cCurrentUIPosition);
	
private:	
	inline float GetBasePositionX(gtuint uiCol) {
		return mStartUIPosition.x + ( mColumnGab * uiCol );
	}
	inline float GetBasePositionY(gtuint uiRow) {
		return mStartUIPosition.y + ( mRowGab * uiRow );
	}
};

#endif
