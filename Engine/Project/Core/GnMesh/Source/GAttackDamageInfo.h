//
//  GAttackDamageInfo.h
//  Core
//
//  Created by Max Yoon on 11. 8. 26..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GAttackDamageInfo_h
#define Core_GAttackDamageInfo_h

class GAttackDamageInfo
{
public:
	guint32 mDamage;
	guint32 mDamageFileIndex;
	
public:
	inline GAttackDamageInfo(guint32 uiDamage = 100, guint32 uiDamageIndex = 1) : mDamage( uiDamage )
		, mDamageFileIndex( uiDamageIndex)
	{}
	inline guint32 GetDamage() {
		return mDamage;
	}
	inline void SetDamage(guint32 uiDamage) {
		mDamage = uiDamage;
	}
	inline guint32 GetDamageFileIndex() {
		return mDamageFileIndex;
	}
	inline void SetDamageFileIndex(guint32 uiDamageFileIndex) {
		mDamageFileIndex = uiDamageFileIndex;
	}
};

#endif
