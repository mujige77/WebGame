//
//  GnSQLite.cpp
//  
//
//  Created by Max Yoon on 11. 6. 23..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnMeshPCH.h"
#include "GnSQLite.h"

GnSQLite::GnSQLite(const gchar* pcFileName) : mpDatabase( NULL )
{
	if( pcFileName )
		GnVerify( Open( pcFileName ) == SQLITE_OK );
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

GnSQLiteSingleQuery GnSQLite::ExecuteSingleQuery(const gchar *pcQuery)
{
	sqlite3_stmt* state = NULL;
	int ret = Query( pcQuery, state );

	if ( ret == SQLITE_OK  )
	{
		ret = sqlite3_step(state);
		if( ret == SQLITE_ROW ) 
			return GnSQLiteSingleQuery( state, false );
	}
	return GnSQLiteSingleQuery( NULL, true );
}

int GnSQLite::Query(const gchar *pcQuery, sqlite3_stmt*& pRetState)
{
	const char* szTail=0;
	int ret = sqlite3_prepare( mpDatabase, pcQuery, -1, &pRetState, &szTail );
	if ( ret != SQLITE_OK  )
	{
		GnLogA( "Error SQLite Query - query = %s, code = %d, msg = %s", pcQuery, ret, szTail );
	}
	return ret;
}
