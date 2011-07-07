
#ifndef __HiroCat__GMobCtlrManager__
#define __HiroCat__GMobCtlrManager__

#include "GActorCtlrManager.h"


class GEnemyCtlrManager : public GActorCtlrManager, public CCTargetedTouchDelegate
{
private:
	GAccumulationTimeEvent mNewEnemyTimeEvent;	
	
public:
	GEnemyCtlrManager(GLayer* pLayer);
	void Update(float fDeltaTime);
	
protected:
	void CreateEnemy();
	
protected:
};

#endif
