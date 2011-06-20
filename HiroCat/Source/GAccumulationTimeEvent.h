//
//  GAccumulationTimeEvent.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GAccumulationTimeEvent__
#define __HiroCat__GAccumulationTimeEvent__

class GAccumulationTimeEvent
{
private:
	float mEventTime;
	float mAccumulationTime;
	
public:
	GAccumulationTimeEvent();
	inline bool UpdateEvent(float fDeltaTime)
	{
		mAccumulationTime += fDeltaTime;
		if( mEventTime < mAccumulationTime )
			return true;
		return false;
	}
	
	inline void Reset(float fEventTime) {
		mEventTime = fEventTime;
		mAccumulationTime = 0.0f;
	}
};

#endif
