#ifndef HiroCat_GStateScene_h
#define HiroCat_GStateScene_h

class GnIListPageCtrl;
class GnInterfaceGroup;
class GAbilityListCtrlItem;
class GItemListCtrlItem;
class GStateListCtrlItem;
class GnIListCtrl;
class GnINumberLabel;
class GUnitViewer;
class GUserHaveItem;
class GStateScene : public GScene
{
private:
	GLayer* mpInterfaceLayer;
	GLayer* mpBackgroundLayer;
	GnInterfaceGroup* mpOtherUIGroup;
	GnMemberSlot2<GStateScene, GnInterface*, GnIInputEvent*> mOtherInputEvent;
	GnMemberSlot2<GStateScene, GnInterface*, GnIInputEvent*> mUnitInputEvent;
	GnMemberSlot2<GStateScene, GnInterface*, GnIInputEvent*> mShopInputEvent;
	GnMemberSlot2<GStateScene, GnInterface*, GnIInputEvent*> mAbilityInputEvent;
	GStateListCtrlItem* mpCurrentStetItem;
	GStateListCtrlItem* mpCurrentShopItem;
	GStateListCtrlItem* mpCurrentInvenItem;
	GStateListCtrlItem* mpCurrentEquipItem;
	gint64 mCurrentControllerIndex;
	GUnitViewer* mpsUnitViewer;
	
public:
	GStateScene();
	virtual ~GStateScene();
	
public:
	static GStateScene* CreateScene();
	bool CreateInterface();
	bool CreateBackground();
	
public:
	virtual void Update(float fTime);
	virtual const gchar* GetSceneName();
	
protected:
	void OtherInputEvent(GnInterface* pInterface, GnIInputEvent* pEvent);
	void UnitInputEvent(GnInterface* pInterface, GnIInputEvent* pEvent);
	void ShopInputEvent(GnInterface* pInterface, GnIInputEvent* pEvent);
	void AbilityInputEvent(GnInterface* pInterface, GnIInputEvent* pEvent);
	bool ViewItemExplain(GStateListCtrlItem*& pCurrentItem, GnInterface* pInterface);
	guint32 SellItem(GnIListCtrl* pInvenList, GnIListCtrl* pEquipList, GnINumberLabel* pMoneyLabel
		, GStateListCtrlItem* pItem);
	void BuyItem(GnIListCtrl* pInvenList, GnIListCtrl* pEquipList, GnINumberLabel* pMoneyLabel
		, GStateListCtrlItem* pItem);
	void EquipItem(GnIListCtrl* pInvenList, GnIListCtrl* pEquipList, GStateListCtrlItem* pItem);
	void UnEquipItem(GnIListCtrl* pInvenList, GnIListCtrl* pEquipList, GStateListCtrlItem* pItem);
	void UpgradeAbility(GnINumberLabel* pStartLabel, GStateListCtrlItem*& pCurrentItem);
	void SelectUnit(guint32 uiUnitIndex, GnINumberLabel* pUnitMoneyLabel);
	void UpgradeUnit(gtuint uiUnitIndex, GnINumberLabel* pTotalMoneyLabel, GnINumberLabel* pUnitMoneyLabel);
	void UpdateItemCount(GUserHaveItem* pHaveItem, GnIListCtrl* pInvenList, GnIListCtrl* pEquipList
		, guint32 uiItemIndex, guint32 uiItemCount);
	GItemListCtrlItem* GetListCtrlItemFromIndex(GnIListCtrl* pInvenList, guint32 uiIndex);
};


#endif

