//
//  GBackgroundSelcetor.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GamePCH.h"
#include "GSceneSelector.h"
#include "GBackgroundLayer.h"
#include "GGameScene.h"
#include "GFileLIst.h"

GnImplementSingleton(GSceneSelector);

void GSceneSelector::RunApplication()
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

	pDirector->setDisplayFPS(true);	

	pDirector->setAnimationInterval(1.0 / 60);	
	
	GScene* gameScene = CreateScene( 1 );
	if( gameScene )
		pDirector->runWithScene( gameScene );
	mpCurrentScene = gameScene;
}

GScene* GSceneSelector::CreateScene(gtuint uiStage)
{
	bool success = false;
	GGameScene* scene = new GGameScene();
	
	do
	{
		if( scene->CreateBackgroundLayer( "./Data/Background/BG_01.png" ) == false )
			break;
		
		if( scene->CreateInterfaceLayer( "./Data/Background/interface_3GS.png" ) == false )
			break;
		
		if( scene->CreateActorLayer() == false )
			break;

		success = true;
		
	}while(false);
	

	
	if( success == false )
	{
		delete scene;
		return NULL;
	}
	return scene;
}

void GSceneSelector::SetUseActorFile()
{
	
}
