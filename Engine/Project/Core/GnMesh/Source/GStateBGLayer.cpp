#include "GnGamePCH.h"
#include "GStateBGLayer.h"

GStateBGLayer* GStateBGLayer::CreateBackground()
{
	GStateBGLayer* background = new GStateBGLayer();
	if( background->InitBackground() == false )
	{
		delete background;
		return NULL;
	}
	return background;	
}

bool GStateBGLayer::InitBackground()
{
	gstring fileName;
	GetFullPathFromWorkPath( "Upgrade/0_0.png", fileName );
	GnReal2DMesh* mesh = GnReal2DMesh::spriteWithFile( fileName.c_str() );
	mesh->setPosition( CCPointMake( GetGameState()->GetGameWidth() / 2
		, GetGameState()->GetGameHeight() / 2 ) );
	addChild( mesh, 0 );
	return true;
}
