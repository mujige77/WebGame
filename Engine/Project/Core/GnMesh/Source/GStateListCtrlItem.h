#ifndef Core_GStateListCtrlItem_h
#define Core_GStateListCtrlItem_h

#include "GnIListCtrlItem.h"
#include "GnINumberLabel.h"

class GStateListCtrlItem : public GnIListCtrlItem
{
	GnDeclareRTTI;
private:
	GnInterface* mpItemExplain;
	GnInterface* mpExplainParent;
	guint32 mItemIndex;
	
public:
	GStateListCtrlItem(const gchar* pcDefaultImage, const gchar* pcClickImage = NULL
					  , const gchar* pcDisableImage = NULL, eButtonType eDefaultType = TYPE_NORMAL);
	virtual ~GStateListCtrlItem();
	
public:
	inline GnInterface* GetItemExplain() {
		return mpItemExplain;
	}
	inline void SetItemExplain(GnInterface* pParent, GnInterface* val) {
		mpItemExplain = val;
		mpExplainParent = pParent;
	}
	inline void SetVisibleExplain(bool val) {
		if( mpItemExplain )
			mpItemExplain->SetIsVisible( val );
	}
	inline bool IsVisibleExplain() {
		if( mpItemExplain )
			return mpItemExplain->IsVisible();
		return false;
	}
	inline void SetItemIndex(guint32 val) {
		mItemIndex = val;
	}
	inline guint32 GetItemIndex() {
		return mItemIndex;
	}
};

#endif
