#include "GnMeshPCH.h"
#include "GnSQLite.h"

GnSQLite::GnSQLite(const gchar* pcFileName) : mpDatabase( NULL )
{
#if ( GNUSE_OS == PLATFORM_IOS  )
	if( pcFileName )
		GnVerify( Open( pcFileName ) == SQLITE_OK );
#endif
}
GnSQLite::~GnSQLite()
{
	Close();
}

gint GnSQLite::Open(const gchar* pcFileName)
{
#if ( GNUSE_OS == PLATFORM_IOS )
	int result = sqlite3_open(pcFileName, &mpDatabase);

	return result;
#else
	return GNSQLITE_NULL;
#endif
}

void GnSQLite::Close()
{
#if ( GNUSE_OS == PLATFORM_IOS  )
	if( mpDatabase ) 
		sqlite3_close( mpDatabase );
#endif
}

GnSQLiteQuery GnSQLite::ExecuteSingleQuery(const gchar *pcQuery, ...)
{
	sqlite3_stmt* state = NULL;
	int ret = Query( pcQuery, state );
#if ( GNUSE_OS == PLATFORM_IOS  )
	if ( ret == SQLITE_OK  )
	{
		ret = sqlite3_step(state);
		if( ret == SQLITE_ROW ) 
			return GnSQLiteSingleQuery( state, false );
	}
#endif
	return GnSQLiteQuery( NULL, true );
}

int GnSQLite::Query(const gchar *pcQuery, sqlite3_stmt*& pRetState)
{
#if ( GNUSE_OS == PLATFORM_IOS  )
	const char* szTail=0;
	int ret = sqlite3_prepare( mpDatabase, pcQuery, -1, &pRetState, &szTail );
	if ( ret != SQLITE_OK  )
	{
		GnLogA( "Error SQLite Query - query = %s, code = %d, msg = %s", pcQuery, ret, szTail );
	}
	return ret;
#else
	return GNSQLITE_NULL;
#endif
}
