//
//  HiroCatDirector.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 15..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__HiroCatDirector__
#define __HiroCat__HiroCatDirector__

class HiroCatDirector : public cocos2d::CCDirector
{
public:
	HiroCatDirector(void) 
	: m_bInvalid(false)
	{}
	
	virtual void mainLoop(void);
	virtual void setAnimationInterval(double dValue);
	virtual void startAnimation(void);
	virtual void stopAnimation();
	
protected:
	bool m_bInvalid;
};

#endif
