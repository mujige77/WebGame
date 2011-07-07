#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GActorController.h"
#include "GAction.h"
#include "GInfoBasic.h"
#include "GActionAttack.h"

void GActorController::GetFullActorFilePath(const gchar* pcID, gstring& pcOutPath)
{
	pcOutPath = GnSystem::GetWorkDirectory();
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
	RemoveAllCurrentComponets();
}

bool GActorController::Init(const gchar* pcActorFilePath, const gchar* pcID, guint32 uiLevel)
{
	SetIsDestory( false );
//	RemoveAllInfoComponets();
//	RemoveAllActionComponets();
//	RemoveAllCurrentComponets();
	mInfoComponents.SetSize( GInfo::INFO_MAX );
	mActionComponents.SetSize( GAction::ACTION_MAX );
	mCurrentActions.SetSize( GAction::ACTION_MAX );
	
	if( LoadActor( pcActorFilePath ) == false )
		return false ;
	
	if( InitInfoCompenent( pcID, uiLevel ) == false )
		return false;
	
	if( InitActionComponents() == false )
		return false;
	
	return true;
}

void GActorController::Update(float fDeltaTime)
{	
	mpsActor->Update( fDeltaTime );
	mpsActor->GetRootNode()->Update( fDeltaTime );
	for( gtuint i = 0 ; i < mCurrentActions.GetSize() ; i++ )
	{
		GAction* action = mCurrentActions.GetAt( i );
		if( action )
			action->Update( fDeltaTime );
	}
	
	MoveStopCheck();
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
	mCurrentActions.SetAt( pComponent->GetActionType(), pComponent );
}

void GActorController::ReceiveAttack(GActorController* pFromActor)
{
	GInfoBasic* fromActorBasic = (GInfoBasic*)pFromActor->GetInfoComponent( GInfo::INFO_BASIC );
	mCurrentInfo.SetHP( mCurrentInfo.GetHP() - (gint32)fromActorBasic->GetStrength() );
	if( mCurrentInfo.GetHP() )
	{
		
	}
}

void GActorController::Start()
{
	GInfoBasic* basic = (GInfoBasic*)GetInfoComponent( GInfo::INFO_BASIC );
	mCurrentInfo.SetHP( basic->GetHP() );
	
	GetActionComponent( GAction::ACTION_MOVE )->AttachCompentToController();
}

bool GActorController::LoadActor(const gchar *pcFilePath)
{
	GnObjectStream stream;
	mpsActor = Gn2DActor::Create( pcFilePath, stream );
	if( mpsActor == NULL )
		return false;
	
	return true;
}

void GActorController::MoveStopCheck()
{
	GActionAttack* attack = (GActionAttack*)GetActionComponent( GAction::ACTION_ATTACK );
	if( attack && attack->GetAttackActorCount() )
	{
		RemoveAllCurrentComponets();
		attack->AttachCompentToController();
		return;
	}
	
	GAction* move = mCurrentActions.GetAt( GAction::ACTION_MOVE );
	if( move )
	{
		if( GetGameEnvironment()->CorrectMove( GetMovePosition() ) == false )
		{
			RemoveAllCurrentComponets();
			GetActionComponent( GAction::ACTION_STAND )->AttachCompentToController();			
		}
		SetPosition( GetMovePosition() );
	}
}

void GActorController::CallbackTimeEvent(Gn2DActor::TimeEvent* pTimeEvent)
{
	if( pTimeEvent->mEventType == Gn2DActor::TimeEvent::END_SEQUENCE )
	{
		if( pTimeEvent->mSequenceID == GAction::ANI_ATTACK )
		{
			RemoveAllCurrentComponets();
			GetActionComponent( GAction::ACTION_STAND )->AttachCompentToController();
		}
	}
}