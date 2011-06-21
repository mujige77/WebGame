//
//  GBackgroundSelcetor.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GBackgroundSelcetor__
#define __HiroCat__GBackgroundSelcetor__
#include "GnSingletonManager.h"

class GScene;
class GSceneSelector : public GnMemoryObject
{
	GnDeclareSingleton(GSceneSelector);
private:
	static const guint DEFAULT_ZORDER = 100;
	GScene* mpCurrentScene;
	
public:	
	GScene* CreateScene(gtuint uiStage);
	void RunApplication();
	
public:
	inline GScene* GetCurrentScene() {
		return mpCurrentScene;
	};
	
protected:
	void SetUseActorFile();
};

#endif
