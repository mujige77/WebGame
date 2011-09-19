#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GInfoUserBasic.h"
#include "GActorInfoDatabase.h"

void GInfoUserBasic::LoadDataFromQuery(GnSQLiteQuery *pQuery)
{
	GnAssert( pQuery->GetColumnCount() == FORCESCOL_MAX );
	GInfoBasic::LoadDataFromQuery( pQuery );
	
	guint32 abLevel = GUserAbility::GetAbilityLevel( eIndexSpeed );
	mMoveSpeed += GetLevel() * abLevel;
}
