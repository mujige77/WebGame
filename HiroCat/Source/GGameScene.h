//
//  GGameScene.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GGameScene__
#define __HiroCat__GGameScene__

#include "GActorCtlrManager.h"

class GGameScene : public GScene
{
	enum eLayerZorder
	{
		BACKGROUND_ZORDER = 99,
	};
	enum eLayerType
	{
		LAYER_BACKGROUND,
		LAYER_INTERFACE,
		MAX_LAYER,
	};	
	enum eManagerType
	{
		USER_CTLRMANAGER,
		FORCES_CTLRMANAGER,		
		ENEMY_CTLRMANAGER,
		MAX_CTLRMANAGER,
	};
	
private:
	gtuint mNumLine;
	GLayer* mLayers[MAX_LAYER];
	GActorCtlrManager* mActorManage[MAX_CTLRMANAGER];
	
public:
	GGameScene();
	virtual ~GGameScene();
	
	bool CreateBackgroundLayer(const gchar* pcName);
	bool CreateInterfaceLayer(const gchar* pcName);
	bool CreateActorLayer();
	bool InitEnvironment();	
	virtual void Update(float fDeltaTime);
};

#endif
