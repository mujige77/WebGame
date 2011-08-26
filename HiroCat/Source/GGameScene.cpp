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
#include "GCastleForces.h"
#include "GCastleEnemy.h"

GGameScene::GGameScene() : mpStageInfo( NULL ), mInputEvent( this, &GGameScene::InputEvent ), mIsWinGame( false )
	, mDialogEvent( this, &GGameScene::DialogInputEvent )
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

bool GGameScene::CreateScene(GStageInfo* pStageInfo)
{
	if( CreateBackgroundLayer( pStageInfo->GetBackgroundFileName() ) == false )
		return false;
	
	if( CreateInterfaceLayer( pStageInfo->GetInterfaceFileName() ) == false )
		return false;
	GStageInfo::GCastlePositions castlePos;
	pStageInfo->GetForcesCastlePosition( castlePos );
	mpsForcesCastle = GCastleForces::CreateCastle( mLayers[LAYER_INTERFACE], mLayers[LAYER_BACKGROUND]
		,pStageInfo, pStageInfo->GetForcesCastleFiles(), &castlePos );
	
	pStageInfo->GetEnemyCastlePosition( castlePos );
	mpsEnemyCastle = GCastleEnemy::CreateCastle( mLayers[LAYER_INTERFACE], mLayers[LAYER_BACKGROUND]
		,pStageInfo, pStageInfo->GetEnemyCastleFiles(), &castlePos );
	return true;
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
	
	mpOtherUI = interfaceLayer->CreateInterface( GInterfaceLayer::UI_MAIN_OTHERUI, &mInputEvent );
	mLayers[LAYER_INTERFACE] = interfaceLayer;
	addChild( mLayers[LAYER_INTERFACE], INTERFACE_ZORDER );
	return true;
}

bool GGameScene::CreateActorManager()
{
	GBackgroundLayer* backlayer = (GBackgroundLayer*)mLayers[LAYER_BACKGROUND];
	GInterfaceLayer* interfaceLayer =(GInterfaceLayer*)mLayers[LAYER_INTERFACE];
	CCSize interfaceSize = interfaceLayer->getContentSize();
	CCSize bgSize = backlayer->getContentSize();

	GEnemyCtlrManager* enemyCtlrManager = GEnemyCtlrManager::CreateActorCtlrManager( backlayer, mpsEnemyCastle );
		mpsActorManages[ENEMY_CTLRMANAGER] = enemyCtlrManager;
	enemyCtlrManager->AddEnableActorIndex( 3 );
	enemyCtlrManager->AddEnableActorIndex( 12 );
	
	GUserCtlrManager* userCtlrManager = GUserCtlrManager::CreateActorCtlrManager( backlayer, mLayers[LAYER_INTERFACE] );
	mpsActorManages[USER_CTLRMANAGER] = userCtlrManager;
	userCtlrManager->Init();
			
	GForcesCtlrManager* forcesCtlrManager = GForcesCtlrManager::CreateActorCtlrManager( backlayer
		, mLayers[LAYER_INTERFACE], mpsForcesCastle );
	mpsActorManages[FORCES_CTLRMANAGER] = forcesCtlrManager;
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
	return true;	
}

void GGameScene::Update(float fDeltaTime)
{
	if( CheckEndGame() )
		return;
	
	for ( gtuint i = 0 ; i < MAX_LAYER ; i++)
	{
		mLayers[i]->Update( fDeltaTime );
	}
	if( mpsEnemyCastle )
		mpsEnemyCastle->Update( fDeltaTime );
	if( mpsForcesCastle )
		mpsForcesCastle->Update( fDeltaTime );
	
	for ( gtuint i = 0 ; i < MAX_CTLRMANAGER ; i++)
	{
		for( gtuint j = 0 ; j < MAX_CTLRMANAGER ; j++)
		{
			if( i == j || ( i == USER_CTLRMANAGER && j == FORCES_CTLRMANAGER )
			   || ( j == USER_CTLRMANAGER && i == FORCES_CTLRMANAGER ) )
				continue;
			mpsActorManages[i]->ProcessAttack( mpsActorManages[j] );
			
		}
	}
	for ( gtuint i = 0 ; i < MAX_CTLRMANAGER ; i++)
	{
		mpsActorManages[i]->Update( fDeltaTime );
	}
}

const gchar* GGameScene::GetSceneName()
{
	return SCENENAME_GAME;
}

void GGameScene::InputEvent(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::PUSHUP )
	{
		if( mpOtherUI->GetChild( GInterfaceLayer::MENU_BUTTON ) == pInterface )
		{
			GInterfaceLayer* interfaceLayer =(GInterfaceLayer*)mLayers[LAYER_INTERFACE];
			GnInterfaceGroup* group = interfaceLayer->CreateInterface(
				GInterfaceLayer::UI_MAIN_DLG_PAUSE, &mDialogEvent );
			
			GScene::SetModalState( GDialog::CreateModalColor( group ) );
		}
	}
}

void GGameScene::DialogInputEvent(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::PUSHUP )
	{
		bool bDialogClose = true;
		switch ( pInterface->GetTegID() )
		{
			case GInterfaceLayer::DIALOG_LEVELSELECT_BUTTON:
				GScene::SetChangeSceneName( GScene::SCENENAME_STATE );
				break;
			case GInterfaceLayer::DIALOG_RESUME_BUTTON:
				break;
			case GInterfaceLayer::DIALOG_REPLAY_BUTTON:
				break;
			case GInterfaceLayer::DIALOG_NEXT_BUTTON:
				GScene::SetChangeSceneName( GScene::SCENENAME_STATE );
				break;
			default:
				bDialogClose = false;
				break;
		}
		
		if( bDialogClose )
		{
			GScene::SetModalState( NULL );
		}
	}	
}

bool GGameScene::CheckEndGame()
{
	GUserCtlrManager* userCtlrManager = (GUserCtlrManager*)((GActorCtlrManager*)mpsActorManages[USER_CTLRMANAGER]);
	if( mpsEnemyCastle->GetCurrentHP() <= 0 )
	{
		WinGame();
		return true;
	}
	else if( mpsForcesCastle->GetCurrentHP() <= 0 || userCtlrManager->GetUserCurrentHP() <= 0 )
	{
		LoseGame();
		return true;
	}
	
	return false;
}

void GGameScene::WinGame()
{
	SetIsWinGame( true );
	GScene::SetChangeSceneName( GScene::SCENENAME_STATE );
}

void GGameScene::LoseGame()
{
	SetIsWinGame( false );
	GScene::SetChangeSceneName( GScene::SCENENAME_STATE );
}