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
//#include "GGameScene.h"
//#include "GStartScene.h"

class GScene;
class GGameScene;
class GStartScene;
class GStateScene;
class GSelectStageScene;

class GSceneSelector : public GnMemoryObject
{
	GnDeclareSingleton(GSceneSelector);
private:
	static const guint DEFAULT_ZORDER = 100;
	GScene* mpCurrentScene;
	GStartScene* mpStartScene;
	GStateScene* mpStateScene;
	GSelectStageScene* mpSelectStageScene;
	GGameScene* mpGameScene;	
	
public:
	GSceneSelector();
	void RunApplication();
	void Update(float fTime);
	void ReleaseScene();
	void SetCurrentScene(GScene* pScene);
public:
	inline GScene* GetCurrentScene() {
		return mpCurrentScene;
	};
	
private:
	void ChangeSceneCheck();
	void SetUseActorFile();
	GScene* CreateGameScene();
	GScene* CreateStartScene();
	GScene* CreateStateScene();
	GScene* CreateSelectStageScene();
	void CreatePlayingData();
};

#endif
