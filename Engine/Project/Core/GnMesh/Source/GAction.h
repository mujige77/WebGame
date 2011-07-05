//
//  GAction.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 20..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

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
		ACTION_MAX,
	};
private:
	GActorController* mpController;
	
public:
	 GAction(GActorController* pController);
	
public:
	virtual void Update(float fTime);
	virtual inline gtint GetActionType() {
		return NULL_TYPE;
	}
	
public:
	inline GActorController* GetController() {
		return mpController;
	}
	inline virtual bool IsEnableMove() {
		return true;
	}

public:
	virtual void AttachCompentToController() = 0;
};

#endif
