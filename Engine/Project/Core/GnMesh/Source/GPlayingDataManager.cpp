//
//  GnPlayingDataManager.cpp
//  Core
//
//  Created by Max Yoon on 11. 8. 4..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GPlayingDataManager.h"

GnImplementSingleton(GPlayingDataManager);

const gchar* GPlayingDataManager::mscPlayingDataName = "PlayingData.dat";

GUserHaveItem* GetCurrentHaveItem()
{
	GPlayingDataManager* dataMng = GPlayingDataManager::GetSingleton();
	GPlayingData* playingData = dataMng->GetPlayingPlayerData();
	GUserHaveItem* haveItem = dataMng->GetPlayingHaveItem();
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );
	return haveItem;
}

void GPlayingDataManager::SaveData()
{
	if( GetPlayingDataCount() <= 0 )
		return;
	
	GnStream dataStream;
	dataStream.SetFileVersion( PLAYINGDATA_MAJOR_VERSION, PLAYINGDATA_MINOR_VERSION
		, PLAYINGDATA_PATCH_VERSION, PLAYINGDATA_INTERNAL_VERSION );
	
	gstring fullPath;
	GetWriteablePath( mscPlayingDataName, fullPath );
	if( dataStream.Save( fullPath.c_str() ) == false )
		return;		
	
	gchar dataHeader[256] =	{ "ldicleiod;scpclfds;c'df'sfl'o4=12-8 ntjpos" };
	dataStream.SaveStreams( dataHeader, sizeof( dataHeader ) );	
	
	guint32 count = GetPlayingDataCount();
	dataStream.SaveStream( count );
	
	for( gtuint i = 0 ; i < count ; i++ )
	{
		GPlayingData* data = mPlayingDatas.GetAt( i );
		
		dataStream.SaveStream( data->GetPlayerName() );
		data->SaveStream( &dataStream );
	}

}

void GPlayingDataManager::LoadData()
{
	GnStream dataStream;
	gstring fullPath;
	GetWriteablePath( mscPlayingDataName, fullPath );
	if( dataStream.Load( fullPath.c_str() ) == false )
		return;
	
	gchar dataHeader[256] = { 0, };	
	dataStream.LoadStreams( dataHeader, sizeof( dataHeader ) );
	
	guint32 count = GetPlayingDataCount();
	dataStream.LoadStream( count );
	
	for ( gtuint i = 0; i < count ; i++ )
	{
		gchar* playingName = NULL;
		dataStream.LoadStream( playingName );
		
		GPlayingData* data = GnNew GPlayingData();
		data->LoadStream( &dataStream );
		
		AddPlayingData( playingName, data );
		
		GnFree( playingName );
	}
}

GPlayingData* GPlayingDataManager::CreatePlayingData()
{
	GPlayingData* data = GnNew GPlayingData();
	data->SetStarCount( 50 );
	data->SetMoneyCount( 5000 );	
	return data;
}

void GPlayingDataManager::DeletePlayingData(gtuint uiIndex)
{
	GPlayingData* data = GetPlayingData( uiIndex );
	if( data == NULL )
		return;
	
	mPlayingDatas.RemoveAndFill( data );
	mPlayingItemData.SetPlayerName( mPlayingPlayerData->GetPlayerName() );	
}

void GPlayingDataManager::AddPlayingData(GPlayingData* pData)
{
	gchar name[10] = { 0, };
	GnSprintf( name, sizeof( name ), "playing%d", GetPlayingDataCount() );
	AddPlayingData( name, pData );
	mPlayingItemData.CreateHaveItem( name );
}

bool GPlayingDataManager::SetPlayingPlayerData(gtuint uiIndex)
{
	mPlayingPlayerData = GetPlayingData( uiIndex );
	if( mPlayingPlayerData == NULL )
		return false;
	
	mPlayingItemData.SetPlayerName( mPlayingPlayerData->GetPlayerName() );
	return true;
}