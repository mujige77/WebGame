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
	
	GFarAttack::RegCreateFunction( eIndexItemSwitchUnit, GShootAttack::CreateAttack );
	bRegistered = true;
}

GFarAttack* GShootAttack::CreateAttack(guint32 uiIndex)
{
	GShootAttack* attck = GnNew GShootAttack();
	switch ( uiIndex )
	{
		case eIndexItemSwitchUnit:
			attck->InitShooting( 4.0f, 0.0f );
			break;
		default:
			attck->InitShooting( 4.0f, 0.0f );
			break;
	}
	return attck;
}

void GShootAttack::InitShooting(float fDirectionX, float fDirectionY)
{
	mShootTimer.SetPercentTime( 0.01f );
	mShootDirection.x = fDirectionX;
	mShootDirection.y = fDirectionY;
}

void GShootAttack::Update(float fTime)
{
	if( GetCurrentAttackCount() >= GetAttackCount() )
		SetIsDestory( true );
	else
	{
		GFarAttack::Update( fTime );
		if( mShootTimer.Update( fTime ) )
		{
			GnVector2 pos = GetAttackMesh()->GetPosition();
			float bgSize =  GetGameEnvironment()->GetStageInfo()->GetBackgroundSize().x;
			if( pos.x < 0.0f || pos.x > bgSize )
			{
				SetIsDestory( true );
			}
			else
			{
				pos += ( mShootDirection * mShootTimer.GetAmplify() );
				SetPosition( pos );
			}
			mShootTimer.Reset();
		}
	}
}

void GShootAttack::SetPosition(GnVector2 cPos)
{
	GFarAttack::SetPosition( cPos );
}

void GShootAttack::SetFilpX(bool val)
{
	GFarAttack::SetFilpX( val );
	float dir = val ? -1.0f : 1.0f;
	InitShooting( mShootDirection.x * dir, mShootDirection.y );
}