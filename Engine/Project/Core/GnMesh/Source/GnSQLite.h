#ifndef __Core__GnSQLite__
#define __Core__GnSQLite__

#if ( GNUSE_OS == PLATFORM_IOS )
#include "/usr/include/sqlite3.h"
#else
typedef int sqlite3;
#endif

#include "GnSQLiteQuery.h"

class GnSQLite{
private:
	sqlite3* mpDatabase;
	
public:
	GnSQLite(const gchar* pcFileName = NULL);
	virtual ~GnSQLite();
	gint Open(const gchar* pcFileName);
	void Close();
	GnSQLiteSingleQuery ExecuteSingleQuery(const gchar* pcQuery);

protected:
	int Query(const gchar* pcquery, sqlite3_stmt*& pRetState);
};

#endif
