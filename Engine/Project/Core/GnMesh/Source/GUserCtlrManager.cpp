#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GUserCtlrManager.h"
#include "GUserController.h"
#include "GnIButton.h"
#include "GInterfaceLayer.h"
#include "GCollectComponentHeader.h"
#include "GInfoBasic.h"
#include "GActionAttackCheck.h"
#include "GFarAttack.h"
#include "GBoltAttack.h"

GUserCtlrManager* GUserCtlrManager::CreateActorCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer)
{
	GUserCtlrManager* ctlrManager = GnNew GUserCtlrManager(pActorLayer, pInterfaceLayer);
	return ctlrManager;
}
														   
GUserCtlrManager::GUserCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer)
	: GActorCtlrManager( pActorLayer ), mpInterfaceLayer( (GInterfaceLayer*)pInterfaceLayer )
	, mMoveInputEvent( this, &GUserCtlrManager::Move ), mSkillInputEvent( this, &GUserCtlrManager::SkillInput )
{
	//InitUI();
}
GUserCtlrManager::~GUserCtlrManager()
{
}

void GUserCtlrManager::Update(float fDeltaTime)
{
	GActorCtlrManager::Update( fDeltaTime );

	GetGameEnvironment()->UserMove( mpUserCtlr );
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
	float saveScale = GetGameState()->GetGameScale();
	GetGameState()->SetGameScale( DEFAULT_SCALE );
	mpUserCtlr = GUserController::Create( "C1", 1 );
	GetGameState()->SetGameScale( saveScale );	
	
	GetGameEnvironment()->CreateActorControllerBasicAction( mpUserCtlr );
	GetGameEnvironment()->UserMove( mpUserCtlr );
	GetGameEnvironment()->InitActorControllerAction( GetActorLayer(), mpUserCtlr );	
	GetGameEnvironment()->SetStartPositionToActor( mpUserCtlr, 1, 0 );	
	
	GnVector2 pos = mpUserCtlr->GetPosition();
	pos.x = 50.0f;
	mpUserCtlr->SetPosition( pos );
	AddActorCtlr( mpUserCtlr );
	
	mpButtonGroup = mpInterfaceLayer->CreateInterface( (gtuint)GInterfaceLayer::UI_MAIN_CONTROLLERS,
		  &mMoveInputEvent );
	
	mpInterfaceLayer->CreateInterface( (gtuint)GInterfaceLayer::UI_MAIN_SKILL,
		&mSkillInputEvent );

}

gint32 GUserCtlrManager::GetUserCurrentHP()
{
	GCurrentActorInfo* curInfo = mpUserCtlr->GetCurrentInfo();
	return curInfo->GetHP();
}

void GUserCtlrManager::Move(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::MOVE )
		return;
	
	// stop check
	bool setStand = true;
	for ( gtuint i = 0; i < GInterfaceLayer::MOVE_NUM; i++ )
	{
		if( mpButtonGroup->GetChild( i )->IsPush() )
		{
			setStand = false;
			break;
		}
	}	
	if( setStand )
	{
		mpUserCtlr->RemoveCurrentAction( GAction::ACTION_MOVE );
		mpUserCtlr->AddCurrentAction( mpUserCtlr->GetActionComponent( GAction::ACTION_STAND ) );
		return;
	}
	
	if( mpUserCtlr->IsEnableMove() == false )
		return;
	
	// move		
	GActionMove* move = (GActionMove*)mpUserCtlr->GetActionComponent( GAction::ACTION_MOVE );
	if( move == NULL )
		return;
	
	if( mpUserCtlr->GetCurrentAction( move->GetActionType() ) == NULL )
	{
		mpUserCtlr->AddCurrentAction( move );
	}
	
	move->CleanMove();
	bool moveLeft = mpButtonGroup->GetChild( GInterfaceLayer::MOVELEFT )->IsPush() 
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVELEFTSMALL )->IsPush() 
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVELEFTUP )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVELEFTUPSMALL )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVELEFTDOWN )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVELEFTDOWNSMALL )->IsPush();
	bool moveRight = mpButtonGroup->GetChild( GInterfaceLayer::MOVERIGHT )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVERIGHTSMALL )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVERIGHTUP )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVERIGHTUPSMALL )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVERIGHTDOWN )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVERIGHTDOWNSMALL )->IsPush();
	move->SetMoveX( moveLeft, moveRight );
	
	bool moveUp = mpButtonGroup->GetChild( GInterfaceLayer::MOVEUP )->IsPush() 
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVEUPSMALL )->IsPush() 
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVELEFTUP )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVELEFTUPSMALL )->IsPush()
		||  mpButtonGroup->GetChild( GInterfaceLayer::MOVERIGHTUP )->IsPush()
		||  mpButtonGroup->GetChild( GInterfaceLayer::MOVERIGHTUPSMALL )->IsPush(); 
	bool moveDown = mpButtonGroup->GetChild( GInterfaceLayer::MOVEDOWN )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVEDOWNSMALL )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVELEFTDOWN )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVELEFTDOWNSMALL )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVERIGHTDOWN )->IsPush()
		|| mpButtonGroup->GetChild( GInterfaceLayer::MOVERIGHTDOWNSMALL )->IsPush();
	
	move->SetMoveY( moveUp, moveDown );
}

void GUserCtlrManager::SkillInput(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() != GnIInputEvent::PUSH )
		return;

	GFarAttack* attack =  GFarAttack::CreateAttack( (gtuint)pInterface->GetTegID() );
	if( attack && attack->GetBasicStartPosition() == GFarAttack::eUserPosition )
	{
		attack->SetFilpX( mpUserCtlr->GetMesh()->GetFlipX() );
		attack->SetPosition( mpUserCtlr->GetPosition() );
		AddFarAttack( attack, (int)(GetGameState()->GetGameHeight() - mpUserCtlr->GetPosition().y) );
	}
	else if( attack )
	{
		GnVector2ExtraData* pos = NULL;
		if( eIndexItemFire != pInterface->GetTegID() )
			pos = (GnVector2ExtraData*)
				mpUserCtlr->GetMesh()->GetExtraDataFromType( GExtraData::EXTRA_FARATTACK_POSITION );
		else
			pos = (GnVector2ExtraData*)
				mpUserCtlr->GetMesh()->GetExtraDataFromType( GExtraData::EXTRA_HEROFIRE_POSITION );
		if( pos )
		{
			GnVector2 effectPos = mpUserCtlr->GetMesh()->GetPosition() + pos->GetValueVector2();
			attack->SetFilpX( mpUserCtlr->GetMesh()->GetFlipX() );
			attack->SetPosition( effectPos );
			AddFarAttack( attack, (int)(GetGameState()->GetGameHeight() - mpUserCtlr->GetPosition().y) );
		}
	}
}