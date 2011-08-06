#include "GnGamePCH.h"
#include "GPlayingData.h"

GPlayingData::GPlayingData() :  mLastClearStage( 0 ), mModeLevel( eNormal )
	, mMoneyCount( 0 ), mStarCount( 0 )
{
	
}

void GPlayingData::LoadStream(GnStream* pStream)
{
	pStream->LoadStream( mModeLevel );
	pStream->LoadStream( mLastClearStage );
	pStream->LoadStream( mMoneyCount );
	pStream->LoadStream( mStarCount );
}

void GPlayingData::SaveStream(GnStream* pStream)
{
	pStream->SaveStream( mModeLevel );
	pStream->SaveStream( mLastClearStage );
	pStream->SaveStream( mMoneyCount );
	pStream->SaveStream( mStarCount );
}