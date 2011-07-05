//
//  GActorInfoManager.h
//  Core
//
//  Created by Max Yoon on 11. 6. 23..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GActorInfoDatabase__
#define __Core__GActorInfoDatabase__

#include "GnSQLite.h"

class GActorInfoDatabase : public GnMemoryObject
{
	GnDeclareSingleton(GActorInfoDatabase);
private:
	GnSQLite mSqlite;
	
public:
	GActorInfoDatabase();
	GnSQLite* GetSql() {
		return &mSqlite;
	}
};

#define GetActorInfoDatabase GActorInfoDatabase::GetSingleton
#endif
