#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GActorController.h"
#include "GAction.h"
#include "GInfoBasic.h"
#include "GActionAttack.h"
#include "GActionAttackCheck.h"
#include "GActionDie.h"
#include "GActionGage.h"

void GActorController::GetFullActorFilePath(const gchar* pcID, gstring& pcOutPath)
{
	pcOutPath = GnSystem::GetWorkDirectory();
	pcOutPath += "Actor/";
	pcOutPath += pcID;
	pcOutPath += "/";
	pcOutPath += pcID;
	pcOutPath += ".gat";
}

GActorController::GActorController()
{
}

GActorController::~GActorController()
{
	RemoveAllInfoComponets();
	RemoveAllActionComponets();
}

bool GActorController::Init(const gchar* pcActorFilePath, const gchar* pcID, guint32 uiLevel)
{
	SetIsDestory( false );
	mInfoComponents.SetSize( GInfo::INFO_MAX );
	mActionComponents.SetSize( GAction::ACTION_MAX );
	mCurrentActions.SetSize( GAction::ACTION_MAX );
	
	if( LoadActor( pcActorFilePath ) == false )
		return false ;
	
	if( InitController() == false )
		return false;
	
	if( InitInfoCompenent( pcID, uiLevel ) == false )
		return false;
	
	if( InitActionComponents() == false )
		return false;
	
	return true;
}

void GActorController::Update(float fDeltaTime)
{	
	for( gtuint i = 0 ; i < mCurrentActions.GetSize() ; i++ )
	{
		GAction* action = mCurrentActions.GetAt( i );
		if( action )
		{
			action->Update( fDeltaTime );
			if( action->IsStopAction() )
				RemoveCurrentAction( action->GetActionType() );
		}		
	}

	MoveStopCheck();
	
	mpsActor->Update( fDeltaTime );
	mpsActor->GetRootNode()->Update( fDeltaTime );
}

void GActorController::RemoveAllInfoComponets()
{
	for ( gtuint i = 0; i < mInfoComponents.GetSize(); i++ )
	{
		GInfo* info = mInfoComponents.GetAt( i );
		if( info )
			GnDelete info;
	}
	mInfoComponents.RemoveAll();
}

void GActorController::RemoveAllActionComponets()
{
	for ( gtuint i = 0; i < mActionComponents.GetSize(); i++ )
	{
		GAction* action = mActionComponents.GetAt( i );
		if( action )
			GnDelete action;
	}
	mActionComponents.RemoveAll();
}

bool GActorController::IsEnableMove()
{
	for ( gtuint i = 0; i < mCurrentActions.GetSize(); i++ )
	{
		GAction* action = mCurrentActions.GetAt( i );
		if( action && action->IsEnableMove() == false )
			return false;
	}
	return true;
}

void GActorController::AddCurrentAction(GAction* pComponent)
{
	pComponent->AttachActionToController();
	mCurrentActions.SetAt( pComponent->GetActionType(), pComponent );
}

void GActorController::RemoveCurrentAction(gtuint uiIndex)
{
	GAction* action = mCurrentActions.GetAt( uiIndex );
	if( action )
		action->DetachActionToController();
	mCurrentActions.SetAt( uiIndex, NULL );
}

void GActorController::RemoveAllCurrentAction()
{
	for( gtuint i = 0; i < mCurrentActions.GetSize(); i++ )
	{
		RemoveCurrentAction( i );
	}
}

