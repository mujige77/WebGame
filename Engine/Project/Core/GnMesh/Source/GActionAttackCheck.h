//
//  GActionAttackCheck.h
//  Core
//
//  Created by Max Yoon on 11. 7. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GActionAttackCheck__
#define __Core__GActionAttackCheck__

#include "GAction.h"

class GActionAttackCheck : public GAction
{
	GnDeclareFlags(gushort);
	enum
	{
		MASK_READYATTACK = 0x000001, // ready attack
		MASK_ENABLEATTACK = 0x000002, // i'm ready send attack message to my enemy
		MASK_WAITATTACKANI = 0x000004, // Sended attack meassage, wait end attack animation
	};
public:
	enum
	{
		MAX_ATTCK_COUNT = 10,
	};
	
private:
	gtuint mAttackAniIndex;
	gtuint mNumAttackLine;
	gtuint mEnableAttackCount;
	
public:
	GActionAttackCheck(GActorController* pController);
	bool CollisionCheck(GActorController* pCheckAttackActor);
	
public:
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
	
	inline bool IsReadyAttack() {
		return GetBit( MASK_READYATTACK );
	}
	inline void SetIsReadyAttack(bool val) {
		SetBit( val, MASK_READYATTACK );
	}
	inline bool IsEnableAttack() {
		return GetBit( MASK_ENABLEATTACK );
	}
	inline void SetIsEnableAttack(bool val) {
		SetBit( val, MASK_ENABLEATTACK );
	}

public:
	inline gtuint GetEnableAttackCount() {
		return mEnableAttackCount;
	}
	inline void SetEnableAttackCount(gtuint val) {
		mEnableAttackCount = val;
	}
	
public:
	inline void AttachActionToController(){
		SetIsEnableAttack( false );
		SetIsReadyAttack( false );
	}
	inline void DetachActionToController() {
		SetIsEnableAttack( false );
		SetIsReadyAttack( false );		
	};
	inline gtint GetActionType() {
		return ACTION_ATTACKCHECK;
	}
};

#endif
