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
	mpInterfaceLayer = interfaceLayer;
	addChild( interfaceLayer, INTERFACE_ZORDER );
	interfaceLayer->release();
	SetSelectModeTabButton();
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
			if( pInterface->GetTegID() != -1 && pInterface == tabButton )
			{
				if( page->GetNumTabPage() == GInterfaceLayer::eSelectModeTab )
					InputSelectModeTabButton( pInterface->GetTegID() );
				else if( page->GetNumTabPage() == GInterfaceLayer::eOptionTab )
					InputLoadTabButton( pInterface->GetTegID() );
			}
		}
	}
}

void GStartScene::InputSelectModeTabButton(gtuint uiNumButton)
{
	GPlayingDataManager* playingDataManager = GPlayingDataManager::GetSingleton();
	GPlayingData* data = playingDataManager->GetPlayingPlayerData();
	data->SetCurrentMode( (eModeLevel)uiNumButton );
	GScene::SetChangeSceneName( GScene::SCENENAME_STATE );
}

void GStartScene::InputLoadTabButton(gtuint uiNumButton)
{
//	GPlayingDataManager* playingDataManager = GPlayingDataManager::GetSingleton();
//	if( playingDataManager->GetPlayingDataCount() > uiNumButton )
//	{
//		playingDataManager->SetPlayingPlayerData( uiNumButton );
//		//GPlayingData* data = playingDataManager->GetPlayingPlayerData();
//		
//		GScene::SetChangeSceneName( GScene::SCENENAME_STATE );
//	}
}

void GStartScene::SetSelectModeTabButton()
{
	GnITabPage* page = mpTab->GetTabPage( 0 );
	if( page == NULL )
		return;
	
	GPlayingDataManager* playingDataManager = GPlayingDataManager::GetSingleton();
	GPlayingData* data = playingDataManager->GetPlayingPlayerData();
	for (gtuint i = 0 ; i < eMaxMode ; i++ )
	{
		GPlayingData::ModeInfo& modeInfo = data->GetModeInfo( (eModeLevel)i );
		GLoadButtonLabel* loadButton = GLoadButtonLabel::CreateLabel( i, modeInfo.mModeLevel
			,  modeInfo.mLastClearStage );
		page->AddChild( loadButton );
	}
}