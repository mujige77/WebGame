//
//  GCPMove.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 20..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GCPMove__
#define __HiroCat__GCPMove__

#include "GComponent.h"

class GCPMove : public GComponent
{
private:
	float mMoveRange;
	
public:
	GCPMove();
	virtual void Update(float fDeltaTime);
	
public:
	inline float GetMoveRange() {
		return mMoveRange;
	}
	inline void SetMoveRange(float val) {
		mMoveRange = val;
	}
};

#endif
