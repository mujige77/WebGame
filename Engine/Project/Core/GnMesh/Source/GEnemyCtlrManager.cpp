#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GEnemyCtlrManager.h"
#include "GEnemyController.h"
#include "GActionMove.h"
#include "GStageLevelManager.h"
#include <GFileList.h>
#include "GPlayingDataManager.h"
#include "GInfoEnemyBasic.h"

GEnemyCtlrManager* GEnemyCtlrManager::CreateActorCtlrManager(GLayer* pLayer, GStageLevelManager* pStageLevelManager
	, GCastle* pCastle)
{
	GEnemyCtlrManager* ctlrManager = GnNew GEnemyCtlrManager( pLayer, pStageLevelManager, pCastle );
	GStageLevel* stageLevel = pStageLevelManager->GetStageLevel();
	if( pCastle )
	{
		pCastle->SetHP( stageLevel->GetCastleHP() );
		pCastle->SetCurrentHP( stageLevel->GetCastleHP() );
	}
		
	return ctlrManager;
}

GEnemyCtlrManager::GEnemyCtlrManager(GLayer* pLayer, GStageLevelManager* pStageLevelManager, GCastle* pCastle)
	: GActorCtlrManager( pLayer, pCastle ), mpStageLevelManager(pStageLevelManager )
{
	mEnableDropMoneyTime.SetPercentTime( 30000.0f );
}

GEnemyCtlrManager::~GEnemyCtlrManager()
{
	if( mpStageLevelManager )
		GnDelete mpStageLevelManager;
}

void GEnemyCtlrManager::Update(float fDeltaTime)
{
	GActorCtlrManager::Update( fDeltaTime );
	
	mpStageLevelManager->Update( fDeltaTime );
	
	mEnableDropMoneyTime.Update(  fDeltaTime  );
		
	static int ikj = 0;
	for( gtuint i = 0 ; i < mpStageLevelManager->GetReadyAppearMobCount() ; i++ )
	{
		GStageLevelManager::ReadyAppearMobCtrl& mob = mpStageLevelManager->GetReadyAppearMob( i );
		//if( ikj == 0 )
		CreateEnemy( mob.index, mob.level, mob.line );
		//ikj++;
	}
	mpStageLevelManager->RemoveAllReadyAppearMob();
}

void GEnemyCtlrManager::RemoveAndDeleteActorCtlr(gtuint uiIndex)
{
	if( mEnableDropMoneyTime.IsPullTime() == false )
	{
		GInfoEnemyBasic* basic = (GInfoEnemyBasic*)GetActorCtlr( uiIndex )->GetInfoComponent( GInfo::INFO_BASIC );
		mDropMoney += basic->GetDropMoney() + 1 + GUserAbility::GetAbilityLevel( eIndexMoney ) ;	
	}
	
	GActorCtlrManager::RemoveAndDeleteActorCtlr( uiIndex );
}

void GEnemyCtlrManager::CreateEnemy(guint32 uiIndex, guint32 uiLevel, guint32 uiLine)
{
	const gchar* idName = GetFileList()->GetEnemyFileName( uiIndex );
	if( idName == NULL )
	{
		GnAssert( idName );
		return;
	}
	
	GEnemyController* controller = GEnemyController::Create( idName, uiLevel );
	GetGameEnvironment()->CreateActorControllerBasicAction( controller );
	GetGameEnvironment()->InitActorControllerAction( GetActorLayer(), controller );
	GetGameEnvironment()->SetStartPositionToActor( controller, uiLine, 1 );	
	
	GActionMove* move = (GActionMove*)controller->GetCurrentAction( GAction::ACTION_MOVE );
	move->SetMove( GActionMove::MOVELEFT );
	move->SetMoveRangeY( GetGameEnvironment()->GetMoveRangeY() );
	
	AddActorCtlr( controller );
}