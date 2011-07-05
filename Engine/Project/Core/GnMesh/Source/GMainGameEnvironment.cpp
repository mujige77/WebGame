//
//  GMainGameEnvironment.cpp
//  Core
//
//  Created by Max Yoon on 11. 6. 30..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GMainGameEnvironment.h"
#include "GMainGameMove.h"
#include "GActionAttack.h"


GMainGameEnvironment* GMainGameEnvironment::Create()
{
	if( mpSingleton )
		GnDelete mpSingleton;
	
	GMainGameEnvironment* thisEnv = GnNew GMainGameEnvironment();
	mpSingleton = thisEnv;
	return thisEnv;
}

void GMainGameEnvironment::Destory()
{
	if( mpSingleton )
		GnDelete mpSingleton;
}

GMainGameEnvironment* GMainGameEnvironment::GetSingleton()
{
	return (GMainGameEnvironment*)mpSingleton;
}

void GMainGameEnvironment::Reset()
{
	mLines.RemoveAll();
}

bool GMainGameEnvironment::CorrectMove(GnVector2& cPosition)
{
	bool ret = true;
	if( mEnableMoveRect.ContainsPointX( cPosition.x ) == false )
	{
		if( cPosition.x <= mEnableMoveRect.left )
			cPosition.x = mEnableMoveRect.left;
		else
			cPosition.x = mEnableMoveRect.right;
		ret = false;
	}
	
//	gtuint size = mLines.GetSize();
//	float maxLinePos = mLines.GetAt( size - 1 );
//	float minLinePos = mLines.GetAt( 0 );
//	if ( cPosition.y > maxLinePos )
//	{
//		cPosition.y = maxLinePos;
//		ret = false;
//	}
//	else if( cPosition.y < minLinePos )
//	{
//		cPosition.y = minLinePos;
//		ret = false;
//	}
	return ret;
}
void GMainGameEnvironment::SetStartPositionToActor(GActorController* pActorCtlr, gtuint uiDirection)
{
	
	static const gtint rendLinePosX = 10;
	static gtint rendLine = rendLinePosX;
	if( rendLine == rendLinePosX )
		rendLine = 0;
	else if( rendLine == 0 )
		rendLine = -rendLinePosX;
	else
		rendLine = rendLinePosX;
	
	guint numLine = GetNumUserLine();
	GnVector2 pos( mEnableMoveRect.left, 0.0f );
	if( uiDirection == 1 )
	{
		pos.x = mEnableMoveRect.right;
		numLine = rand() % GetLineCount();
	}

	GActionAttack* attack = (GActionAttack*)pActorCtlr->GetActionComponent( GAction::ACTION_ATTACK );
	if( attack )
		attack->SetAttackLine( numLine );

	GMainGameMove* moveAction = (GMainGameMove*)pActorCtlr->GetActionComponent( GAction::ACTION_MOVE );
	moveAction->SetNumLine( numLine );
	moveAction->SetMoveRangeY( mMoveRangeY );
	
	pos.y = GetLine( numLine ) + rendLine;
	pActorCtlr->SetPosition( pos );
	pActorCtlr->Start();
}

void GMainGameEnvironment::UserMove(GAction* pMoveAction)
{
	GMainGameMove* moveAction = (GMainGameMove*)pMoveAction;
	SetNumUserLine( moveAction->GetNumLine() );
}