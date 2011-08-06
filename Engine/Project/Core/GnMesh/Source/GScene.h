#ifndef __HiroCat__GScene__
#define __HiroCat__GScene__
#include <cocos2d.h>

class GScene : public cocos2d::CCScene//, public CCTargetedTouchDelegate
{
public:
	static const gchar* SCENENAME_START;
	static const gchar* SCENENAME_STATE;
	static const gchar* SCENENAME_SELECTSTAGE;
	static const gchar* SCENENAME_GAME;
private:
	static gstring mChangeSceneName;
	
public:
	static void SetChangeSceneName(const gchar* pcName);
	static gstring& GetChangeSceneName();
	
public:		
	virtual ~GScene(){}	
	virtual void Update(float fDeltaTime){};
	
	virtual const gchar* GetSceneName() = 0;
	
public:
	
};

#endif
