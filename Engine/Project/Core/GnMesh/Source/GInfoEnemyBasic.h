#ifndef __Core__GInfoEnemyBasic__
#define __Core__GInfoEnemyBasic__

#include "GInfoBasic.h"

class GInfoEnemyBasic : public GInfoBasic
{	
public:
	enum eEnemyColType
	{
		COL_DROPMONEY = GInfoBasic::COL_MAX,
		ENEMYCOL_MAX,
	};
	
private:
	guint32 mDropMoney;

public:
	inline guint32 GetDropMoney() {
		return mDropMoney;
	}
	
protected:
	void LoadDataFromQuery(GnSQLiteQuery* pQuery);
	inline virtual const gchar* GetUseDatabaseTableName() {
		return "EnemyBasicInfo";
	}

};

#endif
