//
//  GInterfaceLayer.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 18..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GInterfaceLayer__
#define __HiroCat__GInterfaceLayer__

class GInterfaceLayer : public GLayer
{
public:
	inline static GInterfaceLayer* Create(const gchar* pcName) {
		CCSprite* sprite = CCSprite::spriteWithFile( pcName );		
		if( sprite == NULL )
			return NULL;
		GInterfaceLayer* layer = new GInterfaceLayer();
		layer->Create( sprite );
		return layer;
	}
	
protected:
	void Create(CCSprite* pSprite);
	
};

#endif
