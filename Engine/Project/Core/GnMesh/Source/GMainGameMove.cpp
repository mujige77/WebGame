#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GMainGameMove.h"
#include "GMainGameEnvironment.h"

GMainGameMove::GMainGameMove(GActorController* pController) : GActionMove( pController )
{
	mBeforeVerticalDirection = MOVE_MAX;
	mBeforeHorizontalDirection = MOVE_MAX;
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
			if( mNumLine < GMainGameEnvironment::GetSingleton()->GetLineCount() - 1 )
			{
				++mNumLine;
				GnVector2 movePos = GetController()->GetPosition();
				movePos.y += GetMoveVector().y;
				GetController()->SetPosition( movePos );
				if( GetActorLayer() )
				{
					GetActorLayer()->reorderChild( GetController()->GetMesh()->GetMesh()
						, (gint)(GetGameState()->GetGameHeight() - movePos.y) );
				}
			}
			SetMoveUp( false );
		}
		else
		{
			if( mNumLine > 0 )
			{
				--mNumLine;
				GnVector2 movePos = GetController()->GetPosition();
				movePos.y += GetMoveVector().y;
				GetController()->SetPosition( movePos );
				if( GetActorLayer() )
				{
					GetActorLayer()->reorderChild( GetController()->GetMesh()->GetMesh()
						, (gint)(GetGameState()->GetGameHeight() - movePos.y) );
				}
					
			}
			SetMoveDown( false );			
		}
		mMoveVector.y = 0;
	}
}