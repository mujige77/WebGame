#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GMainGameEnvironment.h"
#include "GActionMove.h"
#include "GActionDamage.h"
#include "GActionStand.h"
#include "GActionAttack.h"
#include "GActionDamage.h"
#include "GActionAttackCheck.h"
#include "GActionDie.h"
#include "GActionGage.h"
#include "GInfoBasic.h"
#include "GActionFollows.h"
GGameEnvironment* GGameEnvironment::mpSingleton = NULL;

GGameEnvironment* GGameEnvironment::GetSingleton()
{
	return mpSingleton;
}
 
bool GGameEnvironment::SetStage(gtuint uiNumStage)
{
	if( GStageInfo::GetStageInfo( uiNumStage, mStageInfo ) == false )
		return false;
	
	return true;
}

void GGameEnvironment::RemoveBasicCurrentAction(GActorController* pCtrl)
{
	pCtrl->RemoveCurrentAction( GAction::ACTION_MOVE );
	pCtrl->RemoveCurrentAction( GAction::ACTION_ATTACK );
	pCtrl->RemoveCurrentAction( GAction::ACTION_STAND );
}


void GGameEnvironment::InitActorControllerAction(GLayer* pActorLayer, GActorController* pActorCtrl)
{
	GActionMove* move = (GActionMove*)pActorCtrl->GetActionComponent( GAction::ACTION_MOVE );
	move->CleanMove();
	move->SetActorLayer( pActorLayer );
	GActionDamage* damage = (GActionDamage*)pActorCtrl->GetActionComponent( GAction::ACTION_DAMAGE );
	damage->SetActorLayer( pActorLayer );
	GActionGage* gage = (GActionGage*)pActorCtrl->GetActionComponent( GAction::ACTION_GAGE );
	gage->SetActorLayer( pActorLayer );
	GActionFollows* follows = (GActionFollows*)pActorCtrl->GetActionComponent( GAction::ACTION_FOLLOWS );
	follows->SetActorLayer( pActorLayer );
	
	GActionAttack* attackAction = (GActionAttack*)pActorCtrl->GetActionComponent( GAction::ACTION_ATTACK );
	GInfoBasic* info =  (GInfoBasic*)pActorCtrl->GetInfoComponent( GInfo::INFO_BASIC );
	attackAction->Init( info->GetAttackType(), info->GetAttackCount(), info->GetStrength() );
#ifdef GNDEBUG
//	GnSingleDrawPrimitiveslayer* pLayer = new GnSingleDrawPrimitiveslayer();
//	pLayer->GetDrawObject()->SetController( pActorCtrl );
//	pLayer->autorelease();
//	pActorLayer->addChild( pLayer, 500 );
//	pActorCtrl->SetDebugLayer( pLayer );
	pActorCtrl->SetDebugLayer( NULL );
#endif
}

void GGameEnvironment::CreateActorControllerBasicAction(GActorController* pActorCtrl)
{
	CreateActionToActorController<GActionStand>( pActorCtrl );
	CreateActionToActorController<GActionAttack>( pActorCtrl );
	CreateActionToActorController<GActionDamage>( pActorCtrl );
	CreateActionToActorController<GActionAttackCheck>( pActorCtrl );
	CreateActionToActorController<GActionDie>( pActorCtrl );
	CreateActionToActorController<GActionGage>( pActorCtrl );
	CreateActionToActorController<GActionFollows>( pActorCtrl );
	GnVerify( pActorCtrl->InitActionComponents() );
}

template<class T>
void GGameEnvironment::CreateActionToActorController(GActorController* pActorCtrl)
{
	T* action = GnNew T( pActorCtrl );
	pActorCtrl->SetActionComponent( action->GetActionType(), action );
}