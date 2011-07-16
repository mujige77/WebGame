//
//  GActionAttackCheck.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GActionAttackCheck.h"

GActionAttackCheck::GActionAttackCheck(GActorController* pController) : GAction( pController )
	,mEnableAttackCount( 1 ), mAttackAniIndex( ANI_ATTACK ), mNumAttackLine( 0 )
{
}

bool GActionAttackCheck::CollisionCheck(GActorController* pCheckAttackActor)
{
	if( pCheckAttackActor->GetCurrentAction( GAction::ACTION_DIE ) )
		return false;
	
	GActionAttackCheck* checkAttack = (GActionAttackCheck*)pCheckAttackActor->GetActionComponent(
		GAction::ACTION_ATTACKCHECK );
	if( checkAttack == NULL || GetAttackLine() != checkAttack->GetAttackLine() )
		return false;
	
	
	Gn2DSequence* attackSequence = NULL;
	if( GetController()->GetActor()->GetSequence( GetAttackAniIndex(), attackSequence ) == false )
		return false;
	Gn2DAVData* attackAvData = attackSequence->GetAVData();
	if( attackAvData->GetCollisionCount() <= 1 )
	{
		GetController()->AddCurrentAction( this );
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
	
	return true;
}

