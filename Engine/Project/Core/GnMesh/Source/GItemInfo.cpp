//
//  GItemInfo.cpp
//  Core
//
//  Created by Max Yoon on 11. 8. 12..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GItemInfo.h"

GnImplementSingleton(GItemInfo)


const gchar* GItemInfo::GetIconFileName(gtuint uiIndex)
{
	if( mscNumMaxItem <= uiIndex  )
		return NULL;
	
	static const char fileName[mscNumMaxItem][256] = 	
	{
		{"Upgrade/items/400_74 a.png"}, {"Upgrade/items/400_124.png"},
		{"Upgrade/items/400_174.png"}, {"Upgrade/items/400_74 .png"},
		{"Upgrade/items/400_174 a.png"}, {"Upgrade/items/30_140 s.png"}
	};
	
	return fileName[uiIndex];
}

const gchar* GItemInfo::GetPriceIconFileName(gtuint uiIndex)
{
	if( mscNumMaxItem <= uiIndex  )
		return NULL;
	
	static const char fileName[mscNumMaxItem][256] = 	
	{
		{"Upgrade/items/30_140.png"}, {"Upgrade/items/82_74.png"},
		{"Upgrade/items/134_74.png"}, {"Upgrade/items/30_74.png"},
		{"Upgrade/items/82_140.png"}, {"Upgrade/items/400_124 a.png"}
	};
	return fileName[uiIndex];
}

const gchar* GItemInfo::GetExplainFileName(gtuint uiIndex)
{
	if( mscNumMaxItem <= uiIndex  )
		return NULL;
	
	static const char fileName[mscNumMaxItem][256] = 	
	{
		{"Upgrade/items/a 28_222.png"}, {"Upgrade/items/c 28_222.png"},
		{"Upgrade/items/b 28_222.png"}, {"Upgrade/items/d 28_222.png"},
		{"Upgrade/items/e 28_222.png"}, {"Upgrade/items/item1.png"}
	};
	return fileName[uiIndex];	
}

guint32 GItemInfo::GetBuyPrice(gtuint uiIndex)
{
	if( mscNumMaxItem <= uiIndex  )
		return 0;
	
	const guint32 price[mscNumMaxItem] = 	
	{
		100, 200, 300, 400, 500, 0
	};
	return price[uiIndex];	
}

guint32 GItemInfo::GetSellPrice(gtuint uiIndex)
{
	if( mscNumMaxItem <= uiIndex  )
		return 0;

	const guint32 price[mscNumMaxItem] = 	
	{
		30, 60, 90, 120, 150, 0
	};
	return price[uiIndex];
}