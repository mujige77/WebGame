#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GInfo.h"
#include "GActorInfoDatabase.h"


bool GInfo::LoadDataFromSql(const gchar* pcID, const guint32 uiLevel, GnSQLite* pSql)
{
	GnSQLiteQuery query = pSql->ExecuteSingleQuery( "SELECT * FROM %s WHERE id='%s' AND level=%d"
		, GetUseDatabaseTableName(), pcID, uiLevel);
	if( query.IsEof() )
		return false;
	
	LoadDataFromQuery( &query );	
	return true;
}