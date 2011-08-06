#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GInfo.h"
#include "GActorInfoDatabase.h"


bool GInfo::LoadDataFromSql(const gchar* pcID, const guint32 uiLevel, GnSQLite* pSql)
{
	gchar combineQuery[256];
	GnSprintf( combineQuery, sizeof(combineQuery), "SELECT * FROM %s WHERE id='%s' AND level=%d"
			  , GetUseDatabaseTableName(), pcID, uiLevel );
	GnSQLiteSingleQuery query = pSql->ExecuteSingleQuery( combineQuery );
	if( query.IsEof() )
		return false;
	
	LoadDataFromQuery( &query );	
	return true;
}