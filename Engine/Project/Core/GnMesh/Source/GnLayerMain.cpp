#include "GnMeshPCH.h"
#include "GnLayerMain.h"

GnLayerMain::GnLayerMain() : mpBackground(NULL)
{

}

bool GnLayerMain::CreateBackgroundFromFile(const gchar* fileName)
{
	if( mpBackground )
	{
		removeChild( mpBackground, true );
	}

	GnReal2DMesh* mesh = CCSprite::spriteWithFile( fileName );
	if( mesh == NULL )
		return false;
	mesh->setAnchorPoint( CCPointMake(0,0) );
	mpBackground = new GnLayerBackground();
	mpBackground->addChild( mesh, 0 );
	mpBackground->autorelease();

	addChild( mpBackground );
	return true;
}