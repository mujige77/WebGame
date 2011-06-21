//
//  GActorController.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GamePCH.h"
#include "GActorController.h"

GActorController::GActorController()
{
	SetIsDestory( false );
}

bool GActorController::LoadActor(const gchar *pcFilePath)
{
	GnObjectStream stream;
	mpsActor = Gn2DActor::Create( pcFilePath, stream );
	if( mpsActor == NULL )
		return false;
	
	return true;
}

void GActorController::Update(float fDeltaTime)
{
	mpsActor->Update( fDeltaTime );
	mpsActor->GetRootNode()->Update( fDeltaTime );
}