#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GActionMove.h"

GActionMove::GActionMove(GActorController* pController) : GAction( pController ), mpActorLayer( NULL )
	, mMoveRange( 5.0f, 40.0f )
{
	SetMoveLeft( false );
	SetMoveRight( false );
	SetMoveUp( false );
	SetMoveDown( false );
}

void GActionMove::Update(float fDeltaTime)
{
	GnVector2 movePos = GetController()->GetPosition();
	movePos +=  GetMoveVector();
	GetController()->SetMovePosition( movePos );
}

void GActionMove::SetMove(gtuint uiType)
{
	switch ( uiType )
	{
		case MOVELEFT:
		{
			mMoveVector.x = -GetMoveRange().x;
			SetMoveLeft( true );
		}
		break;
		case MOVERIGHT:
		{
			mMoveVector.x = GetMoveRange().x;
			SetMoveRight( true );
		}
		break;
		case MOVEUP:
		{
			mMoveVector.y = GetMoveRange().y;
			SetMoveUp( true );
		}
		break;
		case MOVEDOWN:
		{
			mMoveVector.y = -GetMoveRange().y;
			SetMoveDown( true );
		}
		break;
	}
}

void GActionMove::SetMoveX(bool bLeft, bool bRight)
{		
	if( bRight && bLeft == false )
	{
		SetMove( MOVERIGHT );
	}
	else if( bLeft && bRight == false )
	{
		SetMove( MOVELEFT );
	}
}

void GActionMove::SetMoveY(bool bUp, bool bDown)
{
	if( bUp && bDown == false )
	{
		SetMove( MOVEUP );
	}
	else if( bDown && bUp == false )
	{
		SetMove( MOVEDOWN );
	}
}