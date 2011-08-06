#ifndef __Core__GnSQLite__
#define __Core__GnSQLite__

#include "GnSQLiteQuery.h"

class sqlite3;
class GnSQLite
{
	enum
	{
		GNSQLITE_SUCCESS = 0,
		GNSQLITE_ROW = 100,
	};
private:
	sqlite3* mpDatabase;
	
public:
	GnSQLite(const gchar* pcFileName = NULL);
	virtual ~GnSQLite();
	gint Open(const gchar* pcFileName);
	void Close();
	GnSQLiteSingleQuery ExecuteSingleQuery(const gchar* pcQuery);
	int Execute(const char* pcQuery);
	
protected:
	int Query(const gchar* pcquery, sqlite3_stmt*& pRetState);
};

#endif
