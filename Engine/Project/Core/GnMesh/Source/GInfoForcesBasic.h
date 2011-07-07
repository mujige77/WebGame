#ifndef __Core__GInfoForceBasic__
#define __Core__GInfoForceBasic__

#include "GInfoBasic.h"

class GInfoForcesBasic : public GInfoBasic
{
public:
	enum eForcesColType
	{
		FORCESCOL_MAX = GInfoBasic::COL_MAX,
	};
	
public:
	

protected:
	void LoadDataFromQuery(GnSQLiteQuery* pQuery);
	inline virtual const gchar* GetUseDatabaseTableName() {
		return "ForcesBasicInfo";
	}
};

#endif
