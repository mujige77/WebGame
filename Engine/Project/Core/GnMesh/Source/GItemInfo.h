//
//  GItemInfo.h
//  Core
//
//  Created by Max Yoon on 11. 8. 12..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GItemInfo_h
#define Core_GItemInfo_h

class GItemInfo : public GnMemoryObject
{
	GnDeclareSingleton(GItemInfo);
public:
	static const gtuint mscNumMaxItem = 6;
	
public:
	const gchar* GetIconFileName(gtuint uiIndex);
	const gchar* GetGameIconFileName(gtuint uiIndex);
	const gchar* GetPriceIconFileName(gtuint uiIndex);
	const gchar* GetExplainFileName(gtuint uiIndex);
	guint32 GetBuyPrice(gtuint uiIndex, guint32 uiLevel);
	guint32 GetSellPrice(gtuint uiIndex, guint32 uiLevel);
};	

#define GetItemInfo GItemInfo::GetSingleton

#endif
