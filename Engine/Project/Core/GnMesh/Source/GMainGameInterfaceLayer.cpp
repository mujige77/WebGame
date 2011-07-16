#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GMainGameInterfaceLayer.h"
#include "GnIButton.h"
#include "GEnergyBar.h"
#include "GnInterfaceGroup.h"

GMainGameInterfaceLayer::GMainGameInterfaceLayer() : mForcesButtonInfos( GInterfaceLayer::FORCESBT_NUM )
	, mpForcesButtonGroup( NULL ), mpForcesEnergyBar( NULL )
	, mForcesInputEvent( this, &GMainGameInterfaceLayer::InputForcesButton )
{
	
}
GnInterfaceGroup* GMainGameInterfaceLayer::CreateInterface(gtuint uiIndex
	, GnBaseSlot2<GnInterface*, GnIInputEvent*>* pReceiveSlot)
{
	GnInterfaceGroup* pGroup = NULL;
	switch (uiIndex)
	{
		case UI_MAIN_CONTROLLERS:
		{
			pGroup = CreateMainController();
		}
		break;
		case UI_MAIN_FORCESBUTTONS:
		{
			pGroup = CreateMainForcesButtons();			
			pGroup->SubscribeClickedEvent( &mForcesInputEvent );
			mpForcesButtonGroup = pGroup;
		}
		break;
		case UI_MAIN_SKILL:
		{
			pGroup = CreateMainSkillButtons();
		}
		break;
	}
	
	if( pGroup )
	{
		pGroup->SubscribeClickedEvent( pReceiveSlot );
	}
	return pGroup;
}

void GMainGameInterfaceLayer::Update(float fTime)
{
	if( mpForcesButtonGroup )
		mpForcesButtonGroup->Update( fTime );
	
	UpdateButtonState();
}

GnInterfaceGroup* GMainGameInterfaceLayer::CreateMainController()
{
	GnInterfaceGroup* group = NULL;
	return group;
}

GnInterfaceGroup* GMainGameInterfaceLayer::CreateMainForcesButtons()
{
	GnIButton* buttons[FORCESBT_NUM];
	buttons[BT_C2] = GnNew GnIButton( "Controll/125_223.png", NULL, "Controll/125_223G.png" );
	float pointX = 125;
	float pointY = 223;
	GnVector2 vec = buttons[BT_C2]->GetContentSize();	
	buttons[BT_C2]->SetUIPoint( pointX, pointY );	
	buttons[BT_C2]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
		
	
    buttons[BT_C3] = GnNew GnIButton( "Controll/170_223.png", NULL, "Controll/170_223G.png" );
	pointX = 170;
	pointY = 223;
	vec = buttons[BT_C3]->GetContentSize();
	buttons[BT_C3]->SetUIPoint( pointX, pointY );
	buttons[BT_C3]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );

	
    buttons[BT_C4] = GnNew GnIButton( "Controll/215_223.png", NULL, "Controll/215_223G.png" );	
	pointX = 215;
	pointY = 223;
	vec = buttons[BT_C4]->GetContentSize();
	buttons[BT_C4]->SetUIPoint( pointX, pointY );
	buttons[BT_C4]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );

	
	buttons[BT_C5] = GnNew GnIButton( "Controll/260_223.png", NULL, "Controll/260_223G.png"
		, GnIButton::TYPE_DISABLE );
	pointX = 260;
	pointY = 223;
	vec = buttons[BT_C5]->GetContentSize();
	buttons[BT_C5]->SetUIPoint( pointX, pointY );
	buttons[BT_C5]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );

	
	buttons[BT_C6] = GnNew GnIButton( "Controll/305_223.png", NULL, "Controll/305_223G.png"
		, GnIButton::TYPE_DISABLE );
	pointX = 305;
	pointY = 223;
	vec = buttons[BT_C6]->GetContentSize();	
	buttons[BT_C6]->SetUIPoint( pointX, pointY );	
	buttons[BT_C6]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );

	
    buttons[BT_C7] = GnNew GnIButton( "Controll/125_268.png", NULL, "Controll/125_268G.png"
		,GnIButton::TYPE_DISABLE );
	pointX = 125;
	pointY = 268;
	vec = buttons[BT_C7]->GetContentSize();
	buttons[BT_C7]->SetUIPoint( pointX, pointY );
	buttons[BT_C7]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );

	
    buttons[BT_C8] = GnNew GnIButton( "Controll/170_268.png", NULL, "Controll/170_268G.png"
		, GnIButton::TYPE_DISABLE );
	pointX = 170;
	pointY = 268;
	vec = buttons[BT_C8]->GetContentSize();
	buttons[BT_C8]->SetUIPoint( pointX, pointY );
	buttons[BT_C8]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );

	
	buttons[BT_C9] = GnNew GnIButton( "Controll/215_268.png", NULL, "Controll/215_268G.png",
		GnIButton::TYPE_DISABLE );
	pointX = 215;
	pointY = 268;
	vec = buttons[BT_C9]->GetContentSize();
	buttons[BT_C9]->SetUIPoint( pointX, pointY );
	buttons[BT_C9]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );

	
	buttons[BT_C10] = GnNew GnIButton( "Controll/260_268.png", NULL, "Controll/260_268G.png",
		GnIButton::TYPE_DISABLE );
	pointX = 260;
	pointY = 268;
	vec = buttons[BT_C10]->GetContentSize();
	buttons[BT_C10]->SetUIPoint( pointX, pointY );
	buttons[BT_C10]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );

	
	buttons[BT_C11] = GEnergyBar::Create( 100, 0.5, "Controll/305_268.png" );
	pointX = 305;
	pointY = 268;
	vec = buttons[BT_C11]->GetContentSize();
	buttons[BT_C11]->SetUIPoint( pointX, pointY );
	buttons[BT_C11]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	mpForcesEnergyBar = (GEnergyBar*)buttons[BT_C11];
	
	GnInterfaceGroup* pGroup = GnNew GnInterfaceGroup();
	pGroup->SetRect( 120.0f, 219.0f, 120.0f+232.0f, 219.0f+100.0f );
	for (gtuint i = 0; i < FORCESBT_NUM ; i++ )
	{
		pGroup->AddChild( buttons[i] );
	}
	
	AddChild( pGroup, 1 );
	
	SetForcesButtonInfo( buttons );
	return pGroup;
}
GnInterfaceGroup* GMainGameInterfaceLayer::CreateMainSkillButtons()
{
	GnInterfaceGroup* group = NULL;
	return group;
}

