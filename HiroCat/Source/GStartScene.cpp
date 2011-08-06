//
//  GStartScene.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 13..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GamePCH.h"
#include "GStartScene.h"
#include "GnITabCtrl.h"
#include "GStartInterfaceLayer.h"
#include "GStartBackgroundLayer.h"
#include "GPlayingDataManager.h"
#include "GPlayingData.h"
#include "GLoadButtonLabel.h"

GStartScene::GStartScene() : mInputEvent( this, &GStartScene::InputEvent )
{
}

GStartScene::~GStartScene()
{
}

GStartScene* GStartScene::CreateStartScene()
{
	GStartScene* scene = new GStartScene();
	if( scene->CreateInterface() == false || scene->CreateBackground() == false )
	{
		delete scene;
		return NULL;
	}
	return scene;
}

bool GStartScene::CreateInterface()
{
	GStartInterfaceLayer* interfaceLayer = new GStartInterfaceLayer();
	mpTab = (GnITabCtrl*)interfaceLayer->CreateInterface( GInterfaceLayer::UI_START_TAB, &mInputEvent );
	if( mpTab == NULL )
	{
		delete interfaceLayer;
		return false;
	}
	mpTab->SetActiveTab( 1 );
	mpInterfaceLayer = interfaceLayer;
	addChild( interfaceLayer, INTERFACE_ZORDER );
	interfaceLayer->release();
	SetLoadTabButton();
	return true;
}

bool GStartScene::CreateBackground()
{
	GStartBackgroundLayer* backLayer = GStartBackgroundLayer::CreateBackground();
	if( backLayer == NULL )
	{
		return false;
	}
	mpBackgroundLayer = backLayer;
	addChild( backLayer );
	backLayer->release();
	return true;
}

const gchar* GStartScene::GetSceneName()
{
	return SCENENAME_START;
}

void GStartScene::InputEvent(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::PUSHUP )
	{
		GnITabPage* page = mpTab->GetActiveTabPage();
		for( gtuint i = 0 ; i < page->GetChildrenSize() ; i++ )
		{
			GnInterface* tabButton = page->GetChild( i );
			if( pInterface == tabButton )
			{
				if( page->GetNumTabPage() == GInterfaceLayer::eNewTab )
					InputNewTabButton( i );
				else if( page->GetNumTabPage() == GInterfaceLayer::eLoadTab )
					InputLoadTabButton( i );
			}
		}
	}
}

void GStartScene::InputNewTabButton(gtuint uiNumButton)
{
	GPlayingDataManager* playingDataManager = GPlayingDataManager::GetSingleton();
	guint32 curCount = playingDataManager->GetPlayingDataCount();
	if( MAX_PLAYER <= curCount )
		return;
	GPlayingData* data = playingDataManager->CreatePlayingData( uiNumButton );
	playingDataManager->AddPlayingData( data );
	playingDataManager->SaveData();
	playingDataManager->SetPlayingPlayerData( curCount );
	
	GScene::SetChangeSceneName( GScene::SCENENAME_STATE );
}

void GStartScene::InputLoadTabButton(gtuint uiNumButton)
{
	GPlayingDataManager* playingDataManager = GPlayingDataManager::GetSingleton();
	if( playingDataManager->GetPlayingDataCount() > uiNumButton )
	{
		playingDataManager->SetPlayingPlayerData( uiNumButton );
		//GPlayingData* data = playingDataManager->GetPlayingPlayerData();
		
		GScene::SetChangeSceneName( GScene::SCENENAME_STATE );
	}
}

void GStartScene::SetLoadTabButton()
{
	GnITabPage* page = mpTab->GetTabPage( 1 );
	if( page == NULL )
		return;
	
	GPlayingDataManager* playingDataManager = GPlayingDataManager::GetSingleton();
	guint32 dataCount = playingDataManager->GetPlayingDataCount();
	for ( gtuint i = 0 ; i < dataCount ; i++ )
	{
		GPlayingData* data = playingDataManager->GetPlayingData( i );
		GLoadButtonLabel* loadButton = GLoadButtonLabel::CreateLabel( i, data->GetModeLevel()
			,  data->GetLastCrearStage() );
		page->AddChild( loadButton );
	}
}