//
//  GPlayingDataDefine.h
//  Core
//
//  Created by Max Yoon on 11. 8. 9..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GPlayingDataDefine_h
#define Core_GPlayingDataDefine_h

#define PLAYINGDATA_MAJOR_VERSION 0
#define PLAYINGDATA_MINOR_VERSION 9
#define PLAYINGDATA_PATCH_VERSION 0
#define PLAYINGDATA_INTERNAL_VERSION 0

#define USER_HAVEDATA_FILENAME "UserHaveItem.sqlite"

static const guint32 gscPlayingDataVersion = GnStream::GetVersion(PLAYINGDATA_MAJOR_VERSION
	, PLAYINGDATA_MINOR_VERSION, PLAYINGDATA_PATCH_VERSION, PLAYINGDATA_INTERNAL_VERSION);

enum eModeLevel
{
	eEasy,
	eNormal,
	eHard,
	eMaxMode,
};

enum eItemType
{
	eUnit,
	eAbility,
	eItem,
	eEquip,
};

enum eItemIndex
{
	eIndexC1 = 1,
	eIndexC2,
	eIndexC3,
	eIndexC4,
	eIndexC5,
	eIndexC6,
	eIndexC7,
	eIndexC8,
	eIndexC9,
	eIndexC10,
	eMaxIndexUnit,
	eIndexSkillUp = 100,
	eIndexItemDrop,
	eIndexMoney,
	eIndexSpeed,
	eIndexUnitSpeed,
	eIndexHeroAutoHP,
	eIndexHeroMaxHP,
	eIndexHeroAutoMP,
	eIndexHeroMaxMP,
	eIndexAutoFD,
	eIndexMaxFD,
	eIndexCastleAutoHP,
	eIndexCastleMaxHP,
	eMaxIndexAbility,
	eIndexItemBomb = 1000,
	eIndexItemBolt,
	eIndexItemFire,
	eIndexItemSwitchUnit,
	eIndexItemHPUp,
	eIndexItemMissile,
	eMaxIndexItem,
};

#define INDEX_UNIT 1
#define INDEX_ABILITY 100
#define INDEX_ITEM 1000
#define ENABLE_MAX_EQUIP 3
#define MAX_ABILITY_LEVEL 20
#endif
