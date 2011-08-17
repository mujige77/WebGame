//
//  GnSQLite.cpp
//  
//
//  Created by Max Yoon on 11. 6. 23..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnMeshPCH.h"
#include "GnSQLite.h"
#include "sqlite3.h"

GnSQLite::GnSQLite(const gchar* pcFileName) : mpDatabase( NULL )
{
	if( pcFileName )
		GnVerify( Open( pcFileName ) == GNSQLITE_SUCCESS );
}
GnSQLite::~GnSQLite()
{
	Close();
}

gint GnSQLite::Open(const gchar* pcFileName)
{
	int result = sqlite3_open(pcFileName, &mpDatabase);

	return result;
}

void GnSQLite::Close()
{
	if( mpDatabase ) 
		sqlite3_close( mpDatabase );
}

GnSQLiteQuery GnSQLite::ExecuteSingleQuery(const gchar *pcQuery, ...)
{
	gchar combineQuery[512] = { 0, };
	va_list args;
	va_start( args, pcQuery );
#ifdef __GNUC__
	gint err = vsprintf( combineQuery, pcQuery, args );
#else // #ifdef __GNUC__
	gint err = vsprintf_s( combineQuery, sizeof(combineQuery), format, args );
#endif // #ifdef __GNUC__
	va_end(args);
	if( err != 0 )
	{
		sqlite3_stmt* state = NULL;
		int ret = Query( combineQuery, state );

		if ( ret == GNSQLITE_SUCCESS  )
		{
			ret = sqlite3_step(state);
			if( ret == GNSQLITE_ROW ) 
				return GnSQLiteQuery( state, false );
			else if( GNSQLITE_DONE )
				return GnSQLiteQuery( state, true );
		}
	}
	return GnSQLiteQuery( NULL, true );
}

int GnSQLite::Query(const gchar *pcQuery, sqlite3_stmt*& pRetState)
{
	const char* szTail=0;
	int ret = sqlite3_prepare( mpDatabase, pcQuery, -1, &pRetState, &szTail );
	if ( ret != GNSQLITE_SUCCESS  )
	{
		GnLogA( "Error SQLite Query - query = %s, code = %d, msg = %s", pcQuery, ret, szTail );
	}
	return ret;
}

GnSQLiteTable GnSQLite::GetTable(const char* pcQuery, ...)
{
	gchar combineQuery[512] = { 0, };
	va_list args;
	va_start( args, pcQuery );
#ifdef __GNUC__
	gint err = vsprintf( combineQuery, pcQuery, args );
#else // #ifdef __GNUC__
	gint err = vsprintf_s( combineQuery, sizeof(combineQuery), format, args );
#endif // #ifdef __GNUC__
	va_end(args);
	if( err != 0 )
	{
		char* error=0;
		char** paszResults=0;
		int nRows(0);
		int nCols(0);
		
		int ret = sqlite3_get_table( mpDatabase, combineQuery, &paszResults, &nRows, &nCols, &error );
		
		if( ret == GNSQLITE_SUCCESS )
			return GnSQLiteTable( paszResults, nRows, nCols );
		else
			GnLogA( "Error SQLite Execute - query = %s, code = %d, msg = %s", pcQuery, ret, error );
	}	
	return GnSQLiteTable( NULL, 0, 0 );
}

int GnSQLite::Execute(const char* pcQuery, ...)
{
	gchar combineQuery[512] = { 0, };
	va_list args;
	va_start( args, pcQuery );
#ifdef __GNUC__
	gint err = vsprintf( combineQuery, pcQuery, args );
#else // #ifdef __GNUC__
	gint err = vsprintf_s( combineQuery, sizeof(combineQuery), format, args );
#endif // #ifdef __GNUC__
	va_end(args);
	if( err != 0 )
	{
		char* error=0;
		int ret = sqlite3_exec( mpDatabase, combineQuery, 0, 0, &error );	
		if ( ret != GNSQLITE_SUCCESS )
			GnLogA( "Error SQLite Execute - query = %s, code = %d, msg = %s", combineQuery, ret, error );
		return ret;	
	}
	return GNSQLITE_ERROR;
}