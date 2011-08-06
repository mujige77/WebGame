#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GEnemyCtlrManager.h"
#include "GEnemyController.h"
#include "GActionMove.h"
#include <GFileList.h>

GEnemyCtlrManager* GEnemyCtlrManager::CreateActorCtlrManager(GLayer* pLayer, GCastle* pCastle)
{
	GEnemyCtlrManager* ctlrManager = GnNew GEnemyCtlrManager( pLayer, pCastle );
	return ctlrManager;
}

GEnemyCtlrManager::GEnemyCtlrManager(GLayer* pLayer, GCastle* pCastle) : GActorCtlrManager( pLayer, pCastle )
{
	srand( 10000 );
	mNewEnemyTimeEvent.Reset( 1.0f );
}

void GEnemyCtlrManager::Update(float fDeltaTime)
{
	GActorCtlrManager::Update( fDeltaTime );
	
	if( mNewEnemyTimeEvent.UpdateEvent( fDeltaTime ) )
	{
		mNewEnemyTimeEvent.Reset( 5.0f );
		CreateEnemy();
	}
}

void GEnemyCtlrManager::CreateEnemy()
{
	int numID = GetActorIndex( rand() % GetActorIndexSize() );
	const gchar* idName = GetFileList()->GetEnemyFileName( numID );
	GnAssert( idName );
	
	
	GEnemyController* controller = GEnemyController::Create( idName, 1 );
	GetGameEnvironment()->SetStartPositionToActor( controller, 1 );
	GetGameEnvironment()->InitActorControllerAction( GetActorLayer(), controller );
	
	GActionMove* move = (GActionMove*)controller->GetCurrentAction( GAction::ACTION_MOVE );
	move->SetMove( GActionMove::MOVELEFT );
		
//	Gn2DSequence* attackSequence = NULL;
//	GnVerify( controller->GetActor()->GetSequence( GAction::ACTION_ATTACK
//		, attackSequence ) );
//	Gn2DAVData* avData = attackSequence->GetAVData();
//	if( avData->GetCollisionCount() <= 1 )
//	{
//		avData->FlipX( true, controller->GetMesh()->GetOriginalPosition().x );
//	}

	
	AddActorCtlr( controller );
}