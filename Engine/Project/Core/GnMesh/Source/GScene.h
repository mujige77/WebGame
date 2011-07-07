#ifndef __HiroCat__GScene__
#define __HiroCat__GScene__
#include <cocos2d.h>

class GScene : public cocos2d::CCScene//, public CCTargetedTouchDelegate
{
public:	
	virtual void onEnter();
	virtual void onExit();
	
	virtual ~GScene(){}	
	virtual void Update(float fDeltaTime){};
};

#endif
