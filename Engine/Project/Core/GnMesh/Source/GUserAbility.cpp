//
//  GUserAbility.cpp
//  Core
//
//  Created by Max Yoon on 11. 9. 15..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GUserAbility.h"
#include "GPlayingDataManager.h"

guint32 GUserAbility::GetAbilityLevel(guint32 uiAbilityIndex)
{
	GPlayingDataManager* dataMng = GPlayingDataManager::GetSingleton();
	GPlayingData* playingData = dataMng->GetPlayingPlayerData();	
	GUserHaveItem* haveItem = dataMng->GetPlayingHaveItem();
	haveItem->OpenPlayerItem( playingData->GetPlayerName() );	
	guint32 level = haveItem->GetItemLevel( uiAbilityIndex );
	haveItem->Close();
	return level;
}
