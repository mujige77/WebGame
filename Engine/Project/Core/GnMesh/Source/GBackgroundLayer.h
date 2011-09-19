#ifndef __HiroCat__GBackgroundLayer__
#define __HiroCat__GBackgroundLayer__
#include <cocos2d.h>

class GBackgroundLayer : public GLayer
{
protected:
	CCPoint mLastBackgroundMovePostion;
	GnIRect mBackgroundRect;
	bool mIsMoveBackground;
	CCTouch* mpCurrentTouch;
public:
	inline static GBackgroundLayer* Create(const gchar* pcName) {
		CCSprite* sprite = CCSprite::spriteWithFile( pcName );		
		if( sprite  == NULL )
			return NULL;
		GBackgroundLayer* layer = new GBackgroundLayer();
		layer->Create( sprite );
		return layer;
	}

public:
	GBackgroundLayer();	
	virtual void MoveLayer(float fDeltaX, float fDeltaY);
						
protected:
	void Create(CCSprite* pSprite);
	
protected:
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
};

#endif