void GActorController::ReceiveAttack(GActorController* pFromActor)
{
	GInfoBasic* fromActorBasic = (GInfoBasic*)pFromActor->GetInfoComponent( GInfo::INFO_BASIC );
	mCurrentInfo.SetHP( mCurrentInfo.GetHP() - (gint32)fromActorBasic->GetStrength() );
	if( mCurrentInfo.GetHP() > 0 )
	{
		GAction* damage = GetCurrentAction( GAction::ACTION_DAMAGE );
		if( damage )
			return;
		damage = GetActionComponent( GAction::ACTION_DAMAGE );
		GnAssert( damage );
		if( damage )
			AddCurrentAction( damage );

		GActionGage* gage = (GActionGage*)GetCurrentAction( GAction::ACTION_GAGE );
		if( gage == NULL )
		{
			gage = (GActionGage*)GetActionComponent( GAction::ACTION_GAGE );
			GnAssert( gage );
			if( gage )
				AddCurrentAction( gage );
		}
		GInfoBasic* thisInfo = (GInfoBasic*)GetInfoComponent( GInfo::INFO_BASIC );
		gage->SetGagePercent( (float)GetCurrentInfo()->GetHP() / (float)thisInfo->GetHP() * 100.0f );
	}
	else
	{
		RemoveAllCurrentAction();
		AddCurrentAction( GetActionComponent( GAction::ACTION_DIE ) );
	}
}

void GActorController::Start()
{
	GInfoBasic* basic = (GInfoBasic*)GetInfoComponent( GInfo::INFO_BASIC );
	mCurrentInfo.SetHP( basic->GetHP() );
	
	AddCurrentAction( GetActionComponent( GAction::ACTION_MOVE ) );
	AddCurrentAction( GetActionComponent( GAction::ACTION_ATTACKCHECK ) );
}

bool GActorController::LoadActor(const gchar *pcFilePath)
{
	GnObjectStream stream;
	mpsActor = Gn2DActor::Create( pcFilePath, stream );
	if( mpsActor == NULL )
		return false;
	
	return true;
}

void GActorController::SetAttack(guint32 uiSequenceID)
{
	GActionAttackCheck* attackCheck = (GActionAttackCheck*)GetCurrentAction( GAction::ACTION_ATTACKCHECK );
	if( attackCheck == NULL )
		return;

	attackCheck->SetIsEnableAttack( true );
}

void GActorController::SetEndAttack()
{
	GAction* action = GetCurrentAction( GAction::ACTION_DIE );
	if( action )
		return;
	
	GetGameEnvironment()->RemoveBasicCurrentAction( this );
	action = GetActionComponent( GAction::ACTION_STAND );
	AddCurrentAction( action );
	action = GetActionComponent( GAction::ACTION_ATTACKCHECK );
	AddCurrentAction( action );
}

void GActorController::SetEndDie()
{

}

void GActorController::MoveStopCheck()
{
	GActionAttackCheck* attackCheck = (GActionAttackCheck*)GetActionComponent( GAction::ACTION_ATTACKCHECK );
	if( attackCheck && attackCheck->IsReadyAttack() )
	{
		GetGameEnvironment()->RemoveBasicCurrentAction( this );
		AddCurrentAction( GetActionComponent( GAction::ACTION_ATTACK ) );
		return;
	}
	
	GAction* move = GetCurrentAction( GAction::ACTION_MOVE );
	if( move )
	{
		if( GetGameEnvironment()->CorrectMoveX( GetMovePosition().x ) == false )
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
		GAction* action = GetCurrentAction( GAction::ACTION_STAND );
		if( action && GetGameEnvironment()->CorrectMoveX( GetMovePosition().x ) )
		{
			AddCurrentAction( GetActionComponent( GAction::ACTION_MOVE ) );
			if( GetCurrentAction( GAction::ACTION_ATTACKCHECK ) == NULL )
				AddCurrentAction( GetActionComponent( GAction::ACTION_ATTACKCHECK ) );
		}
	}
}

void GActorController::CallbackTimeEvent(Gn2DActor::TimeEvent* pTimeEvent)
{
	if( pTimeEvent->GetEventType() == Gn2DActor::TimeEvent::END_SEQUENCE )
	{
		if( pTimeEvent->GetSequenceID() == GAction::ANI_ATTACK )
		{
			GetGameEnvironment()->RemoveBasicCurrentAction( this );
			AddCurrentAction( GetActionComponent( GAction::ACTION_MOVE ) );
		}
	}
}