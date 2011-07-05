//
//  GGameManager.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GGameManager.h"
#include "GEnemyCtlrManager.h"
#include "GnSingletonManager.h"

//GGameManager* GGameManager::mpSingleton = CreateSingletonObjects(GGameManager);
//
//GGameManager* GGameManager::GetSingleton()
//{
//	return mpSingleton;
//}
//
//GnMemoryObject* GGameManager::Create()
//{
//	return GnNew GGameManager();
//}

GGameManager::GGameManager(GnLayer* pLayer)
{
	//mActorManage[ENEMY_CTLRMANAGER] = GnNew GEnemyCtlrManager(pLayer);
}

void GGameManager::Update(float fTime)
{
	for ( gtuint i = 0 ; i < MAX_CTLRMANAGER ; i++ )
	{
		mActorManage[i]->Update( fTime );
	}
}