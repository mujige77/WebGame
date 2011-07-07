#include "GnMeshPCH.h"
#include "GnSQLiteQuery.h"

GnSQLiteQuery::GnSQLiteQuery(sqlite3_stmt* pStatement, bool bEof)
	: mpStatement( pStatement ), mEof( bEof )
{
#if ( GNUSE_OS == PLATFORM_IOS  )
	mColumnCount = sqlite3_column_count( pStatement );
#endif
}

gint GnSQLiteQuery::GetFieldDataType(gint iNumColumn)
{
#if ( GNUSE_OS == PLATFORM_IOS  )
	if ( iNumColumn < 0 || iNumColumn > mColumnCount-1 )
	{
		GnLogA( "Error SQLite - iNumColumn" );
	}
	
	return sqlite3_column_type( mpStatement, iNumColumn);
#else
	return SQLITE_NULL;
#endif
}

gint GnSQLiteQuery::GetIntField(gint iNumColumn)
{
#if ( GNUSE_OS == PLATFORM_IOS  )
	if ( GetFieldDataType( iNumColumn ) == SQLITE_NULL )
		return 0;
	else
		return sqlite3_column_int( mpStatement, iNumColumn );
#else
	return SQLITE_NULL;
#endif
}

double GnSQLiteQuery::GetFloatField(gint iNumColumn)
{
#if ( GNUSE_OS == PLATFORM_IOS  )
	if ( GetFieldDataType( iNumColumn ) == SQLITE_NULL )
		return 0;
	else
		return sqlite3_column_double( mpStatement, iNumColumn );
#else
	return SQLITE_NULL;
#endif	
}

const gchar* GnSQLiteQuery::GetStringField(gint iNumColumn)
{
#if ( GNUSE_OS == PLATFORM_IOS  )
	if ( GetFieldDataType( iNumColumn ) == SQLITE_NULL )
		return NULL;
	else
		return (const gchar*)sqlite3_column_text( mpStatement, iNumColumn );
#else
	return NULL;
#endif
}

GnSQLiteSingleQuery::GnSQLiteSingleQuery(sqlite3_stmt* pStatement, bool bEof)
	: GnSQLiteQuery( pStatement, bEof )
{
	
}