#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GUserController.h"
#include "GInfoForcesBasic.h"
#include "GCollectComponentHeader.h"
#include "GActionStand.h"
#include "GActionAttack.h"

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
	moveAction->SetMoveRangeX( info->GetMoveRangeX() );
	moveAction->SetNumLine( 0 );
	
	GAction* action = GnNew GActionStand( this );
	SetActionComponent( action->GetActionType(), action );
	
	action = GnNew GActionAttack( this );
	SetActionComponent( action->GetActionType(), action );
	return true;
}

void GUserController::Start()
{
	GActorController::Start();
	RemoveAllCurrentComponets();
	GetActionComponent( GAction::ACTION_STAND )->AttachCompentToController();
}