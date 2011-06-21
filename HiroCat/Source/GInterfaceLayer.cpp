//
//  GInterfaceLayer.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 18..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GamePCH.h"
#include "GInterfaceLayer.h"


void GInterfaceLayer::Create(CCSprite* pSprite)
{
	pSprite = CCSprite::spriteWithFile( "./Data/Background/interface_3GS.png" );
	pSprite->setAnchorPoint( CCPointMake(0, 0) );
	addChild( pSprite );
}