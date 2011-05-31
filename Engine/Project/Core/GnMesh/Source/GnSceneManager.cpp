#include "GnMeshPCH.h"
#include "GnSceneManager.h"
#include "GnLayerMain.h"

GnSceneManager* GnSceneManager::mpSingleton = NULL;

GnSceneManager* GnSceneManager::GetSingleton()
{
	return mpSingleton;
}

void GnSceneManager::_StartupEBM()
{
	mpSingleton = new GnSceneManager;
}

void GnSceneManager::_ShutdownEBM()
{
	delete mpSingleton;
}

GnSceneManager::~GnSceneManager()
{
	if( mpMain )
		mpMain->release();
}

GnCocosScene* GnSceneManager::CreateMainGameScene()
{
	GnLayerMain* state = new GnLayerMain();
	mpMain = GnCocosScene::CreateScene( 0, state, false );
	return mpMain;
}

GnCocosScene* GnSceneManager::GetMainGameScene()
{
	if( mpMain == NULL )
		GnVerify( CreateMainGameScene() );

	return mpMain;
}

GnLayer* GnSceneManager::GetMainGameLayer()
{
	if( mpMain == NULL )
		GnVerify( CreateMainGameScene() );

	return mpMain->GetLayer();
}

GnSceneManager::GnSceneManager() : mpMain(NULL)
{
}