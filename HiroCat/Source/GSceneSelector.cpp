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
#include "GLoadingScene.h"
#include "GOpeningScene.h"

GnImplementSingleton(GSceneSelector);

GSceneSelector::GSceneSelector() : mpCurrentScene( NULL ), mpStartScene( NULL ), mpStateScene( NULL )
, mpSelectStageScene( NULL ), mpGameScene( NULL ), mPlayOpening( false ), mpLoadingScene( NULL )
{
	
}

void GSceneSelector::RunApplication()
{
	GnSrand( time( 0 ) );
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

	pDirector->setDisplayFPS(true);	

	pDirector->setAnimationInterval(1.0 / 60);	
	
	
	CreatePlayingData();
	
	GScene* gameScene = CreateStartScene();
	if( gameScene )
		pDirector->runWithScene( gameScene );

	SetCurrentScene( gameScene );
	
	CCDirector::sharedDirector()->setDisplayFPS(false);
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
			if( mpLoadingScene == NULL )
			{
				SetLoadingScene();
				return;
			}
			ReleaseScene();
			changeScene = CreateStartScene();
		}
		else if( changeName == GScene::SCENENAME_STATE )
		{
			if( mPlayOpening )
			{
				mPlayOpening = false;
				CCScene* openingScene = GOpeningScene::CreateLoadingScene( 0 );
				if( openingScene )
				{
					pDirector->replaceScene( openingScene );
					changeName.clear();
				}
				return;
			}			
			else if( mpCurrentScene->GetSceneName() == GScene::SCENENAME_SELECTSTAGE )
			{
				if( mpStateScene )
					changeScene = mpStateScene;
				else
					changeScene = CreateStateScene();
			}
			else
			{
//				if( mpCurrentScene->GetSceneName() == GScene::SCENENAME_GAME )
//				{
//					if( mpGameScene->IsWinGame() )
//					{
//						GPlayingData* playing = GPlayingDataManager::GetSingleton()->GetPlayingPlayerData();
//						GPlayingData::ModeInfo& info = playing->GetCurrentModeInfo();
//						info.mLastClearStage += 1;
//						GPlayingDataManager::GetSingleton()->SaveData();
//					}
//				}
				if( mpLoadingScene == NULL )
				{
					SetLoadingScene();
					return;
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
				if( mpLoadingScene == NULL )
				{
					SetLoadingScene();
					return;
				}
				ReleaseScene();
				changeScene = CreateSelectStageScene();
			}
		}
		else if( changeName == GScene::SCENENAME_GAME )
		{
			if( mpLoadingScene == NULL )
			{
				SetLoadingScene();
				return;
			}
			ReleaseScene();
			changeScene = CreateGameScene();
		}
		
		SetCurrentScene( changeScene );
		if( changeScene )
			pDirector->replaceScene( changeScene );
		mpLoadingScene = NULL;
		changeName.clear();
	}
}

void GSceneSelector::SetLoadingScene()
{
	mpLoadingScene = GLoadingScene::CreateLoadingScene();
	CCDirector* pDirector = CCDirector::sharedDirector();
	if( mpLoadingScene )
		pDirector->replaceScene( mpLoadingScene );
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
	mpSelectStageScene = GSelectStageScene::CreateScene( playData->GetCurrentModeInfo().mLastClearStage );
	
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
	
	CCTextureCache::sharedTextureCache()->removeAllTextures();
}
void GSceneSelector::SetCurrentScene(GScene* pScene)
{
	mpCurrentScene = pScene;
	GScene::SetCurrentScene( pScene );
}

void GSceneSelector::CreatePlayingData()
{
	gstring fullPath;
	GetWriteablePath( USER_HAVEDATA_FILENAME, fullPath );
	if( GnFileUtil::ExitsFile( fullPath.c_str() ) == false )
	{
		GnVerify( GnFileUtil::FileCopy( GetFullPath( USER_HAVEDATA_FILENAME ), fullPath.c_str() ) );
		mPlayOpening = true;
	}
	
	GPlayingDataManager* playingDataManager = GPlayingDataManager::GetSingleton();
	playingDataManager->LoadData();
	
	guint32 curCount = playingDataManager->GetPlayingDataCount();
	GPlayingData* data = NULL;
	if( curCount == 0 )
	{
		data = playingDataManager->CreatePlayingData();
		playingDataManager->AddPlayingData( data );
		playingDataManager->SaveData();
	}
	else
		data = playingDataManager->GetPlayingData( 0 );
	
	playingDataManager->SetPlayingPlayerData( 0 );
}