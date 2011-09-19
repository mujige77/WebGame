#include "GnGamePCH.h"
#include "GStageLevelManager.h"


GStageLevelManager* GStageLevelManager::CreateManager(guint uiNumStage)
{
	GStageLevel* pStageLevel = GStageLevel::CreateStageLevel( uiNumStage );
	GStageLevelManager* pStageLevelMng = GnNew GStageLevelManager( pStageLevel );	
	
	return pStageLevelMng;
}

GStageLevelManager::GStageLevelManager(GStageLevel* pStageLevel) : mpStageLevel( pStageLevel )
{
	Init( pStageLevel );
}

GStageLevelManager::~GStageLevelManager()
{
	if ( mpStageLevel )
		GnDelete mpStageLevel;
}

void GStageLevelManager::Update(float fTime)
{
	mAcumTime += fTime;
	mAcumStartAppearTime += fTime;
	if( GetAttackLineCount() != mpStageLevel->GetAttackLineCount() )
		CheckAddAcumAttackLine();

	for( gtuint i = 0 ; i < GetAttackLineCount(); i++)
	{
		AcumAttackLine& line = GetAttackLine( i );
		line.acumTime += fTime;
		if( line.acumTime > line.intervalAppearTime )
		{
			line.acumTime = 0.0f;
			AddReadyAppearMob( line.numLine, GetAppearFromList() );
		}
	}
}

void GStageLevelManager::Init(GStageLevel* pStageLevel)
{
	mAcumTime = 0.0f;
	mAcumStartAppearTime = 0.0f;
	
	CollectAppearMobList( pStageLevel );
}

void GStageLevelManager::CollectAppearMobList(GStageLevel* pStageLevel)
{
	gtuint mobNumber = 0;
	GStageLevel::AppearMob minPercentMob;
	for(gtuint i = 0 ; i < pStageLevel->GetAppearMobCount() ; i++)
	{
		GStageLevel::AppearMob& mob = pStageLevel->GetAppearMob( i );
		float per = (float)mob.mIntervalAppearPercent / 100.0f;
		guint32 mopCount = MAX_APPEARMOB * per;
		for ( gtuint j = 0 ; j < mopCount; j++, mobNumber++ )
		{
			if( mobNumber >= MAX_APPEARMOB )
			{
				GnLogA( "Warring Over MAX_APPEARMOB" );
				return;
			}
			mAppearMobs[mobNumber] = AppearMobCtrl( mob.mIndex, mob.mLevel );
		}
		if( i == 0 )
			minPercentMob = mob;
		else if( minPercentMob.mIntervalAppearPercent > mob.mIntervalAppearPercent )
			minPercentMob = mob;
	}
	
	if( pStageLevel->GetAppearMobCount() )
	{
		for( gtuint i = mobNumber ; i < MAX_APPEARMOB ; i++ )
		{
			mAppearMobs[i] = AppearMobCtrl( minPercentMob.mIndex, minPercentMob.mLevel );
		}
	}
	GnShuffleArray( mAppearMobs, MAX_APPEARMOB );
}

void GStageLevelManager::CheckAddAcumAttackLine()
{
	for( gtuint i = 0 ; i < mpStageLevel->GetAttackLineCount() ; i++ )
	{
		GStageLevel::AttackLine& attackLine = mpStageLevel->GetAttackLine( i );
		if( mAcumStartAppearTime > attackLine.mStartAppearTime )
		{
			bool addLine = true;
			for( gtuint i = 0 ; i < GetAttackLineCount() ; i++ )
			{
				if( attackLine.mNumLine == GetAttackLine( i ).numLine )
				{
					addLine = false;
					break;
				}
			}
			if( addLine )
			{
				AddReadyAppearMob( attackLine.mNumLine, GetAppearFromList() );
				AddAttackLine( AcumAttackLine( attackLine.mNumLine, attackLine.mIntervalAppearTime ) );
			}
		}
	}
}

GStageLevelManager::AppearMobCtrl& GStageLevelManager::GetAppearFromList()
{
	static gtuint mobNumber = 0;
	if( mobNumber >= MAX_APPEARMOB )
		mobNumber = 0;
	
	return mAppearMobs[mobNumber++];
}