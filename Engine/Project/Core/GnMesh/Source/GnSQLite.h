//
//  GnSQLite.h
//  Core
//
//  Created by Max Yoon on 11. 6. 23..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GnSQLite__
#define __Core__GnSQLite__

#if ( GNUSE_OS == FLATFORM_IOS )
#include "/usr/include/sqlite3.h"
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
