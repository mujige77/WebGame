//
//  GComponent.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 20..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GComponent__
#define __HiroCat__GComponent__

class GActorController;
class GComponent : public GnMemoryObject
{
private:
	GActorController* mpController;
	
public:
	GComponent(GActorController* pController);
	virtual void Update(float fTime) = 0;
	
public:
	inline GActorController* GetController() {
		return mpController;
	}
};

#endif
