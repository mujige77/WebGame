#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GInfoForcesBasic.h"
#include "GActorInfoDatabase.h"

void GInfoForcesBasic::LoadDataFromQuery(GnSQLiteQuery *pQuery)
{
	GnAssert( pQuery->GetColumnCount() == FORCESCOL_MAX );
	GInfoBasic::LoadDataFromQuery( pQuery );
}
