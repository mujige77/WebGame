//
//  GnSQLiteQuery.h
//  Core
//
//  Created by Max Yoon on 11. 6. 24..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GnSQLiteQuery__
#define __Core__GnSQLiteQuery__

#if ( GNUSE_OS == FLATFORM_IOS )
#include "/usr/include/sqlite3.h"
#endif

class GnSQLiteQuery
{
private:
	sqlite3_stmt* mpStatement;
	bool mEof;
	guint mColumnCount;
	
public:
	GnSQLiteQuery(sqlite3_stmt* pStatement, bool bEof);
	gint GetFieldDataType(gint iNumColumn);
	gint GetIntField(gint iNumColumn);
	double GetFloatField(gint iNumColumn);
	const gchar* GetStringField(gint iNumColumn);
	
	inline void SetColumnCount(guint uiCount) {
		mColumnCount = uiCount;
	}
	inline guint GetColumnCount() {
		return mColumnCount;
	}
	inline void SetIsEof(bool val) {
		mEof = true;
	}
	inline bool IsEof() {
		return mEof;
	}
};

class GnSQLiteSingleQuery : public GnSQLiteQuery
{
public:
	GnSQLiteSingleQuery(sqlite3_stmt* pStatement, bool bEof);
};

#endif
