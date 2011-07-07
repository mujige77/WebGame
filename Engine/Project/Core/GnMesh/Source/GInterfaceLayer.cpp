#include "GnMeshPCH.h"
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

