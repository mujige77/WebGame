#ifndef __Core__GUserCtlrManager__
#define __Core__GUserCtlrManager__

#include "GActorCtlrManager.h"

class GnIButton;
class GnInterfaceGroup;
class GInterfaceLayer;
class GUserCtlrManager : public GActorCtlrManager
{
	static const gtuint NUM_BUTTON = 4;

private:
	GInterfaceLayer* mpInterfaceLayer;
	GActorController* mpUserCtlr;
	GnInterfaceGroup* mpButtonGroup;
	GnMemberSlot2<GUserCtlrManager, GnInterface*, GnIInputEvent*> mMoveInputEvent;
	GnMemberSlot2<GUserCtlrManager, GnInterface*, GnIInputEvent*> mSkillInputEvent;
	
public:
	static GUserCtlrManager* CreateActorCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer);
	
public:
	virtual ~GUserCtlrManager();
	
public:
	void Update(float fDeltaTime);
	void Init();
	gint32 GetUserCurrentHP();
protected:
	GUserCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer);
	void UpdateBackgroundLayer();

protected:
	void Move(GnInterface* pInterface, GnIInputEvent* pEvent);
	void SkillInput(GnInterface* pInterface, GnIInputEvent* pEvent);
};

#endif
