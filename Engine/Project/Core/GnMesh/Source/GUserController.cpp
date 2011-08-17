#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GUserController.h"
#include "GInfoForcesBasic.h"
#include "GCollectComponentHeader.h"
#include "GActionStand.h"
#include "GActionAttack.h"
#include "GActionDamage.h"
#include "GActionAttackCheck.h"
#include "GActorInfoDatabase.h"

GUserController* GUserController::Create(const gchar* pcID, guint32 uiLevel)
{
	gstring fullPath;
	GetFullActorFilePath( pcID, fullPath );
	
	GUserController* controller = GnNew GUserController();
	if( controller->Init( fullPath.c_str(), pcID, uiLevel ) == false )
	{
		GnDelete controller;
		return NULL;
	}
	return controller;
}

bool GUserController::InitController()
{
	mCallbackActorEventSlot.Initialize( this, &GUserController::ActorCallbackFunc );
	GetActor()->SetCallbackEvent( &mCallbackActorEventSlot );
	return true;
}

bool GUserController::InitInfoCompenent(const gchar* pcID, guint32 uiLevel)
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

bool GUserController::InitActionComponents()
{
	GInfoForcesBasic* info = (GInfoForcesBasic*)GetInfoComponent( GInfo::INFO_BASIC );
	
	GMainGameMove* moveAction = GnNew GMainGameMove( this );
	SetActionComponent( moveAction->GetActionType(), moveAction );
	moveAction->SetMoveRangeX( info->GetMoveSpeed() );
	moveAction->SetMoveRangeY( info->GetMoveSpeed() );
	moveAction->SetNumLine( 0 );
	return true;
}

void GUserController::Start()
{
	GActorController::Start();
	RemoveAllCurrentAction();
	AddCurrentAction( GetActionComponent( GAction::ACTION_STAND ) );
}

void GUserController::ActorCallbackFunc(Gn2DActor::TimeEvent* pEvent)
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

void GUserController::MoveStopCheck()
{
	GAction* move = GetCurrentAction( GAction::ACTION_MOVE );
	if( move )
	{
		GnVector2& movePos = GetMovePosition();
		bool moveX = GetGameEnvironment()->CorrectMoveX( movePos.x );
		bool moveY = GetGameEnvironment()->CorrectMoveY( movePos.y );
		if( moveX == false && moveY == false )
		{
			GetGameEnvironment()->RemoveBasicCurrentAction( this );
			AddCurrentAction( GetActionComponent( GAction::ACTION_STAND ) );
			if( GetCurrentAction( GAction::ACTION_ATTACKCHECK ) == NULL )
				AddCurrentAction( GetActionComponent( GAction::ACTION_ATTACKCHECK ) );
		}
		SetPosition( GetMovePosition() );
	}
	else
	{
		GActionAttackCheck* attackCheck = (GActionAttackCheck*)GetActionComponent( GAction::ACTION_ATTACKCHECK );
		if( attackCheck && attackCheck->IsReadyAttack() )
		{
			GetGameEnvironment()->RemoveBasicCurrentAction( this );
			AddCurrentAction( GetActionComponent( GAction::ACTION_ATTACK ) );
			return;
		}
		
		if( GetCurrentAction( GAction::ACTION_ATTACKCHECK ) == NULL )
			AddCurrentAction( GetActionComponent( GAction::ACTION_ATTACKCHECK ) );
	}
}