#ifndef Core_GItemListCtrlItem_h
#define Core_GItemListCtrlItem_h

#include "GStateListCtrlItem.h"
#include "GnINumberLabel.h"

class GItemListCtrlItem : public GStateListCtrlItem
{
	GnDeclareRTTI;
private:
	bool mCreateLabelPrice;
	GnINumberLabel mLabelPrice;
	GnInterfacePtr mpsIconMoney;
	
public:
	GItemListCtrlItem(const gchar* pcDefaultImage, const gchar* pcClickImage = "Upgrade/items/30_140 s.png"
					  , const gchar* pcDisableImage = NULL, eButtonType eDefaultType = TYPE_NORMAL);
	virtual ~GItemListCtrlItem(){};
	
public:
	void CreateLabelPrice();
	void CreateIconMoney();
	void SetPosition(GnVector2& cPos);
	
public:
	inline void SetPrice(guint32 val) {
		mLabelPrice.SetNumber( val );
	}	
};

#endif
