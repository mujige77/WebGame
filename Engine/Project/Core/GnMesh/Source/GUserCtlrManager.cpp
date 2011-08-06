#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GUserCtlrManager.h"
#include "GUserController.h"
#include "GnIButton.h"
#include "GInterfaceLayer.h"
#include "GCollectComponentHeader.h"
#include "GInfoBasic.h"
#include "GActionAttackCheck.h"

GUserCtlrManager* GUserCtlrManager::CreateActorCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer)
{
	GUserCtlrManager* ctlrManager = GnNew GUserCtlrManager(pActorLayer, pInterfaceLayer);
	return ctlrManager;
}
														   
GUserCtlrManager::GUserCtlrManager(GLayer* pActorLayer, GLayer* pInterfaceLayer)
	: GActorCtlrManager( pActorLayer ), mpInterfaceLayer( (GInterfaceLayer*)pInterfaceLayer )
	, mMoveInputEvent( this, &GUserCtlrManager::Move )
{
	//InitUI();
}
GUserCtlrManager::~GUserCtlrManager()
{
}

void GUserCtlrManager::Update(float fDeltaTime)
{
	GActorCtlrManager::Update( fDeltaTime );

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
	AddActorCtlr( mpUserCtlr );
	
	GetGameEnvironment()->UserMove( mpUserCtlr );
	GetGameEnvironment()->SetStartPositionToActor( mpUserCtlr, 0 );
	GetGameEnvironment()->InitActorControllerAction( GetActorLayer(), mpUserCtlr );	
	
	mMoveInputEvent.Initialize( this, &GUserCtlrManager::Move );
	
	mpButtonGroup = mpInterfaceLayer->CreateInterface( (gtuint)GInterfaceLayer::UI_MAIN_CONTROLLERS,
		  &mMoveInputEvent );
	

}

void GUserCtlrManager::Move(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::MOVE )
		return;
	
	// stop check
	bool setStand = true;
	for ( gtuint i = 0; i < GActionMove::MOVE_MAX; i++ )
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
	move->SetMoveX( mpButtonGroup->GetChild( GActionMove::MOVELEFT )->IsPush()
		, mpButtonGroup->GetChild( GActionMove::MOVERIGHT )->IsPush() );
	move->SetMoveY( mpButtonGroup->GetChild( GActionMove::MOVEUP )->IsPush()
		, mpButtonGroup->GetChild( GActionMove::MOVEDOWN )->IsPush() );
	GetGameEnvironment()->UserMove( mpUserCtlr );
}

gint32 GUserCtlrManager::GetUserCurrentHP()
{
	GCurrentActorInfo* curInfo = mpUserCtlr->GetCurrentInfo();
	return curInfo->GetHP();
}