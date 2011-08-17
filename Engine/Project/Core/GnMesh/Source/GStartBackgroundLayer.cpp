#include "GnGamePCH.h"
#include "GStartBackgroundLayer.h"

GStartBackgroundLayer* GStartBackgroundLayer::CreateBackground()
{
	GStartBackgroundLayer* background = new GStartBackgroundLayer();
	if( background->InitBackground() == false || background->InitClouds() == false )
	{
		delete background;
		return NULL;
	}
	return background;
}

bool GStartBackgroundLayer::InitBackground()
{
	gstring fileName;
	GetFullPathFromWorkPath( "StartScene/0_60.png", fileName );
	GnReal2DMesh* mesh = GnReal2DMesh::spriteWithFile( fileName.c_str() );
	mesh->setPosition( CCPointMake( GetGameState()->GetGameWidth() / 2
		, GetGameState()->GetGameHeight() / 2 ) );
	addChild( mesh, 0 );
	
	GetFullPathFromWorkPath( "StartScene/23_50.png", fileName );
	mesh = GnReal2DMesh::spriteWithFile( fileName.c_str() );
	CCSize size = mesh->getContentSize();
	mesh->setPosition( CCPointMake( 23 + ( size.width / 2 )
		, GetGameState()->GetGameHeight() - 50 - ( size.height / 2 ) ) );
	addChild( mesh, 20 );
	return true;
}

bool GStartBackgroundLayer::InitClouds()
{
	float centerX = GetGameState()->GetGameWidth();
	
//	for ( gtuint i = 0; i < NUM_CLOUD; i++)
//	{
//		gchar fileName[64] = { 0, };
//		GnSprintf( fileName, sizeof( fileName ), "StartScene/%d.png", i + 1 );
//		gstring fullPath;
//		GetFullPathFromWorkPath( fileName, fullPath );
//		mpCloudsMeshs[i] = GnReal2DMesh::spriteWithFile( fullPath.c_str() );		
//		CCSize size = mpCloudsMeshs[i]->getContentSize();
//		mpCloudsMeshs[i]->setPosition( CCPointMake( centerX * i, size.height * 0.5f ) );
//		CCFiniteTimeAction*  action = CCSequence::actions(
//			CCMoveBy::actionWithDuration( 10444.0f + ( 100.0f * ( NUM_CLOUD - i ) ) , CCPointMake( -GetGameState()->GetGameWidth() * i, 0 ) ),
//			CCCallFunc::actionWithTarget( this, callfunc_selector( GStartBackgroundLayer::CloudActionCallback ) ), 
//			NULL );
//		mpCloudsMeshs[i]->runAction( action );
//		addChild( mpCloudsMeshs[i], 1 + i );
//	}	

	gstring fullPath;
	GetFullPathFromWorkPath( "StartScene/5.png", fullPath );
	GnReal2DMesh* mesh = GnReal2DMesh::spriteWithFile( fullPath.c_str() );
	CCSize size = mesh->getContentSize();
	mesh->setPosition( CCPointMake( centerX, size.height * 0.5f ) );
		CCFiniteTimeAction*  action = CCSequence::actions(
		CCMoveBy::actionWithDuration( 304.0f , CCPointMake( -GetGameState()->GetGameWidth(), 0 ) ),
		CCCallFunc::actionWithTarget( this, callfunc_selector( GStartBackgroundLayer::CloudActionCallback ) ), NULL );
	mesh->runAction( action );
	addChild( mesh, 1 );
	return true;
}

void GStartBackgroundLayer::CloudActionCallback(CCNode* pSender)
{
	float startX = GetGameState()->GetGameWidth() + GetGameState()->GetGameWidth();
	GnReal2DMesh* mesh = (GnReal2DMesh*)pSender;
	CCSize size = mesh->getContentSize();
	mesh->setPosition( CCPointMake( startX, size.height * 0.5f ) );
	CCFiniteTimeAction*  action = CCSequence::actions(
		CCMoveBy::actionWithDuration( 304.0f , CCPointMake( -GetGameState()->GetGameWidth(), 0 ) ),
		CCCallFunc::actionWithTarget( this, callfunc_selector( GStartBackgroundLayer::CloudActionCallback ) ), NULL );
	mesh->runAction( action );
//	for ( gtuint i = 0; i < NUM_CLOUD; i++ )
//	{
//		if( mpCloudsMeshs[i] == pSender )
//		{
//			CCFiniteTimeAction*  action = CCSequence::actions(
//				CCMoveBy::actionWithDuration( 10444.0f + ( 100.0f * ( NUM_CLOUD - i ) ) , CCPointMake( -startX * 1.5f, 0.0f ) ),
//				CCCallFunc::actionWithTarget( this, callfunc_selector( GStartBackgroundLayer::CloudActionCallback ) ), 
//				NULL );
//			CCSize size = mpCloudsMeshs[i]->getContentSize();
//			mpCloudsMeshs[i]->setPosition( CCPointMake( startX, size.height * 0.5f ) );
//			mpCloudsMeshs[i]->runAction( action );
//		}
//	}
	
}