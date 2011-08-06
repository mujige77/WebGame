
#ifndef __HiroCat__GMobCtlrManager__
#define __HiroCat__GMobCtlrManager__

#include "GActorCtlrManager.h"


class GEnemyCtlrManager : public GActorCtlrManager, public CCTargetedTouchDelegate
{
private:
	GAccumulationTimeEvent mNewEnemyTimeEvent;	
	
public:
	static GEnemyCtlrManager* CreateActorCtlrManager(GLayer* pLayer, GCastle* pCastle = NULL);

	void Update(float fDeltaTime);
	
protected:
	GEnemyCtlrManager(GLayer* pLayer, GCastle* pCastle = NULL);
	void CreateEnemy();
	
protected:
};

#endif
