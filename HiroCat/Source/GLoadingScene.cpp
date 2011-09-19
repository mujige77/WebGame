#include "GamePCH.h"
#include "GLoadingScene.h"


GLoadingLayer* GLoadingLayer::CreateLoadingLayer(guint32 uiLoadingBgIndex)
{
	float width = GetGameState()->GetGameWidth();
	float height = GetGameState()->GetGameHeight();
	
	GLoadingLayer* loadingLayer = new GLoadingLayer();
	
	gchar fileName[GN_MAX_PATH] = { 0, };
	GnSprintf( fileName, sizeof( fileName ), "loading%d.png", uiLoadingBgIndex );
	gstring fullFileName;
	GetFullPathFromWorkPath( fileName, fullFileName );
	CCSprite* bg = CCSprite::spriteWithFile( fullFileName.c_str() );
	bg->setPosition( CCPointMake( width / 2, height / 2 ) );
	loadingLayer->addChild( bg );
	
	return loadingLayer;
}

GLoadingScene* GLoadingScene::CreateLoadingScene()
{
	GLoadingScene* loadingScene = new GLoadingScene();
	
	GLoadingLayer* loadingLayer = GLoadingLayer::CreateLoadingLayer( ( GnRand() % 3 ) + 1 );	
											 
	loadingScene->addChild( loadingLayer );
	loadingLayer->release();	
	
	return loadingScene;
}
