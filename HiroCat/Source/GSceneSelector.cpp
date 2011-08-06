#include "GamePCH.h"
#include "GSceneSelector.h"
#include "GBackgroundLayer.h"
#include "GFileLIst.h"
#include "GMainGameEnvironment.h"
#include "GGameScene.h"
#include "GStartScene.h"
#include "GSelectStageScene.h"
#include "GStateScene.h"
#include "GPlayingDataManager.h"

GnImplementSingleton(GSceneSelector);

GSceneSelector::GSceneSelector() : mpCurrentScene( NULL ), mpStartScene( NULL ), mpStateScene( NULL )
	, mpSelectStageScene( NULL ), mpGameScene( NULL )
{
	
}

void GSceneSelector::RunApplication()
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

	pDirector->setDisplayFPS(true);	

	pDirector->setAnimationInterval(1.0 / 60);	
	
	GPlayingDataManager::GetSingleton()->LoadData();
	
	GScene* gameScene = CreateStartScene();
	if( gameScene )
		pDirector->runWithScene( gameScene );
	mpCurrentScene = gameScene;

//	GScene* gameScene = CreateStateScene();
//	if( gameScene )
//		pDirector->runWithScene( gameScene );
//	mpCurrentScene = gameScene;
	
//	GScene* gameScene = CreateSelectStageScene();
//	if( gameScene )
//		pDirector->runWithScene( gameScene );
//	mpCurrentScene = gameScene;
	
//	GScene* gameScene = CreateGameScene( 1 );
//	if( gameScene )
//		pDirector->runWithScene( gameScene );
//	mpCurrentScene = gameScene;
}

void GSceneSelector::Update(float fTime)
{
	ChangeSceneCheck();
	if( mpCurrentScene )
		mpCurrentScene->Update( fTime );
}

void GSceneSelector::ChangeSceneCheck()
{
	gstring& changeName = GScene::GetChangeSceneName();
	if( changeName.empty() == false )
	{
		CCDirector* pDirector = CCDirector::sharedDirector();
		GScene* changeScene = NULL;
		if( changeName == GScene::SCENENAME_START )
		{
			ReleaseScene();
			changeScene = CreateStartScene();
		}
		else if( changeName == GScene::SCENENAME_STATE )
		{
			if( mpCurrentScene->GetSceneName() == GScene::SCENENAME_SELECTSTAGE )
			{
				if( mpStateScene )
					changeScene = mpStateScene;
				else
					changeScene = CreateStateScene();
			}
			else
			{
				if( mpCurrentScene->GetSceneName() == GScene::SCENENAME_GAME )
				{
					if( mpGameScene->IsWinGame() )
					{
						GPlayingData* playing = GPlayingDataManager::GetSingleton()->GetPlayingPlayerData();
						playing->SetLastCrearStage( playing->GetLastCrearStage() + 1 );
						GPlayingDataManager::GetSingleton()->SaveData();
					}
				}
				ReleaseScene();
				changeScene = CreateStateScene();
			}
		}
		else if( changeName == GScene::SCENENAME_SELECTSTAGE )
		{
			
			if( mpCurrentScene->GetSceneName() == GScene::SCENENAME_STATE )
			{
				if( mpSelectStageScene )
					changeScene = mpSelectStageScene;
				else
					changeScene = CreateSelectStageScene();
			}
			else
			{
				ReleaseScene();
				changeScene = CreateSelectStageScene();
			}
		}
		else if( changeName == GScene::SCENENAME_GAME )
		{
			ReleaseScene();
			changeScene = CreateGameScene();
		}
		
		mpCurrentScene = changeScene;
		if( changeScene )
			pDirector->replaceScene( changeScene );
		changeName.clear();
	}
}

GScene* GSceneSelector::CreateGameScene()
{
	bool success = false;
	mpGameScene = new GGameScene();
	do
	{
		if( mpGameScene->CreateScene( GetGameEnvironment()->GetStageInfo() ) == false )
			break;
		
		if( mpGameScene->InitEnvironment() == false )
			break;
		
		if( mpGameScene->CreateActorManager() == false )
			break;
		
		success = true;
		
	}while(false);
	

	GetGameState()->SetGameScale( 0.7 );

	if( success == false )
	{
		delete mpGameScene;
		mpGameScene = NULL;
		return NULL;
	}
	return mpGameScene;
}

GScene* GSceneSelector::CreateStartScene()
{
	mpStartScene = GStartScene::CreateStartScene();

	if( mpStartScene == NULL)
		return NULL;
		
	return mpStartScene;	
}

GScene* GSceneSelector::CreateStateScene()
{
	mpStateScene = GStateScene::CreateScene();
	
	if( mpStateScene == NULL)
		return NULL;
	
	return mpStateScene;	
}


GScene* GSceneSelector::CreateSelectStageScene()
{
	GPlayingData* playData = GPlayingDataManager::GetSingleton()->GetPlayingPlayerData();
	mpSelectStageScene = GSelectStageScene::CreateScene( playData->GetLastCrearStage() );
	
	if( mpSelectStageScene == NULL)
		return NULL;
	
	return mpSelectStageScene;	
}

void GSceneSelector::SetUseActorFile()
{
	
}

void GSceneSelector::ReleaseScene()
{
	if( mpCurrentScene == NULL )
		return;
	
	if( mpStartScene )
	{
		mpStartScene->release();
		mpStartScene = NULL;
	}
	if( mpStateScene )
	{
		mpStateScene->release();
		mpStateScene = NULL;
	}
	if( mpSelectStageScene )
	{
		mpSelectStageScene->release();
		mpSelectStageScene = NULL;
	}
	if( mpGameScene )
	{
		mpGameScene->release();
		mpGameScene = NULL;
		GetGameState()->SetGameScale( 1.0 );
	}

	
//	if( mpStartScene && mpCurrentScene->GetSceneName() == mpStartScene->GetSceneName() )
//		mpStartScene = NULL;
//	if( mpStateScene && mpCurrentScene->GetSceneName() == mpStateScene->GetSceneName() )
//		mpStateScene = NULL;
//	if( mpSelectStageScene && mpCurrentScene->GetSceneName() == mpSelectStageScene->GetSceneName() )
//		mpSelectStageScene = NULL;
//	if( mpGameScene && mpCurrentScene->GetSceneName() == mpGameScene->GetSceneName() )
//		mpGameScene = NULL;
//	mpCurrentScene->release();
	
}