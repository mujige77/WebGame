//
//  GInfoForceBasic.h
//  Core
//
//  Created by Max Yoon on 11. 6. 25..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

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
