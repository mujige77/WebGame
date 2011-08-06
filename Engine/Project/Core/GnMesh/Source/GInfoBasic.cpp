#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GInfoBasic.h"
#include "GActorInfoDatabase.h"


void GInfoBasic::LoadDataFromQuery(GnSQLiteQuery* pQuery)
{
	mHP = (gint32)pQuery->GetIntField( COL_HP );
	mStrength = (guint32)pQuery->GetIntField( COL_STRENGTH );
	mMoveRange = (float)pQuery->GetFloatField( COL_MOVERANGE );
}
