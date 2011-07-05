//
//  GMainGameInterfaceLayer.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 1..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GMainGameInterfaceLayer.h"
#include "GnIButton.h"
#include "GnInterfaceGroup.h"

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

GnInterfaceGroup* GMainGameInterfaceLayer::CreateMainController()
{
	GnInterfaceGroup* group = NULL;
	return group;
}
GnInterfaceGroup* GMainGameInterfaceLayer::CreateMainForcesButtons()
{
	
	GnIButton* mButtons[FORCESBT_NUM];
	mButtons[BT_C2] = GnNew GnIButton( "Controll/125_223.png", NULL, "Controll/125_223G.png" );
	float pointX = 125;
	float pointY = 223;
	GnVector2 vec = mButtons[BT_C2]->GetContentSize();	
	mButtons[BT_C2]->SetUIPoint( pointX, pointY );	
	mButtons[BT_C2]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	
    mButtons[BT_C3] = GnNew GnIButton( "Controll/170_223.png", NULL, "Controll/170_223G.png" );
	pointX = 170;
	pointY = 223;
	vec = mButtons[BT_C3]->GetContentSize();
	mButtons[BT_C3]->SetUIPoint( pointX, pointY );
	mButtons[BT_C3]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	
    mButtons[BT_C4] = GnNew GnIButton( "Controll/215_223.png", NULL, "Controll/215_223G.png" );	
	pointX = 215;
	pointY = 223;
	vec = mButtons[BT_C4]->GetContentSize();
	mButtons[BT_C4]->SetUIPoint( pointX, pointY );
	mButtons[BT_C4]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	
	
	mButtons[BT_C5] = GnNew GnIButton( "Controll/260_223.png", NULL, "Controll/260_223G.png" );
	pointX = 260;
	pointY = 223;
	vec = mButtons[BT_C5]->GetContentSize();
	mButtons[BT_C5]->SetUIPoint( pointX, pointY );
	mButtons[BT_C5]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	mButtons[BT_C5]->SetIsCantPush( true );
	
	mButtons[BT_C6] = GnNew GnIButton( "Controll/305_223.png", NULL, "Controll/305_223G.png" );
	pointX = 305;
	pointY = 223;
	vec = mButtons[BT_C6]->GetContentSize();	
	mButtons[BT_C6]->SetUIPoint( pointX, pointY );	
	mButtons[BT_C6]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	mButtons[BT_C6]->SetIsCantPush( true );
	
    mButtons[BT_C7] = GnNew GnIButton( "Controll/125_268.png", NULL, "Controll/125_268G.png" );
	pointX = 125;
	pointY = 268;
	vec = mButtons[BT_C7]->GetContentSize();
	mButtons[BT_C7]->SetUIPoint( pointX, pointY );
	mButtons[BT_C7]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	mButtons[BT_C7]->SetIsCantPush( true );
	
    mButtons[BT_C8] = GnNew GnIButton( "Controll/170_268.png", NULL, "Controll/170_268G.png" );
	pointX = 170;
	pointY = 268;
	vec = mButtons[BT_C8]->GetContentSize();
	mButtons[BT_C8]->SetUIPoint( pointX, pointY );
	mButtons[BT_C8]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	mButtons[BT_C8]->SetIsCantPush( true );
	
	mButtons[BT_C9] = GnNew GnIButton( "Controll/215_268.png", NULL, "Controll/215_268G.png" );
	pointX = 215;
	pointY = 268;
	vec = mButtons[BT_C9]->GetContentSize();
	mButtons[BT_C9]->SetUIPoint( pointX, pointY );
	mButtons[BT_C9]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	mButtons[BT_C9]->SetIsCantPush( true );
	
	mButtons[BT_C10] = GnNew GnIButton( "Controll/260_268.png", NULL, "Controll/260_268G.png",
									   GnIButton::TYPE_DISABLE );
	pointX = 260;
	pointY = 268;
	vec = mButtons[BT_C10]->GetContentSize();
	mButtons[BT_C10]->SetUIPoint( pointX, pointY );
	mButtons[BT_C10]->SetRect( pointX, pointY, pointX+vec.x, pointY+vec.y );
	mButtons[BT_C10]->SetIsCantPush( true );
	
	GnInterfaceGroup* pGroup = GnNew GnInterfaceGroup();
	pGroup->SetRect( 120.0f, 219.0f, 120.0f+232.0f, 219.0f+100.0f );
	for (gtuint i = 0; i < FORCESBT_NUM ; i++ )
	{
		pGroup->AddChild( mButtons[i] );
	}
	
	AddChild( pGroup, 1 );
	return pGroup;
}
GnInterfaceGroup* GMainGameInterfaceLayer::CreateMainSkillButtons()
{
	GnInterfaceGroup* group = NULL;
	return group;
}