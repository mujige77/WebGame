//
//  GBackgroundLayer.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GBackgroundLayer.h"

GBackgroundLayer::GBackgroundLayer()
{
	setIsTouchEnabled(true);
}

void GBackgroundLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
   CCSetIterator it = pTouches->begin();
   CCTouch* touch = (CCTouch*)(*it);
   CCPoint touchPoint = touch->locationInView( touch->view() );
   
   if( mBackgroundRect.ContainsPoint( (gint)touchPoint.x, (gint)touchPoint.y ) == false ) 
	  return;

   mLastBackgroundMovePostion = touchPoint;
}

void GBackgroundLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* event)
{
   CCSetIterator it = pTouches->begin();
   CCTouch* touch = (CCTouch*)(*it);

   CCPoint touchPoint = touch->locationInView( touch->view() );
   if( mBackgroundRect.ContainsPoint( (gint)touchPoint.x, (gint)touchPoint.y ) == false )
	  return;
   
   float moveX = touchPoint.x - mLastBackgroundMovePostion.x; 	
   mLastBackgroundMovePostion = touchPoint;

   MoveLayer( moveX * 5.0f, 0.0f );   
}

void GBackgroundLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event)
{
	
}

void GBackgroundLayer::Create(CCSprite* pSprite)
{
   CCSize bgSize = pSprite->getContentSize();
	
   pSprite->setAnchorPoint( CCPointMake(0, 0) );
   pSprite->setPosition( CCPointMake(0, GetGameState()->GetGameHeight() - bgSize.height ) );
   addChild( pSprite );
   
   setContentSize( pSprite->getContentSize() );
   setAnchorPoint( CCPointZero );
   
   mBackgroundRect.left = 0;
   mBackgroundRect.top = 0;
   mBackgroundRect.right = bgSize.width;
   mBackgroundRect.bottom = bgSize.height;
}

void GBackgroundLayer::MoveLayer(float fDeltaX, float fDeltaY)
{
   CCSize size = getContentSize();
   CCPoint thisPosition = getPosition();
   float maxLeftMovePos = GetGameState()->GetGameWidth() - size.width;
   if( fDeltaX < 0.0f &&  thisPosition.x <= maxLeftMovePos ) // left check
	  return;
   
   if( fDeltaX > 0.0f && thisPosition.x >= 0.0f )
	  return;

   thisPosition.x += fDeltaX;

   if( fDeltaX > 0.0f && thisPosition.x >= 0.0f )
	  thisPosition.x = 0;
   if( fDeltaX < 0.0f &&  thisPosition.x <= maxLeftMovePos ) // left check
	  thisPosition.x = maxLeftMovePos;
   
   setPosition( CCPointMake(thisPosition.x, thisPosition.y) );
}