bool GMainGameInterfaceLayer::SetForcesButtonInfo(GnIButton** ppButtons)
{
	for (gtuint i = 0; i < FORCESBT_NUM ; i++ )
	{
		ppButtons[i]->SetIsCantPush( true );
		if( BT_C11 != i )
		{
			ppButtons[i]->SetIsDisableCantpushBlind( false );
			ppButtons[i]->SetIsEnableCoolTime( true );
			ppButtons[i]->SetCoolTime( (float)i * 0.5f + 0.1f );
		}
		ButtonInfo& btInfo = mForcesButtonInfos.GetAt( i );
		btInfo.SetButton( ppButtons[i] );
		btInfo.SetCanPushEnergy( i * 5 );
		btInfo.SetCoolTime( (float)i * 0.5f );
		
	}
	return true;
}

void GMainGameInterfaceLayer::UpdateButtonState()
{
	const gtuint num = FORCESBT_NUM - 1;
	for (gtuint i = 0; i < num ; i++ )
	{
		ButtonInfo& btInfo = mForcesButtonInfos.GetAt( i );
		if( btInfo.GetButton()->IsDisable() )
			continue;
		if( mpForcesEnergyBar->GetCurrentEnergy() >= btInfo.GetCanPushEnergy() )
		{
			btInfo.GetButton()->SetIsCantPush( false );
		}
		else
		{
			if( btInfo.GetButton()->IsCantPush() == false )
				btInfo.GetButton()->SetIsCantPush( true );
		}
	}
}

void GMainGameInterfaceLayer::InputForcesButton(GnInterface* pInterface, GnIInputEvent* pEvent)
{
	if( pEvent->GetEventType() == GnIInputEvent::PUSH )
	{
		for (gtuint i = 0; i < FORCESBT_NUM ; i++ )
		{
			ButtonInfo& btInfo = mForcesButtonInfos.GetAt( i );		
			if( btInfo.GetButton() == pInterface )
			{
				mpForcesEnergyBar->SetCurrentEnergy( 
					mpForcesEnergyBar->GetCurrentEnergy() - btInfo.GetCanPushEnergy() );
				break;
			}
		}
	}
}