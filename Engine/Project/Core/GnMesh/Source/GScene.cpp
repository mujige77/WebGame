#include "GnMeshPCH.h"
#include "GnGamePCH.h"
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
