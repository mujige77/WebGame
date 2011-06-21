//
//  GMobManager.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GMobCtlrManager__
#define __HiroCat__GMobCtlrManager__

#include "GActorCtlrManager.h"

class GEnemyCtlrManager : public GActorCtlrManager
{
	static const gtuint mNumAccackLine = 2;
private:
	GAccumulationTimeEvent mNewEnemyTimeEvent;	
	
public:
	GEnemyCtlrManager(GLayer* pLayer);
	void Update(float fDeltaTime);
	
protected:
	void CreateEnemy();
};

#endif
