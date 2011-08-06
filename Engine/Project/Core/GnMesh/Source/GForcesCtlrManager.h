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
	static GForcesCtlrManager* CreateActorCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer
		, GCastle* pCastle = NULL);
	
public:
	void Update(float fDeltaTime);
	void Init();
	
protected:
	GForcesCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer, GCastle* pCastle = NULL);
	void CreateForces(GnInterface* pInterface, GnIInputEvent* pEvent);

};

#endif
