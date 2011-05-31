#include "GnMeshPCH.h"
#include "GnCocosScene.h"


GnCocosScene* GnCocosScene::CreateScene(gint32 uiID, GnLayer* pState, bool bAtuoRelease)
{
	GnCocosScene* s = new GnCocosScene( pState );
	s->addChild( pState );
	CCDirector::sharedDirector()->runWithScene(s);
	return s;
}

GnCocosScene::GnCocosScene(GnLayer* pState) : mpState(pState)
{
	
}

GnCocosScene::~GnCocosScene()
{
	mpState->release();
}