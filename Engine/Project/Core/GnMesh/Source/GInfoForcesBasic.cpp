#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GInfoForcesBasic.h"
#include "GActorInfoDatabase.h"

void GInfoForcesBasic::LoadDataFromQuery(GnSQLiteQuery *pQuery)
{
	GnAssert( pQuery->GetColumnCount() == FORCESCOL_MAX );
	GInfoBasic::LoadDataFromQuery( pQuery );
	
	guint32 abLevel = GUserAbility::GetAbilityLevel( eIndexUnitSpeed );
	float flise = (float)pQuery->GetFloatField( COL_LISESPEED );
	mMoveSpeed += abLevel * flise;
}
