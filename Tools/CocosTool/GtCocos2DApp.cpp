#include "StdAfx.h"
#include "GtCocos2DApp.h"


GtCocos2DApp::GtCocos2DApp(void)
{
}


GtCocos2DApp::~GtCocos2DApp(void)
{
}

bool GtCocos2DApp::initInstance()
{
	return true;
}

bool GtCocos2DApp::applicationDidFinishLaunching()
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	// enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
	// pDirector->enableRetinaDisplay(true);

	// sets opengl landscape mode
	// tests set device orientation in RootViewController.mm
	// pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

	// turn on display FPS
	//pDirector->setDisplayFPS(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	//CCScene * pScene = CCScene::node();
	//CCLayer * pLayer = new TestController();
	//pLayer->autorelease();

	//pScene->addChild(pLayer);
	//pDirector->runWithScene(pScene);	

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void GtCocos2DApp::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->pause();
}

// this function will be called when the app is active again
void GtCocos2DApp::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->resume();
}
