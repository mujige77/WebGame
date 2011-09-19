#ifndef __Core__GInfoBasic__
#define __Core__GInfoBasic__
#include "GInfo.h"

class GnSQLiteQuery;
class GInfoBasic : public GInfo
{
public:
	enum eColumnType
	{
		COL_HP = 3,
		COL_STRENGTH = 4,
		COL_MOVESPEED = 5,
		COL_ATTACKSPEED,
		COL_ATTACKTYPE,
		COL_ATTACKCOUNT,
		COL_LISEHP,
		COL_LISEPOWER,
		COL_LISESPEED,
		COL_LISEATTACKSPEED,
		COL_PUSH,
		COL_MAX,
	};
protected:
	gint32 mHP;
	guint32 mStrength;
	float mMoveSpeed;
	float mAttackSpeed;
	gint32 mAttackType;
	guint32 mAttackCount;
	guint32 mPush;
	
public:
	virtual void LoadDataFromQuery(GnSQLiteQuery* pQuery);
	
public:
	virtual inline gtint GetInfoType() {
		return GInfo::INFO_BASIC;
	}
	inline gint32 GetHP() {
		return mHP;
	}
	inline void SetHP(gint32 uiHP) {
		mHP = uiHP;
	}
	inline guint32 GetStrength() {
		return mStrength;
	}
	inline void SetStrength(guint32 val) {
		mStrength = val;
	}
	inline void SetMoveSpeed(float val) {
		mMoveSpeed = val;
	}
	inline float GetMoveSpeed() {
		return mMoveSpeed;
	}
	inline float GetAttackSpeed() {
		return mAttackSpeed;
	}
	inline void SetAttackSpeed(float val) {
		mAttackSpeed = val;
	}
	inline gint32 GetAttackType() {
		return mAttackType;
	}
	inline void SetAttackType(gint32 val) {
		mAttackType = val;
	}
	inline guint32 GetAttackCount() {
		return mAttackCount;
	}
	inline void SetAttackCount(guint32 val) {
		mAttackCount = val;
	}
	inline guint32 GetPush() {
		return mAttackCount;
	}
	inline void SetPush(guint32 val) {
		mAttackCount = val;
	}
};

#endif
