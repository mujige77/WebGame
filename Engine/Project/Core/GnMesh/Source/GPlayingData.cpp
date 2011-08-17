#include "GnGamePCH.h"
#include "GPlayingData.h"

GPlayingData::GPlayingData() : mMoneyCount( 0 ), mStarCount( 0 ), mModeInfos( eMaxMode )
{
	for ( gtuint i = 0 ; i < mModeInfos.GetAllocatedSize() ; i++ )
	{
		ModeInfo mode;
		mode.mEnableMode = true;
		mode.mModeLevel = (eModeLevel)i;
		mode.mLastClearStage = 0;		
		mModeInfos.SetAt( i, mode );
	}
}

void GPlayingData::LoadStream(GnStream* pStream)
{
	for ( gtuint i = 0 ; i < eMaxMode; i++ )
	{
		ModeInfo& info = mModeInfos.GetAt( i );
		pStream->LoadStream( info.mEnableMode );
		pStream->LoadStream( info.mModeLevel );	
		pStream->LoadStream( info.mLastClearStage );
	}
	pStream->LoadStream( mMoneyCount );
	pStream->LoadStream( mStarCount );
}

void GPlayingData::SaveStream(GnStream* pStream)
{
	for ( gtuint i = 0 ; i < eMaxMode; i++ )
	{
		ModeInfo& info = mModeInfos.GetAt( i );
		pStream->SaveStream( info.mEnableMode );
		pStream->SaveStream( info.mModeLevel );	
		pStream->SaveStream( info.mLastClearStage );
	}
	pStream->SaveStream( mMoneyCount );
	pStream->SaveStream( mStarCount );
}