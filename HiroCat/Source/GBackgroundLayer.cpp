//
//  GBackgroundLayer.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GamePCH.h"
#include "GBackgroundLayer.h"

GBackgroundLayer::GBackgroundLayer()
{
	setIsTouchEnabled(true);
}

void GBackgroundLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	mLastBackgroundMovePostion = touch->locationInView( touch->view() );
}

void GBackgroundLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	
	CCPoint touchPoint = touch->locationInView( touch->view() );
	float moveX = mLastBackgroundMovePostion.x - touchPoint.x; 
	
	CCPoint thisPosition = getPosition();
	thisPosition.x += moveX * 5.0f;
	setPosition( CCPointMake(thisPosition.x, thisPosition.y) );

	mLastBackgroundMovePostion = touchPoint;
}

void GBackgroundLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event)
{
	
}

void GBackgroundLayer::Create(CCSprite* pSprite)
{
	mCharacterLinePostion = GetGameState()->GetGameHeight();	
	
	CCSize bgSize = pSprite->getContentSize();
	mCharacterLinePostion -= bgSize.height;
	
	pSprite->setAnchorPoint( CCPointMake(0, 0) );
	pSprite->setPosition( CCPointMake(0, mCharacterLinePostion) );
	addChild( pSprite );
	
}

void GBackgroundLayer::MoveBackground(float x, float y)
{
	
}