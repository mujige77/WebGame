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
private:
	gtuint mNumColumn;
	gtuint mNumRow;
	float mColumnGab;
	float mRowGab;
	GnVector2 mStartUIPosition;
	GnVector2 mMovePosition;
	GnTPrimitiveArray< GnTObjectArray<GnIListCtrlItemPtr>* > mListItems;
	
public:
	static GnIListCtrl* CreateListCtrl(GnVector2 cStartUIPosition, gtuint numColumn, gtuint numRow
		, float fColumnGab, float fRowGab);
	
	virtual ~GnIListCtrl();
	
public:
	void SetSize(gtuint uiNumColumn, gtuint uiNumRow);
	void AddColumn();
	void AddRow();
	void SetItem(gtuint uiCol, gtuint uiRow, GnIListCtrlItem* pItem);
	void MoveX(float fMove);
	void MoveY(float fMove);
	
public:
	inline gtuint GetNumColumn() {
		return mNumColumn;
	}
	inline gtuint GetNumRow() {
		return mNumRow;
	}
protected:
	void Init(GnVector2 cStartUIPosition, gtuint numColumn, gtuint numRow
		, float fColumnGab, float fRowGab);	
};

#endif
