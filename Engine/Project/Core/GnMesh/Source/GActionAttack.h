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

public:
	enum eAttackType
	{
		eTypeNormal,
		eTypeMultiAttack,
		eTypeMissile,
		eTypeMultiMissile,
		eTypeIceMagic,
		eTypeParabolaBoom,
		eTypeSelfBoom,
		eTypeDefence,
		eTypeHeal,
		eTypeMouthFul,
	};
	
private:
	GnTPrimitiveArray<GActorController*> mAttackToActors;
	eAttackType mAttackType;
	guint32 mAttackCount;
	guint32 mAttackDamage;
	
public:
	GActionAttack(GActorController* pController);
	void Reset();
	void Init(guint32 uiAttackType, guint32 uiAttackCount, guint32 uiAttackDamage);
	GFarAttack* CreateFarAttack();
	
public:
	inline void AttachActionToController()	{
		mAttackToActors.RemoveAll();
		Gn2DActor* actor = GetController()->GetActor();
		actor->SetTargetAnimation( ANI_ATTACK );
		Gn2DSequence* sequence = NULL;
		if( actor->GetSequence( ANI_ATTACK, sequence ) )
			sequence->SetLoop( false );
		
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
	gtuint GetAttackedControllerSize() {
		return mAttackToActors.GetSize();
	}
	GActorController* GetAttackedController(gtuint uiIndex) {
		return mAttackToActors.GetAt( uiIndex );
	}
	void AddToAttackController(GActorController* pController) {
		mAttackToActors.Add( pController );
	}
	inline eAttackType GetAttackType() {
		return mAttackType;
	}
	inline bool IsFarAttack() {
		return mAttackType > eTypeMultiAttack;
	}
protected:
	GnFRect GetFarAttackRect(Gn2DMeshObject* pAttackMesh);
	guint32 GetFarAttackFileIndex();
};

#endif
