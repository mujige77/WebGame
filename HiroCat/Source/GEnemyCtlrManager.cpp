//
//  GMobManager.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GamePCH.h"
#include "GEnemyCtlrManager.h"
#include "GEnemyController.h"
#include <GFileList.h>

GEnemyCtlrManager::GEnemyCtlrManager(GLayer* pLayer) : GActorCtlrManager(pLayer)
{
	srand(10);
	mNewEnemyTimeEvent.Reset( 2.0f );
}

void GEnemyCtlrManager::Update(float fDeltaTime)
{
	GActorCtlrManager::Update( fDeltaTime );
	
	if( mNewEnemyTimeEvent.UpdateEvent( fDeltaTime ) )
	{
		mNewEnemyTimeEvent.Reset( 50.0f );
		CreateEnemy();
	}
	for ( gtuint i = 0; i < GetActorCtlrSize(); i++ )
	{
		GetActorCtlr( i )->Update( fDeltaTime );
	}
}

void GEnemyCtlrManager::CreateEnemy()
{
	int numID = GetActorIndex( rand() % GetActorIndexSize() );
	const gchar* fileName = GetFileList()->GetEnemyFileName( numID );
	GnAssert( fileName );
	
	std::string fullFileName = GnSystem::GetWorkDirectory();
	fullFileName += fileName;
	fullFileName += "/";
	fullFileName += fileName;
	fullFileName += ".gat";
	
	GEnemyController* controller = GEnemyController::Create( fullFileName.c_str() );
	SetStartPostion(controller, rand() % mNumAccackLine );
	controller->GetActor()->GetRootNode()->GetMesh()->setFlipX(true);
	controller->GetActor()->SetTargetAnimation( 2 );

	AddActorCtlr( controller );
}