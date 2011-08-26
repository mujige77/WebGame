//
//  GShootAttack.cpp
//  Core
//
//  Created by Max Yoon on 11. 8. 8..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GShootAttack.h"

void GShootAttack::RegisterCreateFunction()
{
	static bool bRegistered = false;
	if(bRegistered)
		return;
	
	GFarAttack::RegCreateFunction( eIndexItemMissile, GShootAttack::CreateAttack );
	GFarAttack::RegCreateFunction( eIndexItemSwitchUnit, GShootAttack::CreateAttack );
	bRegistered = true;
}

GFarAttack* GShootAttack::CreateAttack(guint32 uiIndex)
{
	GShootAttack* attck = GnNew GShootAttack();
	switch ( uiIndex )
	{
		case eIndexItemMissile:
			attck->InitShooting( 5.0f, 0.0f );
			break;
		case eIndexItemSwitchUnit:
			attck->InitShooting( 5.0f, 0.0f );
			break;
		default:
			attck->InitShooting( 5.0f, 0.0f );
			break;
	}
	return attck;
}

void GShootAttack::Update(float fTime)
{
	if( mShootTimer.Update( fTime ) )
	{
		GnVector2 pos = GetAttackMesh()->GetPosition();
		pos += ( mShootDirection * mShootTimer.GetAmplify() );
		SetPosition( pos );
	}
}

void GShootAttack::SetPosition(GnVector2 cPos)
{
	GFarAttack::SetPosition( cPos );
//	GnFRect originalRect = GetOriginalAttackRect();
//	originalRect.MoveX( cPos.x );
//	originalRect.MoveY( cPos.y );
//	SetAttackRect( originalRect );
//	
//	GetAttackMesh()->SetPosition( cPos );
}

void GShootAttack::InitShooting(float fDirectionX, float fDirectionY)
{
	mShootTimer.SetPercentTime( 0.01f );
	mShootDirection.x = fDirectionX;
	mShootDirection.y = fDirectionY;
}