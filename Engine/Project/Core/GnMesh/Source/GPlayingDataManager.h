//
//  GnPlayingDataManager.h
//  Core
//
//  Created by Max Yoon on 11. 8. 4..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GPlayingDataManager_h
#define Core_GPlayingDataManager_h

#include "GPlayingData.h"

class GPlayingDataManager : public GnMemoryObject
{
	GnDeclareSingleton(GPlayingDataManager);
private:
	static const gchar* mscPlayingDataName;
	
private:
	GnTPrimitiveSet<GPlayingData*> mPlayingDatas;
	GPlayingData* mPlayingPlayerData;
	
public:
	void SaveData();
	void LoadData();
	GPlayingData* CreatePlayingData(guint32 uiModeLevel);
	void AddPlayingData(GPlayingData* pData);
	bool SetPlayingPlayerData(gtuint uiIndex);
public:
	inline guint32 GetPlayingDataCount() {
		return (guint32)mPlayingDatas.GetSize();
	}
	inline GPlayingData* GetPlayingData(gtuint uiNum) {
		return mPlayingDatas.GetAt( uiNum );
	}
	inline GPlayingData* GetPlayingPlayerData() {
		return mPlayingPlayerData;
	}
//	inline GPlayingData* GetPlayingData(const gchar* pcName) {
//		GPlayingData* outData = NULL;
//		mPlayingDatas.GetAt( pcName, outData );
//		return outData;
//	}
	inline void AddPlayingData(const gchar* pcName, GPlayingData* pData) {
		pData->SetPlayerName( pcName );
		mPlayingDatas.Add( pData );
	}
};

#endif
