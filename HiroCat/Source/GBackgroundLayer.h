//
//  GBackgroundLayer.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GBackgroundLayer__
#define __HiroCat__GBackgroundLayer__
#include <cocos2d.h>

class GBackgroundLayer : public GLayer
{
protected:
	float mCharacterLinePostion;
	CCPoint mLastBackgroundMovePostion;
	
public:
	GBackgroundLayer();
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
	
	void MoveBackground(float x, float y);
	
public:
	inline static GBackgroundLayer* Create(const gchar* pcName) {
		CCSprite* sprite = CCSprite::spriteWithFile( pcName );		
		if( sprite  == NULL )
			return NULL;
		GBackgroundLayer* layer = new GBackgroundLayer();
		layer->Create( sprite );
		return layer;
	}
	
	inline float GetCharacterLinePostion() {
		return mCharacterLinePostion;
	}
	
protected:
	void Create(CCSprite* pSprite);

};

#endif
