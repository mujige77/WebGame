//
//  GStageInfo.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 20..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GStageInfo.h"

GStageInfo::GCastleFiles::GCastleFiles()
{
	
}
GStageInfo::GCastleFiles::~GCastleFiles()
{
	
}



bool GStageInfo::GetStageInfo(gtuint uiStage, GStageInfo& outStageInfo)
{
	if( uiStage < 20 )
	{
		outStageInfo.Set1_20Stage(uiStage);
	}
	else
		return false;
	
	outStageInfo.mNumStage = uiStage;
	return true;
}

bool GStageInfo::GetForcesCastlePosition(GCastlePositions& cOutPositions)
{
	if( GetNumStage() < 20 )
	{
		Get1_20StagePosition( true, cOutPositions );
	}
	else
		return false;
	
	return true;
}

bool GStageInfo::GetEnemyCastlePosition(GCastlePositions& cOutPositions)
{
	if( GetNumStage() < 20 )
	{
		Get1_20StagePosition( false, cOutPositions );
	}
	else
		return false;
	return true;
}

void GStageInfo::Set1_20Stage(gtuint uiStage)
{
	mInterfaceSize = GnVector2( 480.0f, 105.0f );
	mBackgroundSize = GnVector2( 800.0f, 223.0f );	
	mUseCastleFile = true;
	mLineHeight = 31.0f;
	mLineRects.Add( GnFRect( 50.0f, 142.0f, 750.0f, 105.0f) );
	mLineRects.Add( GnFRect( 50.0f, 179.0f, 750.0f, 136.1f) );
	mBackgroundFileName = "./Data/Background/BG_01.png";
	mInterfaceFileName = "./Data/Controll/0_198.png";
	
	// forces
	mForcesCastleFiles.mCastle = "Background/1/0_4 a.png";
	mForcesCastleFiles.mCastleBreak = "Background/1/0_46 b.png";
	mForcesCastleFiles.mCastleBottom = "Background/1/0_89 ab.png";
	mForcesCastleFiles.mCastleDestroy = "Background/1/0_101 c.png";
	mForcesCastleFiles.mCastleDamageEffect = "Effect/BE1/BE1.gm";
	mForcesCastleFiles.mCastleBreakDamageEffect = "Effect/BE2/BE2.gm";
	mForcesCastleFiles.mCastleBottomDamageEffect = "Effect/BE3/BE3.gm";
	
	// enemy
	mEnemyCastleFiles.mCastle = "Background/1/721_23 a.png";
	mEnemyCastleFiles.mCastleBreak = "Background/1/708_63 b.png";
	mEnemyCastleFiles.mCastleBottom = "Background/1/751_102 ab.png";
	mEnemyCastleFiles.mCastleDestroy = "Background/1/708_95 c.png";
	mEnemyCastleFiles.mCastleDamageEffect = "Effect/BE4/BE4.gm";
	mEnemyCastleFiles.mCastleBreakDamageEffect = "Effect/BE5/BE5.gm";
	mEnemyCastleFiles.mCastleBottomDamageEffect = "Effect/BE6/BE6.gm";
	mEnemyCastleFiles.mDeckEffect = "Effect/BE7/BE7.gm";
}

void GStageInfo::Get1_20StagePosition(bool bForces, GCastlePositions& cOutPositions)
{
	if( bForces )
	{
		// forces
		cOutPositions.mCastle = GnVector2( 0.0f, 4.0f );
		cOutPositions.mCastleBreak = GnVector2( 0.0f, 46.0f );
		cOutPositions.mCastleBottom = GnVector2( 0.0f, 89.0f );
		cOutPositions.mCastleDestroy = GnVector2( 0.0f, 101.0f );
		cOutPositions.mCastleDamageEffect = GnVector2( 0.0, 0.0f );
		cOutPositions.mCastleBreakDamageEffect = GnVector2( 0.0, 16.0f );
		cOutPositions.mCastleBottomDamageEffect = GnVector2( 0.0, 72.0f );		
	
	}	
	else
	{
		// enemy
		cOutPositions.mCastle = GnVector2( 721.0f, 23.0f );
		cOutPositions.mCastleBreak = GnVector2( 708.0f, 63.0f );
		cOutPositions.mCastleBottom = GnVector2( 751.0f, 102.0f );
		cOutPositions.mCastleDestroy = GnVector2( 708.0, 95.0f );
		cOutPositions.mCastleDamageEffect = GnVector2( 712.0, 2.0f );
		cOutPositions.mCastleBreakDamageEffect = GnVector2( 703.0, 43.0f );
		cOutPositions.mCastleBottomDamageEffect = GnVector2( 734.0, 101.0f );
		cOutPositions.mDeckEffect = GnVector2( 776.0f, 68.0f );
	}
}