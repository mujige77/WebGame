//
//  GActionDie.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GActionDie.h"


GActionDie::GActionDie(GActorController* pController) : GAction(pController)
{
	
}


void GActionDie::Update(float fTime)
{
	Gn2DSequence* sequence = GetController()->GetActor()->GetCurrentSequence();
	//GnAssert( sequence->IsLoop() == false );
	if( sequence->IsStop() )
	{
		mAcumTime += fTime;
		gint alpha = 255 - ( (mAcumTime / mAlphaTime) * 255 );
		if( alpha <= 0 )
		{
			GetController()->SetIsDestory( true );
			return;
		}
		Gn2DMeshObject* mesh = GetController()->GetMesh();
		mesh->SetAlpha( (guchar)alpha );
	}
}