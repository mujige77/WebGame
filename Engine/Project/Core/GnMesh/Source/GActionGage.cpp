//
//  GActionGage.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 17..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GActionGage.h"
#include "GnIProgressBar.h"
#include "GInfoBasic.h"
#include "GCurrentActorInfo.h"

GActionGage::GActionGage(GActorController* pController) : GAction( pController ), mpGageBar( NULL )
	, mViewGageTime( 5.0f )
{
	
}

GActionGage::~GActionGage()
{
	if( mpGageBar )
		GnDelete mpGageBar;
}

void GActionGage::Update(float fTime)
{
	mAcumTime += fTime;
	if( IsStopAction() )
		return;
	
	SetGagePosition();
	if( mpGageBar )
		mpGageBar->SetProgressPercent( mGagePercent );
}

void GActionGage::AttachActionToController()
{
	if( mpGageBar == NULL )
		mpGageBar = CreateGageBar();
	
	if( mpGageBar )
	   GetActorLayer()->addChild( mpGageBar->GetParentUseNode(), 6000 );
	
	mAcumTime = 0.0f;
}

void GActionGage::DetachActionToController()
{
	if( mpGageBar && mpGageBar->GetParentUseNode()->getParent() )
		GetActorLayer()->removeChild( mpGageBar->GetParentUseNode(), true );
}

GnIProgressBar* GActionGage::CreateGageBar()
{
	GnIProgressBar* gageBar = GnIProgressBar::Create( GnIProgressBar::eHorizontalFromRight
		, "Controll/GageBackground.png", "Controll/Gage.png" );
	if( gageBar )
	{
		gageBar->SetVisibleProgress( true );
		gageBar->SetVisibleBackground( true );
	}
	
	return gageBar;
}

void GActionGage::SetGagePosition()
{
	GnVector2ExtraData* posExtraData = (GnVector2ExtraData*)
		GetController()->GetMesh()->GetExtraDataFromType( GExtraData::EXTRA_GAGE_POSITION );
	
	if( posExtraData == NULL )
		return;
	
	GnVector2 vector = posExtraData->GetValueVector2();
	GnVector2 gagePos;
//	if( GetController()->GetMesh()->GetFlipX() )
//	{
//		gagePos = posExtraData->GetValueVector2() - GetController()->GetMesh()->GetFlipCenter();
//		gagePos += GetController()->GetMesh()->GetPosition();
//	}
//	else
//	{
		gagePos = GetController()->GetMesh()->GetPosition() + posExtraData->GetValueVector2();
//	}
	if( mpGageBar )
		mpGageBar->SetPosition( gagePos );
}

void GActionGage::SetGagePercent(gint32 iPercent)
{
	mGagePercent = iPercent;
}
