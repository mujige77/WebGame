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
#include "GMainGameInterfaceLayer.h"
#include "GForcesCtlrManager.h"
#include "GUserCtlrManager.h"
#include "GEnemyCtlrManager.h"
#include "GMainGameEnvironment.h"

GGameScene::GGameScene() : mNumLine( 2 )
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
	for( gtuint i = 0 ; i < MAX_CTLRMANAGER ; i++ )
	{
		if( mActorManage[i] )
			GnDelete mActorManage;
	}
}

bool GGameScene::CreateBackgroundLayer(const gchar *pcName)
{
	GBackgroundLayer* backlayer = GBackgroundLayer::Create( pcName );
	if( backlayer == NULL )
		return false;
	
	mLayers[LAYER_BACKGROUND] = backlayer;
	addChild( backlayer, BACKGROUND_ZORDER );
	return true;
}

bool GGameScene::CreateInterfaceLayer(const gchar *pcName)
{
	GInterfaceLayer* interfaceLayer = GMainGameInterfaceLayer::Create( pcName );
	if( interfaceLayer == NULL )
		return false;
	
	//mLayers[LAYER_INTERFACE]->setPosition( CCPointMake( -(GetGameState()->GetGameWidth() / 2), -(GetGameState()->GetGameHeight() / 2)) );
	mLayers[LAYER_INTERFACE] = interfaceLayer;
	addChild( mLayers[LAYER_INTERFACE], INTERFACE_ZORDER );
	return true;
}

bool GGameScene::CreateActorLayer()
{
	GBackgroundLayer* backlayer = (GBackgroundLayer*)mLayers[LAYER_BACKGROUND];
	GInterfaceLayer* interfaceLayer =(GInterfaceLayer*)mLayers[LAYER_INTERFACE];
	CCSize interfaceSize = interfaceLayer->getContentSize();
	CCSize bgSize = backlayer->getContentSize();

	GEnemyCtlrManager* enemyCtlrManager = GnNew GEnemyCtlrManager( backlayer );
		mActorManage[ENEMY_CTLRMANAGER] = enemyCtlrManager;
	enemyCtlrManager->AddEnableActorIndex( 3 );
	enemyCtlrManager->AddEnableActorIndex( 12 );
	
	GUserCtlrManager* userCtlrManager = GnNew GUserCtlrManager( backlayer, mLayers[LAYER_INTERFACE] );
	mActorManage[USER_CTLRMANAGER] = userCtlrManager;
	userCtlrManager->Init();
			
	GForcesCtlrManager* forcesCtlrManager = GnNew GForcesCtlrManager( backlayer
		, mLayers[LAYER_INTERFACE] );
	mActorManage[FORCES_CTLRMANAGER] = forcesCtlrManager;
	forcesCtlrManager->Init();
	forcesCtlrManager->AddEnableActorIndex( 2 );
	forcesCtlrManager->AddEnableActorIndex( 3 );
	forcesCtlrManager->AddEnableActorIndex( 4 );
	return true;
}

bool GGameScene::InitEnvironment()
{
	GBackgroundLayer* backlayer = (GBackgroundLayer*)mLayers[LAYER_BACKGROUND];
	GInterfaceLayer* interfaceLayer =(GInterfaceLayer*)mLayers[LAYER_INTERFACE];
	CCSize interfaceSize = interfaceLayer->getContentSize();
	CCSize bgSize = backlayer->getContentSize();
	
	GMainGameEnvironment::GetSingleton()->SetEnableMoveRect( GnFRect( 50.0f, 0.0f
		, bgSize.width - 100.0f, GetGameState()->GetGameHeight() - interfaceSize.height) );
	
	float basePosition = interfaceSize.height + 10.0f;
	for( gtuint i = 0 ; i < mNumLine ; i++ )
	{
		GMainGameEnvironment::GetSingleton()->AddLine( basePosition + ( 40.0f * (float)i ) );
	}
	GMainGameEnvironment::GetSingleton()->SetMoveRangeY( 40.0f );
	return true;	
}
void GGameScene::Update(float fDeltaTime)
{
	for ( gtuint i = 0 ; i < MAX_LAYER ; i++)
	{
		mLayers[i]->Update( fDeltaTime );
	}
	
	for ( gtuint i = 0 ; i < MAX_CTLRMANAGER ; i++)
	{
		for( gtuint j = 0 ; j < MAX_CTLRMANAGER ; j++)
		{
			if( i == j )
				continue;
			mActorManage[i]->ProcessAttack( mActorManage[j] );
			
		}
	}
	for ( gtuint i = 0 ; i < MAX_CTLRMANAGER ; i++)
	{
		mActorManage[i]->Update( fDeltaTime );
	}
}