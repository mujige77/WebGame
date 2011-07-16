
#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GEnemyController.h"
#include "GInfoEnemyBasic.h"
#include "GCollectComponentHeader.h"
#include "GActionStand.h"
#include "GActionAttack.h"
#include "GActionDamage.h"
#include "GActionAttackCheck.h"

GEnemyController::GEnemyController()
{
	
}

GEnemyController* GEnemyController::Create(const gchar* pcID, guint32 uiLevel)
{
	gstring fullPath;
	GetFullActorFilePath( pcID, fullPath );
	
	GEnemyController* controller = GnNew GEnemyController();
	if( controller->Init( fullPath.c_str(), pcID, uiLevel ) == false )
	{
		GnDelete controller;
		return NULL;
	}
	return controller;
} 

bool GEnemyController::InitController()
{
	mCallbackActorEventSlot.Initialize( this, &GEnemyController::ActorCallbackFunc );
	GetActor()->SetCallbackEvent( &mCallbackActorEventSlot );
	return true;
}

bool GEnemyController::InitInfoCompenent(const gchar* pcID, guint32 uiLevel)
{
	GInfoEnemyBasic* pInfo = GnNew GInfoEnemyBasic();
	if( pInfo->LoadDataFromSql( pcID, uiLevel, GetActorInfoDatabase()->GetSql() ) == false )
	{
		GnDelete pInfo;
		return  false;
	}	SetInfoComponent( pInfo->GetInfoType(), pInfo );
	return true;
}

bool GEnemyController::InitActionComponents()
{
	GInfoEnemyBasic* info = (GInfoEnemyBasic*)GetInfoComponent( GInfo::INFO_BASIC );

	GMainGameMove* moveAction = GnNew GMainGameMove( this );
	SetActionComponent( moveAction->GetActionType(), moveAction );
	moveAction->SetMoveRangeX( info->GetMoveRangeX() );

	GetGameEnvironment()->CreateActorControllerBasicAction( this );
	return true;
}

void GEnemyController::ActorCallbackFunc(Gn2DActor::TimeEvent* pEvent)
{
	GnAssert( pEvent );
	if( pEvent == NULL )
		return;
	
	if( pEvent->GetEventType() == Gn2DActor::TimeEvent::ANIKEY )
	{
		if( pEvent->GetSequenceID() == GAction::ANI_ATTACK )
			SetAttack( pEvent->GetSequenceID() );
		return;
	}
	else if( pEvent->GetEventType() == Gn2DActor::TimeEvent::END_SEQUENCE )
	{
		if( pEvent->GetSequenceID() == GAction::ANI_ATTACK )
			SetEndAttack();
		if( pEvent->GetSequenceID() == GAction::ANI_DIE )
			SetEndDie();
	}
}