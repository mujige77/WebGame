//
//  GForcesController.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GForcesController.h"
#include "GInfoForcesBasic.h"
#include "GCollectComponentHeader.h"
#include "GActionStand.h"
#include "GActionAttack.h"

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
	GInfoForcesBasic* info = (GInfoForcesBasic*)GetInfoComponent( GInfo::INFO_BASIC );
	
	GMainGameMove* moveAction = GnNew GMainGameMove( this );
	SetActionComponent( moveAction->GetActionType(), moveAction );
	moveAction->SetMoveRangeX( info->GetMoveRangeX() );
	moveAction->SetMoveRight( true );
	
	GAction* action = GnNew GActionStand( this );
	SetActionComponent( action->GetActionType(), action );

	action = GnNew GActionAttack( this );
	SetActionComponent( action->GetActionType(), action );
	return true;
}
