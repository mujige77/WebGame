#ifndef Core_GAbilityListCtrlItem_h
#define Core_GAbilityListCtrlItem_h

#include "GStateListCtrlItem.h"
#include "GnINumberLabel.h"

class GAbilityListCtrlItem : public GStateListCtrlItem
{
	GnDeclareRTTI;
private:
	GnINumberLabel mLabelCurrentLevel;
	GnINumberLabel mLabelMaxLevel;
	
//public:
//	static GAbilityListCtrlItem* CreateListCtrlItem(gtuint uiRow, gtuint uiColumn, gtuint uiID);
	
public:
	GAbilityListCtrlItem(const gchar* pcDefaultImage, const gchar* pcClickImage = NULL
		, const gchar* pcDisableImage = NULL, eButtonType eDefaultType = TYPE_NORMAL);
	virtual ~GAbilityListCtrlItem(){};
	
public:
	void SetPosition(GnVector2& cPos);
	
public:
	inline guint32 GetCurrentLevel() {
		return (guint32)mLabelCurrentLevel.GetNumber();
	}
	inline void SetCurrentLevel(guint32 val) {
		mLabelCurrentLevel.SetNumber( val );
	}
	inline guint32 GetMaxLevel() {
		return (guint32)mLabelMaxLevel.GetNumber();
	}
	inline void SetMaxLevel(guint32 val) {
		mLabelMaxLevel.SetNumber( val );
	}
};

#endif
