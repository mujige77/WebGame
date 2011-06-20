#ifndef  _HiroCatApplication__H_
#define  _HiroCatApplication__H_

#include "CCApplication.h"


class HiroCatApplication : public cocos2d::CCApplication
{
public:
	HiroCatApplication();
	virtual ~HiroCatApplication();
	
    virtual bool initInstance();
	virtual bool applicationDidFinishLaunching();
	
	virtual void applicationDidEnterBackground();
	
	virtual void applicationWillEnterForeground();
};

#endif // _HiroCatApplication__H_


