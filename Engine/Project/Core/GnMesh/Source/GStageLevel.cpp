#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GStageLevel.h"

GStageLevel* GStageLevel::CreateStageLevel(guint32 uiStageLevel)
{
	gchar fileName[256] = { 0, };
	GnSprintf( fileName, sizeof( fileName ), "StageLevel/StageLevel%d.gd", uiStageLevel + 1);
	gstring fullPathName;
	GetFullPathFromWorkPath( fileName, fullPathName );
	GStageLevel* retStage = CreateStageLevel( fullPathName.c_str() );
	if( retStage == NULL )
	{
		GetFullPathFromWorkPath( "StageLevel/StageLevel5.gd", fullPathName );
		retStage = CreateStageLevel( fullPathName.c_str() );	
	}
	return retStage;
}

GStageLevel* GStageLevel::CreateStageLevel(const gchar* pcFilePath)
{
	GnStream stream;
	if( stream.Load( pcFilePath ) )
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
		thisVal->LoadStream( &stream );
		return thisVal;
	}
	return NULL;
}

void GStageLevel::LoadStream(GnStream* pStream)
{
	pStream->LoadStream( mLevelIndex );
	pStream->LoadStream( mBossMobIndex );
	pStream->LoadStream( mCastleHP );
	
	guint32 count = 0;
	pStream->LoadStream( count );
	for( gtuint i = 0 ; i < count ; i++ )
	{
		GStageLevel::AppearMob mob;
		pStream->LoadStream( mob.mIndex );
		pStream->LoadStream( mob.mLevel );
		pStream->LoadStream( mob.mIntervalAppearPercent );
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

	if( pStream->GetFileVersion() > GnStream::GetVersion( 1, 0, 0, 2 ) )
	{
		pStream->LoadStream( count );
		for( gtuint i = 0 ; i < count ; i++ )
		{
			GStageLevel::MassAppearMob mob;
			pStream->LoadStream( mob.mIndex );
			pStream->LoadStream( mob.mLevel );
			pStream->LoadStream( mob.mNumLine );
			pStream->LoadStream( mob.mNumMobCount);
			AddMassAppearMob( mob );
		}
	}
}

void GStageLevel::SaveStream(GnStream* pStream)
{
	pStream->SaveStream( mLevelIndex );
	pStream->SaveStream( mBossMobIndex );
	pStream->SaveStream( mCastleHP );

	guint32 count = GetAppearMobCount();
	pStream->SaveStream( count );
	for( gtuint i = 0 ; i < count ; i++ )
	{
		GStageLevel::AppearMob& mob = GetAppearMob( i );
		pStream->SaveStream( mob.mIndex );
		pStream->SaveStream( mob.mLevel );
		pStream->SaveStream( mob.mIntervalAppearPercent );
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

	count = GetMassAppearMobCount();
	pStream->SaveStream( count );
	for( gtuint i = 0 ; i < count ; i++ )
	{
		GStageLevel::MassAppearMob& mob = GetMassAppearMob( i );
		pStream->SaveStream( mob.mIndex );
		pStream->SaveStream( mob.mLevel );
		pStream->SaveStream( mob.mNumLine );
		pStream->SaveStream( mob.mNumMobCount );
	}
}