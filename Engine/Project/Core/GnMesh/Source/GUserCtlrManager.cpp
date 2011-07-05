//
//  GUserCtlrManager.cpp
//  Core
//
//  Created by Max Yoon on 11. 6. 26..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//
#include "GnGamePCH.h"
#include "GUserCtlrManager.h"
#include "GUserController.h"
#include "GnInterfaceGroup.h"
#include "GnIButton.h"
#include "GCollectComponentHeader.h"

GUserCtlrManager::GUserCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer)
	: GActorCtlrManager( pActorLayer ), mpInterfaceLayer( pInterfaceLayer )
{
	//InitUI();
}
GUserCtlrManager::~GUserCtlrManager()
{
}

void GUserCtlrManager::Update(float fDeltaTime)
{
	mpUserCtlr->Update( fDeltaTime );
	UpdateBackgroundLayer();
}

void GUserCtlrManager::UpdateBackgroundLayer()
{
	float movePoint = GetGameState()->GetGameWidth() / 2;
	GnVector2 userPos = mpUserCtlr->GetMesh()->GetPositionFromImageCenter();
	if( movePoint < userPos.x )
	{
		GActionMove* move = (GActionMove*)mpUserCtlr->GetCurrentAction( GAction::ACTION_MOVE );
		if( move == NULL )
			return;
		
		if( move->GetMoveLeft() )
		{
			CCSize bgSize = GetActorLayer()->getContentSize();
			if( bgSize.width - movePoint >= userPos.x )
				GetActorLayer()->MoveLayer( move->GetMoveRange().x, 0.0f );
		}
		else if( move->GetMoveRight() )
		{
			GetActorLayer()->MoveLayer( -move->GetMoveRange().x, 0.0f );
		}
	}
}

void GUserCtlrManager::Init()
{
	mpUserCtlr = GUserController::Create( "C1", 1 );
	GActionMove* move = (GActionMove*)mpUserCtlr->GetActionComponent( GAction::ACTION_MOVE );
	GetGameEnvironment()->UserMove( move );
	GetGameEnvironment()->SetStartPositionToActor( mpUserCtlr, 0 );
	GetActorLayer()->AddChild( mpUserCtlr->GetMesh()
		, GetGameState()->GetGameHeight() - mpUserCtlr->GetMesh()->GetPosition().y );
	move->SetActorLayer( GetActorLayer() );
	
	mMoveInputEvent.Initialize( this, &GUserCtlrManager::Move );
	
	
	mButtons[GActionMove::MOVELEFT] = GnNew GnIButton( "Controll/14_247.png", NULL, NULL );
	float pointX = 14;
	float pointY = 247;
	GnVector2 vec = mButtons[GActionMove::MOVELEFT]->GetContentSize();	
	mButtons[GActionMove::MOVELEFT]->SetUIPoint( pointX, pointY );	
	mButtons[GActionMove::MOVELEFT]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	
    mButtons[GActionMove::MOVERIGHT] = GnNew GnIButton( "Controll/58_247.png", NULL, NULL );
	pointX = 58;
	pointY = 247;
	vec = mButtons[GActionMove::MOVERIGHT]->GetContentSize();
	mButtons[GActionMove::MOVERIGHT]->SetUIPoint( pointX, pointY );
	mButtons[GActionMove::MOVERIGHT]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	
    mButtons[GActionMove::MOVEUP] = GnNew GnIButton( "Controll/37_223.png", NULL, NULL );	
	pointX = 37;
	pointY = 223;
	vec = mButtons[GActionMove::MOVEUP]->GetContentSize();
	mButtons[GActionMove::MOVEUP]->SetUIPoint( pointX, pointY );
	mButtons[GActionMove::MOVEUP]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	

	mButtons[GActionMove::MOVEDOWN] = GnNew GnIButton( "Controll/38_268.png", NULL, NULL );
	pointX = 37;
	pointY = 268;
	vec = mButtons[GActionMove::MOVEDOWN]->GetContentSize();
	mButtons[GActionMove::MOVEDOWN]->SetUIPoint( pointX, pointY );
	mButtons[GActionMove::MOVEDOWN]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );

	
	GnInterfaceGroup* pGroup = GnNew GnInterfaceGroup();
	pGroup->SubscribeClickedEvent( &mMoveInputEvent );
	pGroup->SetRect( 0.5f, 219.0f, 0.5f+100.0f, 219.0f+100.0f );
	for (gtuint i = 0; i < NUM_BUTTON ; i++ )
	{
		pGroup->AddChild( mButtons[i] );
	}

	mpInterfaceLayer->AddChild( pGroup, 1 );
}

void GUserCtlrManager::Move(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::PUSHUP )
	{
		mpUserCtlr->RemoveCurrentComponent( GAction::ACTION_MOVE );
		mpUserCtlr->GetActionComponent( GAction::ACTION_STAND )->AttachCompentToController();
		return;
	}
	
	if( mpUserCtlr->IsEnableMove() == false )
		return;
		
	GActionMove* move = (GActionMove*)mpUserCtlr->GetActionComponent( GAction::ACTION_MOVE );
	if( move == NULL )
		return;
	
	if( mpUserCtlr->GetCurrentAction( move->GetActionType() ) == NULL )
		move->AttachCompentToController();
	
	
	for ( gtuint i = 0; i < GActionMove::MOVE_MAX; i++)
	{
		if( mButtons[i] == pInterface )
			move->SetMove( i, true );
	}
	GetGameEnvironment()->UserMove( mpUserCtlr->GetActionComponent( GAction::ACTION_MOVE ) );
}