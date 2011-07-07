
#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GEnemyController.h"
#include "GInfoEnemyBasic.h"
#include "GCollectComponentHeader.h"
#include "GActionStand.h"
#include "GActionAttack.h"

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

	GAction* action = GnNew GActionStand( this );
	SetActionComponent( action->GetActionType(), action );
	
	action = GnNew GActionAttack( this );
	SetActionComponent( action->GetActionType(), action );
	return true;
}
