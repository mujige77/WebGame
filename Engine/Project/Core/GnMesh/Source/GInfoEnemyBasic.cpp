#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GInfoEnemyBasic.h"

void GInfoEnemyBasic::LoadDataFromQuery(GnSQLiteQuery *pQuery)
{
	GnAssert( pQuery->GetColumnCount() == ENEMYCOL_MAX );
	GInfoBasic::LoadDataFromQuery( pQuery );
}
