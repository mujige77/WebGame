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
		COL_STRENGTH = 5,
		COL_MOVERANGE = 6,
		COL_MAX,
	};
private:
	gint32 mHP;
	guint32 mStrength;
	float mMoveRange;
	
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
	inline void SetMoveRange(float val) {
		mMoveRange = val;
	}
	inline float GetMoveRange() {
		return mMoveRange;
	}

};

#endif
