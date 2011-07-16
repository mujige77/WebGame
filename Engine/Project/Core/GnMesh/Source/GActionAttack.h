#ifndef __Core__GAttack__
#define __Core__GAttack__
#include "GAction.h"

class GActionAttack : public GAction
{
	GnDeclareFlags(gushort);
	enum
	{
		MASK_WAITATTACKANI = 0x000004, // Sended attack meassage, wait end attack animation
	};

private:
	GnTPrimitiveArray<GActorController*> mAttackToActors;
	
public:
	GActionAttack(GActorController* pController);
	void Reset();
	
public:
	inline void AttachActionToController()	{
		GetController()->GetActor()->SetTargetAnimation( ANI_ATTACK );
	}
	inline gtint GetActionType() {
		return ACTION_ATTACK;
	}
	inline bool IsWaitEndAttackAni() {
		return GetBit( MASK_WAITATTACKANI );
	}
	inline void SetIsWaitEndAttackAni(bool val) {
		SetBit( val, MASK_WAITATTACKANI );
	}
};

#endif
