//
//  GScene.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 19..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GamePCH.h"
#include "GScene.h"

void GScene::onEnter()
{
	//CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
	CCScene::onEnter();
}

void GScene::onExit()
{
	//CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCScene::onExit();
}
