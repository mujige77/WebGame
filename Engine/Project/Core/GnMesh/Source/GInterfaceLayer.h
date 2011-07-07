#ifndef __HiroCat__GInterfaceLayer__
#define __HiroCat__GInterfaceLayer__

class GnInterfaceGroup;
class GInterfaceLayer : public GLayer
{
public:
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
		FORCESBT_NUM
	};
	enum eUiType
	{
		UI_MAIN_CONTROLLERS,
		UI_MAIN_FORCESBUTTONS,
		UI_MAIN_SKILL,
	};
	
public:
	GInterfaceLayer();
	virtual GnInterfaceGroup* CreateInterface(gtuint uiIndex
		, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pSlot) = 0;
	
public:
	virtual void Create(CCSprite* pSprite);
};
#endif