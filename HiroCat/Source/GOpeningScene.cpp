#include "GamePCH.h"
#include "GOpeningScene.h"

static const gtuint gscLastPage = 4;

GOpeningLayer::GOpeningLayer() : mInputEvent( this, &GOpeningLayer::InputEvent )
{
	setIsTouchEnabled(true);
}

GOpeningLayer* GOpeningLayer::CreateOpeningLayer(gtuint uiPage)
{
	float width = GetGameState()->GetGameWidth();
	float height = GetGameState()->GetGameHeight();
	
	GOpeningLayer* openLayer = new GOpeningLayer();
	
	for( gtuint i = 0 ; i < gscLastPage ; i++ )
	{
		gchar fileName[GN_MAX_PATH] = { 0, };
		GnSprintf( fileName, sizeof( fileName ), "%d.png", uiPage + 1 );
		gstring fullFileName;
		GetFullPathFromWorkPath( fileName, fullFileName );
		CCSprite* bg = CCSprite::spriteWithFile( fullFileName.c_str() );
		bg->release();
	}

	gchar fileName[GN_MAX_PATH] = { 0, };
	GnSprintf( fileName, sizeof( fileName ), "%d.png", uiPage + 1 );
	gstring fullFileName;
	GetFullPathFromWorkPath( fileName, fullFileName );
	CCSprite* bg = CCSprite::spriteWithFile( fullFileName.c_str() );
	bg->setPosition( CCPointMake( width / 2, height / 2 ) );
	openLayer->addChild( bg );
	
	GnInterfaceGroup* group = GnNew GnInterfaceGroup();	
	group->SetRect( 0.0f, 0.0f, width, height );
	
	// next button
	GnIButton* buttons = GnNew GnIButton( "17_402.png" );
	SetUIPosition( buttons, 402.0f, 17.0f );
	group->AddChild( buttons );
	openLayer->AddChild( group, 1 );
	
	group->SubscribeClickedEvent( &openLayer->mInputEvent );
	openLayer->mCurrentPage = uiPage;
	return openLayer;
}

void GOpeningLayer::InputEvent(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::PUSH )
	{
		if( gscLastPage == mCurrentPage )
		{
			GScene::SetChangeSceneName( GScene::SCENENAME_STATE );
		}
		else
		{
			CCScene* openingScene = GOpeningScene::CreateLoadingScene( ++mCurrentPage );
			CCDirector::sharedDirector()->replaceScene( openingScene );
		}
	}
}

CCScene* GOpeningScene::CreateLoadingScene(gtuint uiPage)
{
	GOpeningScene* openingScene = new GOpeningScene();
	
	GOpeningLayer* openLayer = GOpeningLayer::CreateOpeningLayer( uiPage );
	openingScene->addChild( openLayer );

	CCScene* transScene = NULL;
	if( uiPage == 0 )
	{
		 transScene = CCTransitionFade::transitionWithDuration( 2.0f, openingScene, ccWHITE );
	}
	else if( uiPage < gscLastPage )
	{
		CCDirector::sharedDirector()->setDepthTest(true);
        transScene = CCTransitionPageTurn::transitionWithDuration( 1.0f, openingScene, false );		
	}
	else
	{
		CCDirector::sharedDirector()->setDepthTest( false );
		transScene = CCTransitionTurnOffTiles::transitionWithDuration( 1.0f, openingScene );
	}
	
	openingScene->release();
	openLayer->release();
	return transScene;
}
