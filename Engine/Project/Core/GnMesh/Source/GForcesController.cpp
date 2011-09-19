#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GForcesController.h"
#include "GInfoForcesBasic.h"
#include "GCollectComponentHeader.h"
#include "GActionStand.h"
#include "GActionAttack.h"
#include "GActionDamage.h"
#include "GActionAttackCheck.h"
#include "GActorInfoDatabase.h"
#include "GActionFollows.h"

GForcesController::GForcesController()
{
	
}

GForcesController* GForcesController::Create(const gchar* pcID, guint32 uiLevel)
{
	gstring fullPath;
	GetFullActorFilePath( pcID, fullPath );
	
	GForcesController* controller = GnNew GForcesController();
	if( controller->Init( fullPath.c_str(), pcID, uiLevel ) == false )
	{
		GnDelete controller;
		return NULL;
	}
	return controller;
}

bool GForcesController::InitController()
{
	mCallbackActorEventSlot.Initialize( this, &GForcesController::ActorCallbackFunc );
	GetActor()->SetCallbackEvent( &mCallbackActorEventSlot );
	return true;
}

bool GForcesController::InitInfoCompenent(const gchar* pcID, guint32 uiLevel)
{
	GInfoForcesBasic* pInfo = GnNew GInfoForcesBasic();
	if( pInfo->LoadDataFromSql( pcID, uiLevel, GetActorInfoDatabase()->GetSql() ) == false )
	{
		GnDelete pInfo;
		return  false;
	}
	SetInfoComponent( pInfo->GetInfoType(), pInfo );
	return true;
}

bool GForcesController::InitActionComponents()
{
	GActorController::InitActionComponents();
	
	GInfoForcesBasic* info = (GInfoForcesBasic*)GetInfoComponent( GInfo::INFO_BASIC );
	
	GMainGameMove* moveAction = GnNew GMainGameMove( this );
	SetActionComponent( moveAction->GetActionType(), moveAction );
	moveAction->SetMoveRangeX( info->GetMoveSpeed() );	
	moveAction->SetMoveRight( true );
	
	GActionDamage* damageAction = (GActionDamage*)GetActionComponent( GAction::ACTION_DAMAGE );
	damageAction->SetIsPushDamage( info->GetPush() == 1 );
	damageAction->SetPushDelta( GnVector2( -1.0f, 0.0f) );
	
	GActionFollows* follows = (GActionFollows*)GetActionComponent( GAction::ACTION_FOLLOWS );
	follows->CreateFollow( GActionFollows::eShadow );
	return true;
}

void GForcesController::ActorCallbackFunc(Gn2DActor::TimeEvent* pEvent)
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