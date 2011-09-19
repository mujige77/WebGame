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
	SetIsWaitAttackTime( false );
}

void GActionAttackCheck::Update(float fTime)
{
	if( IsReadyAttack() )
		mAcumAttackTime += fTime;
}

bool GActionAttackCheck::CollisionCheck(gtuint uiAttackLine, GnFRect& bodyRect, bool bDetailCheck)
{
	if( GetAttackLine() != uiAttackLine )
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
	

	attackAvData->Move( GetController()->GetMesh()->GetOriginalPosition() );
	if( GetController()->GetMesh()->GetFlipX() )
	{
		attackAvData->FlipX( true, GetController()->GetMesh()->GetOriginalPosition().x );
		Gn2DAVData::CollisionRect attackRect = attackAvData->GetCollisionRect( 1 );
		if( bDetailCheck == false )
			attackRect.mRect.left += 10.0f;
		
		if( attackRect.mRect.ContainsRectWidth( bodyRect ) == false )
			return false;
	}
	else
	{
		Gn2DAVData::CollisionRect attackRect = attackAvData->GetCollisionRect( 1 );
		if( bDetailCheck == false )
			attackRect.mRect.right -= 10.0f;
		
		if( attackRect.mRect.ContainsRectWidth( bodyRect ) == false )
			return false;
	}
	
	return true;
}

