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
#include "GActionFollows.h"

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
	mpUseMoveAction = NULL;
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
	GActorController::InitActionComponents();
	
	GInfoForcesBasic* info = (GInfoForcesBasic*)GetInfoComponent( GInfo::INFO_BASIC );
	
	GMainGameMove* moveAction = GnNew GMainGameMove( this );
	SetActionComponent( moveAction->GetActionType(), moveAction );
	moveAction->SetMoveRangeX( info->GetMoveSpeed() );
	moveAction->SetMoveRangeY( info->GetMoveSpeed() );
	moveAction->SetNumLine( 0 );
	
	GActionDamage* damageAction = (GActionDamage*)GetActionComponent( GAction::ACTION_DAMAGE );
	damageAction->SetIsPushDamage( true );
	damageAction->SetPushDelta( GnVector2( -1.0f, 0.0f) );
	
	GActionFollows* follows = (GActionFollows*)GetActionComponent( GAction::ACTION_FOLLOWS );
	follows->CreateFollow( GActionFollows::eShadow );
	return true;
}

void GUserController::Start()
{
	GActorController::Start();
	RemoveAllCurrentAction();
	SetStartAction();
}

void GUserController::SetStartAction()
{
	if( mpUseMoveAction )
		AddCurrentAction( mpUseMoveAction );
	else
		AddCurrentAction( GetActionComponent( GAction::ACTION_STAND ) );
	
	AddCurrentAction( GetActionComponent( GAction::ACTION_FOLLOWS ) );
}

void GUserController::RemoveCurrentAction(gtuint uiIndex)
{
	if( uiIndex == GAction::ACTION_MOVE )
		mpUseMoveAction = NULL;
	GActorController::RemoveCurrentAction( uiIndex );
}

void GUserController::RemoveAllCurrentAction()
{
	GAction* move  = GetCurrentAction( GAction::ACTION_MOVE );
	GActorController::RemoveAllCurrentAction();
	
	mpUseMoveAction = move;
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
	GAction* damage = GetCurrentAction( GAction::ACTION_DAMAGE );
	if( damage || move )
	{
		GnVector2 movePos = GetPosition() + GetMoveDeltaPosition();
		//GnVector2& movePos = GetMovePosition();
		bool moveX = GetGameEnvironment()->CorrectMoveX( movePos.x, GetActor()->GetRootNode()->GetFlipX(), true );
		bool moveY = GetGameEnvironment()->CorrectMoveY( movePos.y );
		if( moveX == false && moveY == false )
		{
			GetGameEnvironment()->RemoveBasicCurrentAction( this );
			AddCurrentAction( GetActionComponent( GAction::ACTION_STAND ) );
			if( GetCurrentAction( GAction::ACTION_ATTACKCHECK ) == NULL )
				AddCurrentAction( GetActionComponent( GAction::ACTION_ATTACKCHECK ) );
		}
		RemoveCurrentAction( GAction::ACTION_ATTACK );
		RemoveCurrentAction( GAction::ACTION_ATTACKCHECK );
		SetPosition( movePos );
		SetMoveDeltaPosition( GnVector2( 0.0f, 0.0f ) );
	}
	else if( damage == NULL )
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
//	else
//	{
//		GnVector2 movePos = GetPosition() + GetMoveDeltaPosition();
//		SetPosition( movePos );
//		SetMoveDeltaPosition( GnVector2( 0.0f, 0.0f ) );
//	}
}