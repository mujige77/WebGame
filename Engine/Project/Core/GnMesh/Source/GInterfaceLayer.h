#ifndef __HiroCat__GInterfaceLayer__
#define __HiroCat__GInterfaceLayer__

class GnInterfaceGroup;
class GInterfaceLayer : public GLayer
{
public:
	enum eStartTabPage
	{
		eSelectModeTab,
		//eLoadTab,
		eOptionTab,
	};
	enum eStartButtons
	{
		BT_SELECT_EASY,
		BT_SELECT_NORMAL,
		BT_SELECT_HARD,
		BT_SOUNDON = 0,
		BT_SOUNDOFF,
		BT_RESETGAME,
	};
	enum eStateButtons
	{
		BT_STATE_FRONT,
		BT_STATE_BACK,
		LABEL_STATE_STAR,
		LABEL_STATE_MONEY,
		BT_ABILITY_UPGRADE,
		LISTITEM_SHOP,
		LISTITEM_INVEN,
		LISTITEM_EQUIP,
		BT_SELL_ITEM,
		BT_BUY_ITEM,
		BT_EQUIP_ITEM,
		BT_UNEQUIP_ITEM,
		BT_UPC1 = 1,
		BT_UPC2,
		BT_UPC3,
		BT_UPC4,
		BT_UPC5,
		BT_UPC6,
		BT_UPC7,
		BT_UPC8,
		BT_UPC9,
		BT_UPC10,
		BT_UNIT_UPGRADE,
	};
	
	enum eSelectStageButtons
	{
		BT_PREVIOUS,
		BT_NEXT,
		BT_SELECTSTAGE_BACK,
	};
	enum eControllerButton
	{
		MOVELEFT,
		MOVERIGHT,
		MOVEUP,
		MOVEDOWN,
		MOVE_NUM,
	};
	enum eCreateForcesButton
	{
		BT_C2,
		BT_C3,
		BT_C4,
		BT_C5,
		BT_C6,
		BT_C7,
		BT_C8,
		BT_C9,
		BT_C10,		
		BT_C11,
		FORCESBT_NUM
	};	
	enum eMainMenu
	{
//		FORCES_PROGRESS,
//		FORCES_PROGRESSICON,
//		ENEMY_PROGRESS,
//		ENEMY_PROGRESSICON,
//		HERO_PROGRESS,
//		HERO_PROGRESSICON,
		MENU_BUTTON,
		MAINMENU_NUM
	};
	enum eUiType
	{
		UI_MAIN_CONTROLLERS,
		UI_MAIN_FORCESBUTTONS,
		UI_MAIN_SKILL,
		UI_MAIN_OTHERUI,
		UI_START_TAB,
		UI_SELECTSTAGE_LIST,
		UI_SELECTSTAGE_BT,
		UI_STATE_UNITTAB,
		UI_STATE_ABILITYTAB,
		UI_STATE_SHOPTAB,
		UI_STATE_OTHERUI,
	};
	
public:
	GInterfaceLayer();
	
public:
	virtual GnInterfaceGroup* CreateInterface(gtuint uiIndex
		, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pSlot) = 0;
	virtual void Create(CCSprite* pSprite);
};
#endif