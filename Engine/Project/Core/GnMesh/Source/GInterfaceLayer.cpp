//
//  GInterfaceLayer.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 18..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GInterfaceLayer.h"

// 320*480

GInterfaceLayer::GInterfaceLayer()
{
	setIsTouchEnabled(true);
}


void GInterfaceLayer::Create(CCSprite* pSprite)
{
	if( pSprite == NULL )
		return;
	
	pSprite->setAnchorPoint( CCPointMake(0, 0) );
	setContentSize( pSprite->getContentSize() );
	addChild( pSprite, 0);
}

