#include "GnGamePCH.h"
#include "GSelectStageBGLayer.h"

GSelectStageBGLayer* GSelectStageBGLayer::CreateBackground()
{
	GSelectStageBGLayer* background = new GSelectStageBGLayer();
	if( background->InitBackground() == false )
	{
		delete background;
		return NULL;
	}
	return background;	
}

bool GSelectStageBGLayer::InitBackground()
{
	gstring fileName;
	GetFullPathFromWorkPath( "StageScene/0_0.png", fileName );
	GnReal2DMesh* mesh = GnReal2DMesh::spriteWithFile( fileName.c_str() );
	mesh->setPosition( CCPointMake( GetGameState()->GetGameWidth() / 2
		, GetGameState()->GetGameHeight() / 2 ) );
	addChild( mesh, 0 );
	return true;
}