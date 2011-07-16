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
#include "GMainGameEnvironment.h"

GnImplementSingleton(GSceneSelector);

void GSceneSelector::RunApplication()
{
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

	pDirector->setDisplayFPS(true);	

	pDirector->setAnimationInterval(1.0 / 60);	
	
	CreateEnvironment( 1 );
	
	GScene* gameScene = CreateScene( 1 );
	if( gameScene )
		pDirector->runWithScene( gameScene );
	
	mpCurrentScene = gameScene;
	GetGameState()->SetGameScale( 0.7 );
}

GScene* GSceneSelector::CreateScene(gtuint uiStage)
{
	bool success = false;
	GGameScene* scene = new GGameScene();
	do
	{
//		char = GetFullPath( "template.lst" );
//		GnFile* file = GnFile::GetFile( fileName.c_str(), GnFile::READ_ACSII, 256 );
//		if( file == NULL )
//			break;	
		
		if( scene->CreateBackgroundLayer( "./Data/Background/BG_01.png" ) == false )
			break;
		
		if( scene->CreateInterfaceLayer( "./Data/Controll/0_215.png" ) == false )
			break;
		
		if( scene->InitEnvironment() == false )
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
void GSceneSelector::CreateEnvironment(gtuint uiStage)
{
	GMainGameEnvironment::Create();
}
void GSceneSelector::SetUseActorFile()
{
	
}
