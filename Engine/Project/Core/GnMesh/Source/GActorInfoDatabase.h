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
