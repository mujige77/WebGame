//
//  GInfo.h
//  Core
//
//  Created by Max Yoon on 11. 6. 23..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GInfo__
#define __Core__GInfo__

#include "GActorInfoDatabase.h"

class GInfo : public GnMemoryObject
{
public:
	static const gtint NULL_TYPE = -1;
public:
	enum eInofComponentType
	{
		INFO_BASIC,
		INFO_MAX,
	};
	
public:
	bool LoadDataFromSql(const gchar* pcID, const guint32 uiLevel, GnSQLite* pSql);
	
	virtual inline gtint GetInfoType() {
		return GInfo::NULL_TYPE;
	}
protected:
	virtual void LoadDataFromQuery(GnSQLiteQuery* pQuery) = 0;
	virtual const gchar* GetUseDatabaseTableName() = 0;
	
//	inline void ExecuteSingleQueryFromID(GnSQLite* pSql, const gchar* pcTableaName
//		, const gchar* pcID, guint32 uiLevel)
//	{
//		gchar combineQuery[256];
//		GnSprintf( combineQuery, sizeof(combineQuery), "SELECT * FROM %s WHERE id=%s AND %d"
//			, pcTableaName, pcID, uiLevel );
//		GnSQLiteSingleQuery query = pSql->ExecuteSingleQuery( combineQuery );
//		LoadDataFromQuery( &query );
//	}
};

#endif
