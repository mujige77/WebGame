#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GActionAttack.h"
#include "GActorController.h"

GActionAttack::GActionAttack(GActorController* pController) : GAction( pController )
	, mEnableAttackCount( 1 ), mAttackAniIndex( ANI_ATTACK ), mNumAttackLine( 0 )
{
	

}

bool GActionAttack::CollisionCheck(GActorController* pCheckAttackActor)
{
	GActionAttack* checkAttack = (GActionAttack*)pCheckAttackActor->GetActionComponent( GAction::ACTION_ATTACK );
	if( GetAttackLine() != checkAttack->GetAttackLine() )
		return false;
	
	
	Gn2DSequence* attackSequence = NULL;
	GnVerify( GetController()->GetActor()->GetSequence( GetAttackAniIndex()
		, attackSequence ) );
	Gn2DAVData* attackAvData = attackSequence->GetAVData();
	if( attackAvData->GetCollisionCount() <= 1 )
	{
		AttachCompentToController();
		return false;
	}
	
	Gn2DAVData* avData = pCheckAttackActor->GetMesh()->GetAVData();
	if( avData == NULL )
		return false;
	Gn2DAVData::CollisionRect& rect	= avData->GetCollisionRect( 0 );
	
	attackAvData->Move( GetController()->GetMesh()->GetOriginalPosition() );
	if( GetController()->GetMesh()->GetFlipX() )
	{
		attackAvData->FlipX( true, GetController()->GetMesh()->GetOriginalPosition().x );
		Gn2DAVData::CollisionRect attackRect = attackAvData->GetCollisionRect( 1 );
		if( rect.mRect.ContainsRectWidth( attackRect.mRect ) == false )
			return false;
	}
	else
	{
		Gn2DAVData::CollisionRect attackRect = attackAvData->GetCollisionRect( 1 );
		if( attackRect.mRect.ContainsRectWidth( rect.mRect ) == false )
			return false;
	}
		
	
	
	
	AddAttackActor( pCheckAttackActor );
	return true;
}
