//
//  GActionDie.h
//  Core
//
//  Created by Max Yoon on 11. 7. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GActionDie__
#define __Core__GActionDie__

#include "GAction.h"
class GActionDie : public GAction
{
private:
	float mAlphaTime;
	float mAcumTime;
	
public:
	GActionDie(GActorController* pController);	
	
public:
	virtual void Update(float fTime);
	virtual inline gtint GetActionType() {
		return ACTION_DIE;
	}
	inline void AttachActionToController() {
		mAlphaTime = 2.0f;
		mAcumTime = 0.0f;
		Gn2DSequence* sequence = NULL;
		GetController()->GetActor()->GetSequence( GAction::ANI_DIE, sequence );
		GnAssert( sequence );
		if( sequence )
			sequence->SetLoop( false );
		GetController()->GetActor()->SetTargetAnimation( GAction::ANI_DIE );
	};
};

#endif
