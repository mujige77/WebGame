#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GMainGameEnvironment.h"
#include "GMainGameMove.h"
#include "GActionAttackCheck.h"



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
	{
		GnDelete mpSingleton;
		mpSingleton = NULL;
	}
}

GMainGameEnvironment* GMainGameEnvironment::GetSingleton()
{
	return (GMainGameEnvironment*)mpSingleton;
}

bool GMainGameEnvironment::SetStage(gtuint uiNumStage)
{
	if( GGameEnvironment::SetStage( uiNumStage ) == false )
		return false;
	
	float top = GetStageInfo()->GetInterfaceSize().y + 5.0f;
	float bottom = top + ( GetStageInfo()->GetLineHeight() * GetStageInfo()->GetNumLine() ) - 10.0f;
	
	SetEnableMoveRect( GnFRect( 0.0f, top, GetStageInfo()->GetBackgroundSize().x
		, bottom ) );
	
	//float basePosition = GetStageInfo()->GetInterfaceSize().y;
	for( gtuint i = 0 ; i < GetStageInfo()->GetNumLine() ; i++ )
	{
		GnFRect lineRect = GetStageInfo()->GetLineRect( i );
		AddLine( lineRect.bottom + ( GetStageInfo()->GetLineHeight() / 2 ) );
	}
	
	GMainGameEnvironment::GetSingleton()->SetMoveRangeY( GetStageInfo()->GetLineHeight() );
	return true;
}

void GMainGameEnvironment::Reset()
{
	mLines.RemoveAll();
}

bool GMainGameEnvironment::CorrectMoveX(float& fPositionX, bool uiDirection, bool bUser)
{
	bool ret = true;
	float userRect = 0.0f;
	if( uiDirection )
	{
		if( bUser == true )
			userRect = 50.0f;
		if( fPositionX <= mEnableMoveRect.left + userRect)
		{
			fPositionX = mEnableMoveRect.left + userRect;
			ret = false;
		}
	}
	else
	{
		if( bUser == true )
			userRect = 110.0f;
		if( fPositionX >= mEnableMoveRect.right - userRect)
		{
			fPositionX = mEnableMoveRect.right - userRect;
			ret = false;
		}
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

bool GMainGameEnvironment::CorrectMoveY(float& fPositionY)
{
	bool ret = true;
	if( mEnableMoveRect.ContainsPointY( fPositionY ) == false )
	{
		if( fPositionY <= mEnableMoveRect.top )
			fPositionY = mEnableMoveRect.top;
		else
			fPositionY = mEnableMoveRect.bottom;
		ret = false;
	}
	return ret;
}

void GMainGameEnvironment::SetStartPositionToActor(GActorController* pActorCtlr, guint32 uiLine, gtuint uiDirection)
{
	
	static gtint rendLinePosX = GetStageInfo()->GetLineHeight() / 4;
	static gtint rendLine = rendLinePosX;
	if( rendLine == rendLinePosX )
		rendLine = 0;
	else if( rendLine == 0 )
		rendLine = -rendLinePosX;
	else
		rendLine = rendLinePosX;
	
//	guint numLine = GetNumUserLine();
	GnVector2 pos( 0.0f, 0.0f );
	if( uiDirection == 1 )
	{
		pos.x = GetStageInfo()->GetBackgroundSize().x;
	}
	pos.y = GetLine( uiLine ) + (float)rendLine;
	
	
	GActionAttackCheck* attackCheck = (GActionAttackCheck*)pActorCtlr->GetActionComponent( GAction::ACTION_ATTACKCHECK );
	if( attackCheck )
		attackCheck->SetAttackLine( uiLine );

	GMainGameMove* moveAction = (GMainGameMove*)pActorCtlr->GetActionComponent( GAction::ACTION_MOVE );
	moveAction->SetNumLine( uiLine );
	
	pActorCtlr->SetPosition( pos );
	pActorCtlr->Start();
}

void GMainGameEnvironment::UserMove(GActorController* pActorCtlr)
{
	GMainGameMove* moveAction = (GMainGameMove*)pActorCtlr->GetActionComponent( GAction::ACTION_MOVE );
	SetNumUserLine( moveAction->GetNumLine() );
	
	GActionAttackCheck* attackCheck
	= (GActionAttackCheck*)pActorCtlr->GetActionComponent( GAction::ACTION_ATTACKCHECK );
	attackCheck->SetAttackLine( moveAction->GetNumLine() );
}