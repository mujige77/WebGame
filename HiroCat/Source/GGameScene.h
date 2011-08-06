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
#include <GStageInfo.h>

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
	GLayer* mLayers[MAX_LAYER];
	GActorCtlrManagerPtr mpsActorManages[MAX_CTLRMANAGER];
	GCastlePtr mpsEnemyCastle;
	GCastlePtr mpsForcesCastle;
	GStageInfo* mpStageInfo;
	GnMemberSlot2<GGameScene, GnInterface*, GnIInputEvent*> mInputEvent;
	GnInterfaceGroup* mpOtherUI;
	bool mIsWinGame;
	
public:
	GGameScene();
	virtual ~GGameScene();
	
	bool CreateScene(GStageInfo* pStageInfo);
	bool CreateBackgroundLayer(const gchar* pcName);
	bool CreateInterfaceLayer(const gchar* pcName);
	bool CreateActorManager();
	bool InitEnvironment();	
	
public:
	virtual void Update(float fDeltaTime);
	const gchar* GetSceneName();
	
public:
	inline bool IsWinGame() {
		return mIsWinGame;
	}

protected:
	void InputEvent(GnInterface* pInterface, GnIInputEvent* pEvent);
	bool CheckEndGame();
	void WinGame();
	void LoseGame();
	
protected:
	inline void SetIsWinGame(bool val) {
		mIsWinGame = val;
	}
};

#endif
