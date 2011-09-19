
#ifndef __HiroCat__GMobCtlrManager__
#define __HiroCat__GMobCtlrManager__

#include "GActorCtlrManager.h"

class GStageLevelManager;
class GStageLevel;
class GEnemyCtlrManager : public GActorCtlrManager, public CCTargetedTouchDelegate
{
private:
	GStageLevelManager* mpStageLevelManager;
	guint32 mDropMoney;
	GnTimer mEnableDropMoneyTime;
	
public:
	static GEnemyCtlrManager* CreateActorCtlrManager(GLayer* pLayer, GStageLevelManager* pStageLevelManager
		, GCastle* pCastle = NULL);

public:
	~GEnemyCtlrManager();
	void Update(float fDeltaTime);
	
public:
	void RemoveAndDeleteActorCtlr(gtuint uiIndex);

public:
	guint32 GetDropMoney() {
		return mDropMoney;
	};
protected:
	GEnemyCtlrManager(GLayer* pLayer, GStageLevelManager* pStageLevelManager, GCastle* pCastle = NULL);
	void CreateEnemy(guint32 uiIndex, guint32 uiLevel, guint32 uiLine);
	
protected:

};

#endif
