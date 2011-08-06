//
//  GEnergyBar.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 14..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GEnergyBar.h"

GEnergyBar* GEnergyBar::Create(gint32 uiMax, float fFillTime, const gchar* pBackgroundImagePath)
{
	GEnergyBar* bar = GnNew GEnergyBar( pBackgroundImagePath );
	bar->Init( uiMax, fFillTime );
	return bar;
}

GEnergyBar::GEnergyBar(const gchar* pBackgroundImagePath) : GnIButton( pBackgroundImagePath )
{
	SetIsDisableCantpushBlind( true );
	SetIsCantPush( true );
}

void GEnergyBar::Init(gint32 iMax, float fFillTime)
{
	mFillTime = fFillTime;
	mAcumTime = 0.0f;
	
	gstring fullPath;
	GetFullPathFromWorkPath( "Controll/integer.png", fullPath );

	mLabelCurrentEnergy.Init( "000", fullPath.c_str(), 12, 14, '.' );
	mLabelCurrentEnergy.SetMaxDigit( 3, "%03d" );
	SetCurrentEnergy( 0 );
	mLabelMaxEnergy.Init( "000", fullPath.c_str(), 12, 14, '.' );
	mLabelMaxEnergy.SetMaxDigit( 3, "%03d" );
	SetMaxEnergy( iMax );
	
	GetParentUseNode()->addChild( mLabelCurrentEnergy.GetParentUseNode(), INTERFACE_ZORDER + 1 );
	GetParentUseNode()->addChild( mLabelMaxEnergy.GetParentUseNode(), INTERFACE_ZORDER + 1 );
}

void GEnergyBar::Update(float fDeltaTime)
{
	if( GetCurrentEnergy() >= GetMaxEnergy() )
		return;
		
	mAcumTime += fDeltaTime;
	if( mAcumTime / mFillTime > 1.0f )
	{
		mAcumTime = 0.0f;
		SetCurrentEnergy( GetCurrentEnergy() + 1 );
	}
}

void GEnergyBar::SetPosition(GnVector2& cPos)
{
	GnIButton::SetPosition( cPos );

	cPos.x -= GetContentSize().x / 2.0f;
	cPos.x += 22.0f;
	cPos.y += 12.0f;
	mLabelCurrentEnergy.SetPosition( cPos );
	cPos.y -= 20;
	mLabelMaxEnergy.SetPosition( cPos );
}