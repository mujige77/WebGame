#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GActorController.h"
#include "GAction.h"
#include "GInfoBasic.h"
#include "GActionAttack.h"
#include "GActionAttackCheck.h"
#include "GActionDie.h"
#include "GActionGage.h"
#include "GActionDamage.h"
#include "GAttackDamageInfo.h"


void GActorController::GetFullActorFilePath(const gchar* pcID, gstring& pcOutPath)
{
	pcOutPath = GnSystem::GetWorkDirectory();
	pcOutPath += "Actor/";
	pcOutPath += pcID;
	pcOutPath += "/";
	pcOutPath += pcID;
	pcOutPath += ".gat";
}

GActorController::GActorController() : mUsedDownDamage( false ), mUsedDefence( false )
	, mMoveDeltaPosition( GnVector2(0.0f, 0.0f) )
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

	GActionDamage* damage = (GActionDamage*)GetCurrentAction( GAction::ACTION_DAMAGE );
	if( damage && damage->IsDontMove() && damage->IsDownDamage() == false )
	{
		//damage->Update( fDeltaTime );
		GnVector2 movePos = GetPosition() + GetMoveDeltaPosition();
		GetGameEnvironment()->CorrectMoveX( movePos.x, GetActor()->GetRootNode()->GetFlipX() );
		SetPosition( movePos );
		SetMoveDeltaPosition( GnVector2(0.0f, 0.0f) );
		return;
	}
	
	if( mUsedDefence )
	{
		mDefanceAcumTime += fDeltaTime;
		if( mDefanceAcumTime < 10.0f )
		{
			return;
		}
		mUsedDefence = false;
		SetStartAction();
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
	if( pComponent )
	{
		pComponent->AttachActionToController();
		mCurrentActions.SetAt( pComponent->GetActionType(), pComponent );	
	}
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

bool GActorController::InitActionComponents()
{
	GInfoBasic* info = (GInfoBasic*)GetInfoComponent( GInfo::INFO_BASIC );
	
	GActionAttackCheck* attackCheck = (GActionAttackCheck*)GetActionComponent( GAction::ACTION_ATTACKCHECK );
	attackCheck->SetAttackSpeed( info->GetAttackSpeed() );
	attackCheck->SetEnableAttackCount( info->GetAttackCount() );
	
	GActionDamage* damage = (GActionDamage*)GetActionComponent( GAction::ACTION_DAMAGE );
	
	if( info->GetAttackType() == GActionAttack::eTypeDefence )
	{
		if( damage )
			damage->SetIsEnableSetStartAction( false );
	}
		
	return true;
}

void GActorController::ReceiveAttack(GAttackDamageInfo* pDamage)
{
	if( pDamage->GetAttackType() == GActionAttack::eTypeMouthFul )
	{
		mCurrentInfo.SetHP( 0 );
		AddCurrentAction( GetActionComponent( GAction::ACTION_DIE ) );
		return;
	}
	
	mCurrentInfo.SetHP( mCurrentInfo.GetHP() - (gint32)pDamage->GetDamage() );
	if( mCurrentInfo.GetHP() > 0 )
	{
		bool downDamage = false;
		GInfoBasic* info = (GInfoBasic*)mInfoComponents.GetAt( GInfo::INFO_BASIC );
		if( info )
			downDamage = ( info->GetHP() / 2 ) > mCurrentInfo.GetHP() ? true : false;
		
		GActionDamage* damage = (GActionDamage*)GetActionComponent( GAction::ACTION_DAMAGE );
		if( pDamage->GetDontMoveTime() > 0.0000001f && damage )
		{
			damage->SetIsDontMove( true );
			damage->SetDontMoveTime( pDamage->GetDontMoveTime() );
		}
		
		damage = (GActionDamage*)GetCurrentAction( GAction::ACTION_DAMAGE );
		if( damage == NULL )
		{
			damage = (GActionDamage*)GetActionComponent( GAction::ACTION_DAMAGE );
			GnAssert( damage );
			if( damage )
			{
				if( mUsedDownDamage == false )
				{
					mUsedDownDamage = downDamage;
					damage->SetIsDownDamage( downDamage );
					if( mUsedDownDamage )
					{
						mUsedDefence = false;
						mDefanceAcumTime = 0.0f;
					}
				}
				
				damage->SetAttackDamage( pDamage );
				AddCurrentAction( damage );
			}
		}
		else
		{
			if( damage->IsEnableDamage() )
			{
				bool dontMove = damage->IsDontMove();
				bool ice = damage->IsIce();
				RemoveCurrentAction( damage->GetActionType() );
				if( mUsedDownDamage == false )
				{
					mUsedDownDamage = downDamage;
					damage->SetIsDownDamage( downDamage );
				}
				damage->SetIsDontMove( dontMove, ice );
				damage->SetAttackDamage( pDamage );
				AddCurrentAction( damage );				
			}
		}
		
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

void GActorController::SetStartAction()
{
	AddCurrentAction( GetActionComponent( GAction::ACTION_MOVE ) );
	AddCurrentAction( GetActionComponent( GAction::ACTION_ATTACKCHECK ) );
	AddCurrentAction( GetActionComponent( GAction::ACTION_FOLLOWS ) );
}

void GActorController::Start()
{
	GInfoBasic* basic = (GInfoBasic*)GetInfoComponent( GInfo::INFO_BASIC );
	mCurrentInfo.SetHP( basic->GetHP() );
	SetStartAction();
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
	
	GActionAttack* attack = (GActionAttack*)GetActionComponent( GAction::ACTION_ATTACK );
	if( attack )
	{
		if( attack->GetAttackType() == GActionAttack::eTypeSelfBoom )
		{
			RemoveAllCurrentAction();
			SetIsDestory( true );
			GetActor()->GetRootNode()->SetAlpha( (guchar)0 );
			return;
		}
		if( attack->GetAttackType() == GActionAttack::eTypeDefence )
		{
			mUsedDefence = true;
			mDefanceAcumTime = 0.0f;
			RemoveAllCurrentAction();
			return;
		}
	}
	
	if( GetGameEnvironment() )
		GetGameEnvironment()->RemoveBasicCurrentAction( this );
	action = GetActionComponent( GAction::ACTION_STAND );
	AddCurrentAction( action );
	GActionAttackCheck* attackCheck = (GActionAttackCheck*)GetActionComponent( GAction::ACTION_ATTACKCHECK );
	if( attackCheck )
	{
		AddCurrentAction( attackCheck );
		attackCheck->ResetAttackTime();	
	}
}

void GActorController::SetEndDie()
{
	
}

void GActorController::UpdateAction(gtuint uiIndex)
{
	
}

void GActorController::MoveStopCheck()
{
	GActionAttackCheck* attackCheck = (GActionAttackCheck*)GetActionComponent( GAction::ACTION_ATTACKCHECK );
	if( attackCheck && attackCheck->IsReadyAttack() )
	{
		if( attackCheck->IsOverAttackTime() )
		{
			GetGameEnvironment()->RemoveBasicCurrentAction( this );
			AddCurrentAction( GetActionComponent( GAction::ACTION_ATTACK ) );
		}
		else			
		{
			GetGameEnvironment()->RemoveBasicCurrentAction( this );
			AddCurrentAction( GetActionComponent( GAction::ACTION_STAND ) );

		}			
		return;
	}
	
	GAction* move = GetCurrentAction( GAction::ACTION_MOVE );
	GActionDamage* damage = (GActionDamage*)GetCurrentAction( GAction::ACTION_DAMAGE );
	if( damage || move )
	{
		GnVector2 movePos = GetPosition() + GetMoveDeltaPosition();
		if( GetGameEnvironment()->CorrectMoveX( movePos.x, GetActor()->GetRootNode()->GetFlipX() ) == false )
		{
			GetGameEnvironment()->RemoveBasicCurrentAction( this );
			AddCurrentAction( GetActionComponent( GAction::ACTION_STAND ) );
			if( GetCurrentAction( GAction::ACTION_ATTACKCHECK ) == NULL )
				AddCurrentAction( GetActionComponent( GAction::ACTION_ATTACKCHECK ) );
		}
		SetPosition( movePos );
		SetMoveDeltaPosition( GnVector2(0.0f, 0.0f) );
	}
	else
	{
		GAction* action = GetCurrentAction( GAction::ACTION_STAND );
		GnVector2 movePos = GetPosition() + GetMoveDeltaPosition();
		if( action && GetGameEnvironment()->CorrectMoveX( movePos.x, GetActor()->GetRootNode()->GetFlipX() ) )
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