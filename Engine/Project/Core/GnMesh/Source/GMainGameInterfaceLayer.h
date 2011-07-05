//
//  GMainGameInterfaceLayer.h
//  Core
//
//  Created by Max Yoon on 11. 7. 1..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GMainGameInterfaceLayer__
#define __Core__GMainGameInterfaceLayer__

#include "GInterfaceLayer.h"

class GMainGameInterfaceLayer : public GInterfaceLayer
{
public:
	inline static GInterfaceLayer* Create(const gchar* pcName) {
		CCSprite* sprite = CCSprite::spriteWithFile( pcName );		
		if( sprite == NULL )
			return NULL;
		GInterfaceLayer* layer = new GMainGameInterfaceLayer();
		layer->Create( sprite );
		return layer;
	}
	
	
public:
	GnInterfaceGroup* CreateInterface(gtuint uiIndex
		, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pReceiveSlot);
	
protected:
	GnInterfaceGroup* CreateMainController();
	GnInterfaceGroup* CreateMainForcesButtons();
	GnInterfaceGroup* CreateMainSkillButtons();
};

#endif
