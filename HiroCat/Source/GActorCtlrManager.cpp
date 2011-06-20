//
//  GActorCtlrManager.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GamePCH.h"
#include "GActorCtlrManager.h"

GActorCtlrManager::GActorCtlrManager(GLayer* pLayer) : mpActorLayer(pLayer)
{
}

GActorCtlrManager::~GActorCtlrManager()
{
}

void GActorCtlrManager::Update(float fDeltaTime)
{
	for( gtuint i = 0; i < mActors.GetSize(); i++ )
	{
		GActorController* actorCtlr = mActors.GetAt( i );
		if( actorCtlr->IsDestory() )
		{
			mActors.RemoveAtAndFill( i );
			--i;
			GnDelete actorCtlr;
		}
		else
		{
			actorCtlr->Update( fDeltaTime );
		}
	}
}

void GActorCtlrManager::SetStartPostion(GActorController* pActorController
	, gtuint uiAttackLine)
{
	if( uiAttackLine == 0  )
	{
		pActorController->GetMesh()->SetPosition( GetStartActorPostion() );
	}
	else
	{
		GnVector2 postion = GetStartActorPostion();
		postion.y += 20.0f;
		pActorController->GetMesh()->SetPosition( postion );
	}
}