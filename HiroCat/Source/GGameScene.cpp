//
//  GGameScene.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GamePCH.h"
#include "GGameScene.h"
#include "GBackgroundLayer.h"
#include "GInterfaceLayer.h"
#include "GEnemyCtlrManager.h"

GGameScene::GGameScene()
{
	memset( mLayers, NULL, sizeof(mLayers) );
}
GGameScene::~GGameScene()
{
	for( gtuint i = 0 ; i < MAX_LAYER ; i++ )
	{
		if( mLayers[i] )
			mLayers[i]->release();
	}
}

bool GGameScene::CreateBackgroundLayer(const gchar *pcName)
{
	mLayers[LAYER_BACKGROUND] = GBackgroundLayer::Create( pcName );
	if( mLayers[LAYER_BACKGROUND] == NULL )
		return false;
	addChild( mLayers[LAYER_BACKGROUND], BACKGROUND_ZORDER );
	return true;
}

bool GGameScene::CreateInterfaceLayer(const gchar *pcName)
{
	mLayers[LAYER_INTERFACE] = GInterfaceLayer::Create( pcName );
	if( mLayers[LAYER_INTERFACE] == NULL )
		return false;
	addChild( mLayers[LAYER_INTERFACE], INTERFACE_ZORDER );
	return true;
}

bool GGameScene::CreateActorLayer()
{
	GBackgroundLayer* backlayer = (GBackgroundLayer*)mLayers[LAYER_BACKGROUND];
	GEnemyCtlrManager* enemyCtlrManager = GnNew GEnemyCtlrManager( backlayer );
	mActorManage[ENEMY_CTLRMANAGER] = enemyCtlrManager;
	
	enemyCtlrManager->SetStartActorPostion( 10.0f, backlayer->GetCharacterLinePostion() );
	enemyCtlrManager->AddEnableActorIndex( 3 );
	enemyCtlrManager->AddEnableActorIndex( 10 );
	enemyCtlrManager->AddEnableActorIndex( 12 );

	return true;
}

void GGameScene::Update(float fDeltaTime)
{
	for ( gtuint i = 0 ; i < MAX_CTLRMANAGER ; i++)
	{
		mActorManage[i]->Update( fDeltaTime );
	}
}