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
	guint32 mAttackType;
	float mDontMoveTime;
	
public:
	inline GAttackDamageInfo(guint32 uiDamage = 0, guint32 uiAttackType = 0, guint32 uiDamageIndex = 1)
		: mAttackType( uiAttackType ), mDamage( uiDamage ), mDamageFileIndex( uiDamageIndex), mDontMoveTime( 0.0f )
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
	inline guint32 GetAttackType() {
		return mAttackType;
	}
	inline void SetAttackType(guint32 val) {
		mAttackType = val;
	}
	inline void SetDontMoveTime(float val) {
		mDontMoveTime = val;
	}
	inline float GetDontMoveTime() {
		return mDontMoveTime;
	}
};

#endif
