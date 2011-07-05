//
//  GAttack.h
//  Core
//
//  Created by Max Yoon on 11. 7. 3..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GAttack__
#define __Core__GAttack__
#include "GAction.h"

class GActionAttack : public GAction
{
private:
	gtuint mEnableAttackCount;
	gtuint mAttackAniIndex;
	gtuint mNumAttackLine;
	GnTPrimitiveArray<GActorController*> mAttackToActors;

	
public:
	GActionAttack(GActorController* pController);
	bool CollisionCheck(GActorController* pCheckAttackActor);
	void SendToAttackActors();
	
public:
	inline void AttachCompentToController()	{
		GetController()->AddCurrentAction( this );
		GetController()->GetActor()->SetTargetAnimation( ANI_ATTACK );
	}
	inline gtint GetActionType() {
		return ACTION_ATTACK;
	}
public:
	inline gtuint GetEnableAttackCount() {
		return mEnableAttackCount;
	}
	inline void SetEnableAttackCount(gtuint val) {
		mEnableAttackCount = val;
	}
	inline gtuint GetAttackAniIndex() {
		return mAttackAniIndex;
	}
	inline void SetAttackAniIndex(gtuint val) {
		mAttackAniIndex = val;
	}
	inline void SetAttackLine(gtuint uiAttackLine) {
		mNumAttackLine = uiAttackLine;
	}
	inline gtuint GetAttackLine() {
		return mNumAttackLine;
	}
	inline void AddAttackActor(GActorController* pAttackActor) {
		mAttackToActors.Add( pAttackActor );
	}
	inline gtuint GetAttackActorCount() {
		return mAttackToActors.GetSize();
	}
	inline bool IsMoreAttack() {
		return mAttackToActors.GetSize() >= GetEnableAttackCount();
	}
};

#endif
