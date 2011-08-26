//
//  GFarAttack.cpp
//  Core
//
//  Created by Max Yoon on 11. 8. 24..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GFarAttack.h"
#include "GFileLIst.h"

GFarAttack::GFarAttack() : mAttackCount( 1 )
{
#ifdef GNDEBUG
	GnFarAttackDrawPrimitiveslayer* pLayer = new GnFarAttackDrawPrimitiveslayer();
	pLayer->GetDrawObject()->SetFarAttack( this );
	pLayer->autorelease();	
	mpDebugLayer = pLayer;
	//mpDebugLayer = NULL;
#endif // GNDEBUG
	
	Reset();
}

std::map<gtuint, GFarAttack::CreateAttackFunc> GFarAttack::mCreateFuncs;

void GFarAttack::RegCreateFunction(gtuint uiIndex, GFarAttack::CreateAttackFunc pFunc)
{
	mCreateFuncs.insert( std::make_pair( uiIndex, pFunc ) );
}

GFarAttack* GFarAttack::CreateAttack(gtuint uiIndex)
{
	std::map<gtuint, GFarAttack::CreateAttackFunc>::iterator iter = mCreateFuncs.find( uiIndex );
	if( iter == mCreateFuncs.end() )
		return NULL;
	
	GFarAttack* attack = iter->second( uiIndex );
	attack->SetAttackIndex( uiIndex );
	return attack;
}

GFarAttack* GFarAttack::CreateAttackFromEffectIndex(gtuint uiIndex, gtuint uiEffectFileIndex)
{
	std::map<gtuint, GFarAttack::CreateAttackFunc>::iterator iter = mCreateFuncs.find( uiIndex );
	if( iter == mCreateFuncs.end() )
		return NULL;
	
	GFarAttack* attack = iter->second( uiIndex );
	attack->SetAttackIndex( uiIndex );
	attack->CreateAttackMesh( uiEffectFileIndex );
	return attack;
}

bool GFarAttack::CreateAttackMesh(gtuint uiIndex)
{
	gstring fullName;
	if( GetFileList()->GetFullEffectName( uiIndex, fullName ) == false )
		return false;

	mpsAttackMesh = Gn2DMeshObject::CreateFullPath( fullName.c_str(), true );
	mOriginalAttackRect.left = 0.0f;
	mOriginalAttackRect.top = 0.0f;
	mOriginalAttackRect.right = mpsAttackMesh->GetSize().x;
	mOriginalAttackRect.bottom = mpsAttackMesh->GetSize().y;
	SetPosition( GnVector2(0.0f, 0.0f) );
	return true;	
}

void GFarAttack::Reset()
{
	mStopAnimation = false;
	mCurrentAttackCount = 0;
	mStartAttackTime = 0.0f;
	mAccumulateTime = 0.0f;
	SetIsDestory( false );
	SetIsEnableAttack( true );
}

void GFarAttack::Update(float fTime)
{
	mAccumulateTime += fTime;
	if( mpsAttackMesh )
	{
		mpsAttackMesh->Update( fTime );
		bool bAllStop = true;
		GnTimeController* ctrl = mpsAttackMesh->GetTimeControllers();
		GnAssert( ctrl );
		while ( ctrl )
		{
			if( ctrl->GetPlayFlags() != GnTimeController::STOP )
			{
				bAllStop = false;
				break;
			}
			ctrl = ctrl->GetNext();
		}
		mStopAnimation = bAllStop;
	}
}

void GFarAttack::SetPosition(GnVector2 cPos)
{
	if( mpsAttackMesh )
		mpsAttackMesh->SetPosition( cPos );
	mAttackRect = mOriginalAttackRect;
	mAttackRect.MoveX( cPos.x );
	mAttackRect.MoveY( cPos.y );
}