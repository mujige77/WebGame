//
//  GnIListCtrlItem.h
//  Core
//
//  Created by Max Yoon on 11. 7. 27..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GnIListCtrlItem_h
#define Core_GnIListCtrlItem_h

class GnIListCtrlItem : public GnIButton
{
	GnDeclareRTTI;
private:
//	gint32 mItemIndex;
	guint32 mNumRow;
	guint32 mNumColumn;
	
public:
	GnIListCtrlItem(const gchar* pcDefaultImage, const gchar* pcClickImage = NULL
		, const gchar* pcDisableImage = NULL, eButtonType eDefaultType = TYPE_NORMAL);
	virtual ~GnIListCtrlItem();
	
public:
	virtual bool PushUp(float fPointX, float fPointY);
	virtual bool PushMove(float fPointX, float fPointY);
	virtual void Push();
	virtual void PushUp();

public:
//	inline void SetItemIndex(gint32 val) {
//		mItemIndex = val;
//	}
//	inline gint32 GetItemIndex() {
//		return mItemIndex;
//	}
	inline void SetCell(guint32 uiCol, guint32 uiRow) {
		mNumColumn = uiCol;
		mNumRow = uiRow;
	}
	inline guint32 GetNumRow() {
		return mNumRow;
	}
	inline guint32 GetNumColumn() {
		return mNumColumn;
	}
};

GnSmartPointer(GnIListCtrlItem);

#endif
