#ifndef __Core__GnSQLite__
#define __Core__GnSQLite__

#include "GnSQLiteQuery.h"
#include "GnSQLiteTable.h"

class sqlite3;
class GnSQLite
{
protected:
	enum
	{
		GNSQLITE_SUCCESS = 0, // SQLITE_OK
		GNSQLITE_ERROR = 1, // SQLITE_ERROR
		GNSQLITE_ROW = 100, // SQLITE_ROW
		GNSQLITE_DONE = 101,
	};
private:
	sqlite3* mpDatabase;
	
public:
	GnSQLite(const gchar* pcFileName = NULL);
	virtual ~GnSQLite();
	gint Open(const gchar* pcFileName);
	void Close();
	GnSQLiteQuery ExecuteSingleQuery(const gchar* pcQuery, ...);
	GnSQLiteTable GetTable(const gchar* pcQuery, ...);
	int Execute(const char* pcQuery, ...);
	
protected:
	int Query(const gchar* pcquery, sqlite3_stmt*& pRetState);
};

#endif
