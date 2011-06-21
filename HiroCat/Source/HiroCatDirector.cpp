//
//  HiroCatDirector.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 15..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//
#include "GamePCH.h"
#include "HiroCatDirector.h"
#include "CCAutoreleasePool.h"
#include "platform/platform.h"
#include "GSceneSelector.h"
// should we afford 4 types of director ??
// I think HiroCatDirector is enough
// so we now only support HiroCatDirector
void HiroCatDirector::startAnimation(void)
{
	if (CCTime::gettimeofdayCocos2d(m_pLastUpdate, NULL) != 0)
	{
		CCLOG("cocos2d: DisplayLinkDirector: Error on gettimeofday");
	}
	
	m_bInvalid = false;
	CCApplication::sharedApplication().setAnimationInterval(m_dAnimationInterval);
}

void HiroCatDirector::mainLoop(void)
{	
	if (m_bPurgeDirecotorInNextLoop)
	{
		purgeDirector();
        m_bPurgeDirecotorInNextLoop = false;
	}
	else if (! m_bInvalid)
 	{
		calculateDeltaTime();
		GScene* pScene = GSceneSelector::GetSingleton()->GetCurrentScene(); 
		pScene->Update( m_fDeltaTime );
		
 		drawScene();		
 		// release the objects
 		CCPoolManager::getInstance()->pop();
 	}
}

void HiroCatDirector::stopAnimation(void)
{
	m_bInvalid = true;
}

void HiroCatDirector::setAnimationInterval(double dValue)
{
	m_dAnimationInterval = dValue;
	if (! m_bInvalid)
	{
		stopAnimation();
		startAnimation();
	}	
}