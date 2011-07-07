#ifndef __Core__GInfoEnemyBasic__
#define __Core__GInfoEnemyBasic__

#include "GInfoBasic.h"

class GInfoEnemyBasic : public GInfoBasic
{	
public:
	enum eEnemyColType
	{
		ENEMYCOL_MAX = GInfoBasic::COL_MAX,
	};
	
public:

protected:
	void LoadDataFromQuery(GnSQLiteQuery* pQuery);
	inline virtual const gchar* GetUseDatabaseTableName() {
		return "EnemyBasicInfo";
	}
};

#endif
