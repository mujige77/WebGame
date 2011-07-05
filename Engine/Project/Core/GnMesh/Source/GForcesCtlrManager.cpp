//
//  GForcesCtlrManager.cpp
//  Core
//
//  Created by Max Yoon on 11. 6. 26..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GForcesCtlrManager.h"
#include "GForcesController.h"
#include <GFileList.h>
#include "GnInterfaceGroup.h"
#include "GInterfaceLayer.h"
#include "GCollectComponentHeader.h"

GForcesCtlrManager::GForcesCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer)
	: GActorCtlrManager( pActorLayer ), mpInterfaceLayer( (GInterfaceLayer*)pInterfaceLayer )
{
	
}

void GForcesCtlrManager::Update(float fDeltaTime)
{
	GActorCtlrManager::Update( fDeltaTime );
}

void GForcesCtlrManager::Init()
{
	mCreateForcesInputEvent.Initialize( this, &GForcesCtlrManager::CreateForces );
	mpButtonGroup = mpInterfaceLayer->CreateInterface( (gtuint)GInterfaceLayer::UI_MAIN_FORCESBUTTONS,
		&mCreateForcesInputEvent );
}

void GForcesCtlrManager::CreateForces(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() != GnIInputEvent::PUSH )
		return;
	
	const gchar* idName = NULL;
	for ( gtuint i = 0; i < GInterfaceLayer::FORCESBT_NUM; i++ )
	{
		if( mpButtonGroup->GetChild( i )  == pInterface )
		{
			gtuint numID = GetActorIndex( i );
			idName = GetFileList()->GetForcesFileName( numID );
			GnAssert( idName );
			if( idName == NULL )
				return;
			break;
		}
	}
	
	GForcesController* controller = GForcesController::Create( idName, 1 );
	if( controller )
	{
		GetGameEnvironment()->SetStartPositionToActor( controller, 0 );
		GActionMove* move = (GActionMove*)controller->GetCurrentAction( GAction::ACTION_MOVE );
		move->SetMove(GActionMove::MOVERIGHT, true);
		move->SetActorLayer( GetActorLayer() );
		AddActorCtlr( controller );
		
#ifdef GNDEBUG
		GnSingleDrawPrimitiveslayer* pLayer = new GnSingleDrawPrimitiveslayer();
		pLayer->GetDrawObject()->SetController( controller );
		GetActorLayer()->addChild( pLayer, 500 );
#endif
	}
}