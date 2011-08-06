#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GForcesCtlrManager.h"
#include "GForcesController.h"
#include <GFileList.h>
#include "GInterfaceLayer.h"
#include "GCollectComponentHeader.h"

GForcesCtlrManager* GForcesCtlrManager::CreateActorCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer
		, GCastle* pCastle)
{
	GForcesCtlrManager* ctlrManager = GnNew GForcesCtlrManager(pActorLayer, pInterfaceLayer
		, pCastle);
	return ctlrManager;
}

GForcesCtlrManager::GForcesCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer, GCastle* pCastle)
	: GActorCtlrManager( pActorLayer, pCastle ), mpInterfaceLayer( (GInterfaceLayer*)pInterfaceLayer )
	, mCreateForcesInputEvent( this, &GForcesCtlrManager::CreateForces )
{
	
}

void GForcesCtlrManager::Update(float fDeltaTime)
{
	GActorCtlrManager::Update( fDeltaTime );
}

void GForcesCtlrManager::Init()
{
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
		if( mpButtonGroup->GetChild( i ) == pInterface )
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
		GetGameEnvironment()->InitActorControllerAction( GetActorLayer(), controller );
		
		GActionMove* move = (GActionMove*)controller->GetCurrentAction( GAction::ACTION_MOVE );
		move->SetMove( GActionMove::MOVERIGHT );		
		AddActorCtlr( controller );
	}
}