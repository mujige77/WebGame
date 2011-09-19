#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GInfo.h"
#include "GActorInfoDatabase.h"


bool GInfo::LoadDataFromSql(const gchar* pcID, const guint32 uiLevel, GnSQLite* pSql)
{
	GnSQLiteQuery query = pSql->ExecuteSingleQuery( "SELECT * FROM %s WHERE id='%s' AND level=1"
		, GetUseDatabaseTableName(), pcID);
	if( query.IsEof() )
		return false;
	
	mLevel = uiLevel;
	LoadDataFromQuery( &query );
	return true;
}