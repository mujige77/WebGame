#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GMainGameMove.h"
#include "GMainGameEnvironment.h"

GMainGameMove::GMainGameMove(GActorController* pController) : GActionMove( pController )
{
	mBeforeVerticalDirection = MOVE_MAX;
	mBeforeHorizontalDirection = MOVE_MAX;
}

void GMainGameMove::Update(float fDeltaTime)
{
	GActionMove::Update( fDeltaTime );
	SetCurrentLine();
}

void GMainGameMove::SetMove(gtuint uiType)
{
	GActionMove::SetMove( uiType );
	if( MOVEUP > uiType )
	{
		if( mBeforeVerticalDirection == uiType )
			return;
		if( MOVELEFT == uiType )
			GetController()->GetMesh()->SetFlipX( true );
		else
			GetController()->GetMesh()->SetFlipX( false );
		mBeforeVerticalDirection = (eMoveType)uiType;
	}
	else
	{
		if( GetMoveUp() )
		{
			GnVector2 movePos = GetController()->GetPosition();
			movePos.y += GetMoveVector().y;
			GetController()->SetPosition( movePos );
			if( GetActorLayer() )
			{
				GetActorLayer()->reorderChild( GetController()->GetMesh()->GetMesh()
					, (gint)(GetGameState()->GetGameHeight() - movePos.y) );
			}
		}
		else
		{
			GnVector2 movePos = GetController()->GetPosition();
			movePos.y += GetMoveVector().y;
			GetController()->SetPosition( movePos );
			if( GetActorLayer() )
			{
				GetActorLayer()->reorderChild( GetController()->GetMesh()->GetMesh()
					, (gint)(GetGameState()->GetGameHeight() - movePos.y) );
			}			
		}
	}
}

void GMainGameMove::SetCurrentLine()
{
	GMainGameEnvironment* env = GMainGameEnvironment::GetSingleton();
	float lineHeight = env->GetStageInfo()->GetLineHeight();
	GnVector2 movePos = GetController()->GetPosition();
	for( gtuint i = 0 ; i < env->GetLineCount() ; i++ )
	{
		float line = env->GetLine( i ) - ( lineHeight / 2 );
		if( line <= movePos.y && lineHeight + line >= movePos.y )
		{
			mNumLine = i;
			break;
		}
	}
}