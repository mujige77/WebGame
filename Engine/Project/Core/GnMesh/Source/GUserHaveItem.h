//
//  GUserHaveItem.h
//  Core
//
//  Created by Max Yoon on 11. 8. 7..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GUserHaveItem_h
#define Core_GUserHaveItem_h

#include "GGameDefine.h"

class GUserHaveItem : protected GnSQLite
{
public:
	class Item
	{
	public:
		guint32 mIndex;
		eItemType mType;
		guint32 mLevel;
		guint32 mCount;
	};
protected:
	enum eFieldIndex
	{
		eIndex,
		eType,		
		eLevel,
		eCount,
	};
	
private:
	GnSimpleString mCurrentTableName;
	GnSQLiteTable mOpenItemTable;
	
public:
	bool CreateHaveItem(const gchar* pcName);
	bool DropHaveItem(const gchar* pcName);
	bool OpenPlayerItem(const gchar* pcName);
	void Close();
	void AddItem(guint32 uiIndex, eItemType uiType = eItem, guint32 uiLevel = 0, guint32 uiCount = 1);
	void DeleteItem(guint32 uiIndex, eItemType type);
	guint32 GetItemLevel(guint32 uiIndex);
	guint32 GetItemCount(guint32 uiIndex);
	bool GetItem(guint32 uiIndex, GUserHaveItem::Item& outItem);
	bool GetItems(eItemType uiType, GnList<GUserHaveItem::Item>& outItem);
	void UpdateLevel(guint32 uiIndex, guint32 uiLevel);
	void UpdateCount(guint32 uiIndex, guint32 uiCount);

public:
	void SetPlayerName(const gchar* pcName) {
		mCurrentTableName = pcName;
	};
	inline bool OpenPlayerItem() {
		return OpenPlayerItem( mCurrentTableName );
	}
	inline gint32 GetItemCount() {
		return mOpenItemTable.NumRows();
	}
	
private:
	void CreateBasicUnit();
	void CreateBasicAbility();
};

#endif
