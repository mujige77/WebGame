#include "GnMeshPCH.h"
#include "GnSQLiteQuery.h"
#include "sqlite3.h"

GnSQLiteQuery::GnSQLiteQuery(sqlite3_stmt* pStatement, bool bEof)
	: mpStatement( pStatement ), mEof( bEof )
{
	mColumnCount = sqlite3_column_count( pStatement );
}

GnSQLiteQuery::~GnSQLiteQuery()
{
	Finalize();
}

gint GnSQLiteQuery::GetFieldDataType(gint iNumColumn)
{
	if ( iNumColumn < 0 || iNumColumn > mColumnCount-1 )
	{
		GnLogA( "Error SQLite - iNumColumn" );
	}
	
	return sqlite3_column_type( mpStatement, iNumColumn);
}

gint GnSQLiteQuery::GetIntField(gint iNumColumn)
{
	if ( GetFieldDataType( iNumColumn ) == SQLITE_NULL )
		return 0;
	else
		return sqlite3_column_int( mpStatement, iNumColumn );
}

double GnSQLiteQuery::GetFloatField(gint iNumColumn)
{
	if ( GetFieldDataType( iNumColumn ) == SQLITE_NULL )
		return 0;
	else
		return sqlite3_column_double( mpStatement, iNumColumn );
	
}

const gchar* GnSQLiteQuery::GetStringField(gint iNumColumn)
{
	if ( GetFieldDataType( iNumColumn ) == SQLITE_NULL )
		return NULL;
	else
		return (const gchar*)sqlite3_column_text( mpStatement, iNumColumn );
}

gint GnSQLiteQuery::GetFieldIndex(const gchar* szField)
{
	if (szField)
	{
		for (int nField = 0; nField < mColumnCount; nField++)
		{
			const char* szTemp = sqlite3_column_name( mpStatement, nField );			
			if ( GnStrcmp( szField, szTemp ) == 0)
				return nField;
		}
	}
	return -1;
}


const gchar* GnSQLiteQuery::GetFieldName(gint iCol)
{
	if( iCol < 0 || iCol > mColumnCount - 1 )
	{
		return NULL;
	}	
	return sqlite3_column_name( mpStatement, iCol );
}


const gchar* GnSQLiteQuery::GetFieldDeclType(gint iCol)
{
	if( iCol < 0 || iCol > mColumnCount - 1 )
	{
		return NULL;
	}
	
	return sqlite3_column_decltype( mpStatement, iCol );
}

void GnSQLiteQuery::NextRow()
{
	int nRet = sqlite3_step( mpStatement );
	
	if (nRet == SQLITE_DONE)
	{
		// no rows
		mEof = true;
	}
	else if (nRet != SQLITE_ROW)
	{
		// failed
		Finalize();
	}
}

void GnSQLiteQuery::Finalize()
{
	if ( mpStatement )
	{
		int nRet = sqlite3_finalize( mpStatement );
		mpStatement = 0;
		if (nRet != SQLITE_OK)
		{
			GnLogA( "Error Release Query" );
		}
	}
}