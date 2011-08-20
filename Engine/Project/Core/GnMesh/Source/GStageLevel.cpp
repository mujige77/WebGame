#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GStageLevel.h"

GStageLevel* GStageLevel::CreateStageLevel(const gcahr* pcFilePath)
{
	GnStream stream;
	if( stream.Load( filePath ) )
	{
		gint32 tempCount = 0;
		stream.LoadStream( tempCount );
		for( gint32 i = 0 ; i < tempCount ; i++ )
		{
			gchar viewName[256] = { 0, };
			gushort nameLen = 0;
			stream.LoadStream( nameLen );
			stream.LoadStreams( viewName, nameLen );
		}
		
		GStageLevel* thisVal = GnNew GStageLevel();
		thisVal->LoadStream( filePath );
	}
	return NULL;
}
void GStageLevel::LoadStream(GnStream* pStream)
{
	pStream->LoadStream( mLevelIndex );
	pStream->LoadStream( mBossMobIndex );
	guint32 count = 0;
	pStream->LoadStream( count );
	for( gtuint i = 0 ; i < count ; i++ )
	{
		GStageLevel::AppearMob mob;
		pStream->LoadStream( mob.mIndex );
		pStream->LoadStream( mob.mLevel );
		pStream->LoadStream( mob.mIntervalAppearTime );
		AddAppearMob( mob );
	}
	
	pStream->LoadStream( count );
	for( gtuint i = 0 ; i < count ; i++ )
	{
		GStageLevel::AttackLine attline;
		pStream->LoadStream( attline.mNumLine );
		pStream->LoadStream( attline.mStartAppearTime );
		pStream->LoadStream( attline.mIntervalAppearTime );
		AddAttackLine( attline );
	}
}

void GStageLevel::SaveStream(GnStream* pStream)
{
	pStream->SaveStream( mLevelIndex );
	pStream->SaveStream( mBossMobIndex );

	guint32 count = GetAppearMobCount();
	pStream->SaveStream( count );
	for( gtuint i = 0 ; i < count ; i++ )
	{
		GStageLevel::AppearMob& mob = GetAppearMob( i );
		pStream->SaveStream( mob.mIndex );
		pStream->SaveStream( mob.mLevel );
		pStream->SaveStream( mob.mIntervalAppearTime );
	}

	count = GetAttackLineCount();
	pStream->SaveStream( count );
	for( gtuint i = 0 ; i < count ; i++ )
	{
		GStageLevel::AttackLine& attline = GetAttackLine( i );
		pStream->SaveStream( attline.mNumLine );
		pStream->SaveStream( attline.mStartAppearTime );
		pStream->SaveStream( attline.mIntervalAppearTime );
	}
}