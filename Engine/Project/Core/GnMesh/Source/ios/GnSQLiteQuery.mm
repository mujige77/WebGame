//
//  GnSQLiteQuery.cpp
//  Core
//
//  Created by Max Yoon on 11. 6. 24..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnMeshPCH.h"
#include "GnSQLiteQuery.h"

GnSQLiteQuery::GnSQLiteQuery(sqlite3_stmt* pStatement, bool bEof)
	: mpStatement( pStatement ), mEof( bEof )
{
	mColumnCount = sqlite3_column_count( pStatement );
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

GnSQLiteSingleQuery::GnSQLiteSingleQuery(sqlite3_stmt* pStatement, bool bEof)
	: GnSQLiteQuery( pStatement, bEof )
{
	
}