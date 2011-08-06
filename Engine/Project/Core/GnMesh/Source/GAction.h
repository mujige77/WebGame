#ifndef __HiroCat__GAction__
#define __HiroCat__GAction__

class GActorController;
class GAction : public GnMemoryObject
{
public:
	static const gtint NULL_TYPE = -1;

public:
	enum eAniIndex
	{
		ANI_STAND = 1,
		ANI_WALK = 2,
		ANI_ATTACK = 3,
		ANI_DIE = 4,
		ANI_ATTACK_MULTI
	};
	enum eActionComponentType
	{
		ACTION_MOVE,
		ACTION_STAND,
		ACTION_ATTACK,
		ACTION_ATTACKCHECK,
		ACTION_DAMAGE,
		ACTION_DIE,
		ACTION_GAGE,
		ACTION_MAX,
	};
private:
	GActorController* mpController;
	
public:
	GAction(GActorController* pController);
	virtual inline ~GAction() {}
public:
	virtual void Update(float fTime);
	virtual inline gtint GetActionType() {
		return NULL_TYPE;
	}
	
public:
	inline GActorController* GetController() {
		return mpController;
	}


public:
	virtual void AttachActionToController() = 0;
	virtual inline void DetachActionToController() {		
	};
	virtual inline bool IsEnableMove() {
		return true;
	}
	virtual inline bool IsStopAction() {
		return false;
	}
};

#endif
