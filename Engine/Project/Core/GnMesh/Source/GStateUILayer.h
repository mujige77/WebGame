//
//  GStateUILayer.h
//  Core
//
//  Created by Max Yoon on 11. 7. 30..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GStateUILayer_h
#define Core_GStateUILayer_h

#include "GInterfaceLayer.h"

class GnITabCtrl;
class GnIListCtrl;
class GnITabPage;
class GnINumberLabel;
class GStateListCtrlItem;
class GItemListCtrlItem;
class GStateUILayer : public GInterfaceLayer
{
public:
	enum TabPageID
	{
		UNIT_TAB,
		ABILITY_TAB,
		ITEM_TAB,
	};
	enum
	{
		NUM_STET_ROW = 5,
		NUM_STET_COLUMN = 3,
		NUM_ITEMSHOP_ROW = 2,
		NUM_ITEMSHOP_COLUMN = 3,
		NUM_ITEMINVEN_COLUMN = 2,
		NUM_ITEMEQUIP_ROW = 3,
	};
private:
	GnITabCtrl* mpTabCtrl;
	GnIListCtrl* mpAbilityListCtrl;
	GnIListCtrl* mpShopListCtrl;
	GnIListCtrl* mpInventoryListCtrl;
	GnIListCtrl* mpEquipListCtrl;
	GnINumberLabel* mStarLabel;
	GnINumberLabel* mMoneyLabel;
	GnInterfaceGroup* mpUnitGroup;
	
public:
	GStateUILayer();
	virtual ~GStateUILayer();	
	
public:
	virtual GnInterfaceGroup* CreateInterface(gtuint uiIndex
		, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pReceiveSlot);
	void Update(float fTime);
	
	GItemListCtrlItem* CreateItemCtrlItem(gtuint uiIndex);
	GItemListCtrlItem* CreateItemCtrlItem(gtuint uiIndex, GnInterface* pExplainParent);
	GItemListCtrlItem* CreateEquipCtrlItem(gtuint uiIndex);
	GItemListCtrlItem* CreateEquipCtrlItem(gtuint uiIndex, GnInterface* pExplainParent);
	
public:
	inline GnITabCtrl* GetTabCtrl() {
		return mpTabCtrl;
	}
	inline GnIListCtrl* GetAbilityListCtrl() {
		return mpAbilityListCtrl;
	}
	inline GnIListCtrl* GetShopListCtrl() {
		return mpShopListCtrl;
	}
	inline GnIListCtrl* GetInventoryListCtrl() {
		return mpInventoryListCtrl;
	}
	inline GnIListCtrl* GetEquipListCtrl() {
		return mpEquipListCtrl;
	}
	inline GnINumberLabel* GetStarLabel() {
		return mStarLabel;
	}
	inline GnINumberLabel* GetMoneyLabel() {
		return mMoneyLabel;
	}
	
protected:
	GnITabCtrl* CreateTabCtrl(GnVector2& cTabctrlSize);
	GnITabPage* CreateUnitPage();
	GnITabPage* CreateAbilityPage();
	GnITabPage* CreateItemPage();
	GnInterfaceGroup* CreateOtherUI();
	void CreateBasicAbilityCtrlItem(GnInterface* pExplainParent);
	void CreateBasicShopCtrlItem(GnInterface* pExplainParent);
	void CreateBasicInventoryCtrlItem(GnInterface* pExplainParent);
	void CreateBasicEquipCtrlItem(GnInterface* pExplainParent);
};

#endif
