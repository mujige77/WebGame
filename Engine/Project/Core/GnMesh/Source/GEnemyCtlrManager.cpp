#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GEnemyCtlrManager.h"
#include "GEnemyController.h"
#include "GActionMove.h"
#include <GFileList.h>

GEnemyCtlrManager::GEnemyCtlrManager(GLayer* pLayer) : GActorCtlrManager( pLayer )
{
	srand( 10000 );
	mNewEnemyTimeEvent.Reset( 1.0f );
}

void GEnemyCtlrManager::Update(float fDeltaTime)
{
	GActorCtlrManager::Update( fDeltaTime );
	
	if( mNewEnemyTimeEvent.UpdateEvent( fDeltaTime ) )
	{
		mNewEnemyTimeEvent.Reset( 10.0f );
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
	GActionMove* move = (GActionMove*)controller->GetCurrentAction( GAction::ACTION_MOVE );
	move->SetMove(GActionMove::MOVELEFT, true);
	move->SetActorLayer( GetActorLayer() );
	
//	Gn2DSequence* attackSequence = NULL;
//	GnVerify( controller->GetActor()->GetSequence( GAction::ACTION_ATTACK
//		, attackSequence ) );
//	Gn2DAVData* avData = attackSequence->GetAVData();
//	if( avData->GetCollisionCount() <= 1 )
//	{
//		avData->FlipX( true, controller->GetMesh()->GetOriginalPosition().x );
//	}

	
	AddActorCtlr( controller );
	
#ifdef GNDEBUG
	GnSingleDrawPrimitiveslayer* pLayer = new GnSingleDrawPrimitiveslayer();
	pLayer->GetDrawObject()->SetController( controller );
	GetActorLayer()->addChild( pLayer, 500 );
#endif
}