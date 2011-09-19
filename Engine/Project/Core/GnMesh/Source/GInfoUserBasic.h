#ifndef Core_GInfoUserBasic_h
#define Core_GInfoUserBasic_h

#include "GInfoBasic.h"

class GInfoUserBasic : public GInfoBasic
{
public:
	enum eUserColType
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
