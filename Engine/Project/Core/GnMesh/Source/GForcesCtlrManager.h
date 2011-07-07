 #ifndef __Core__GForcesCtlrManager__
#define __Core__GForcesCtlrManager__

#include "GActorCtlrManager.h"
class GnIButton;
class GInterfaceLayer;
class GnInterfaceGroup;
class GForcesCtlrManager : public GActorCtlrManager
{
private:
	GInterfaceLayer* mpInterfaceLayer;
	GnInterfaceGroup* mpButtonGroup;
	GnMemberSlot2<GForcesCtlrManager, GnInterface*, GnIInputEvent*> mCreateForcesInputEvent;
	
public:
	GForcesCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer);
	
public:
	void Update(float fDeltaTime);
	void Init();
	
protected:
	void CreateForces(GnInterface* pInterface, GnIInputEvent* pEvent);

};

#endif
