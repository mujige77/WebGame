#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GInfoBasic.h"
#include "GActorInfoDatabase.h"


void GInfoBasic::LoadDataFromQuery(GnSQLiteQuery* pQuery)
{
	mHP = (gint32)pQuery->GetIntField( COL_HP );
	mStrength = (guint32)pQuery->GetIntField( COL_STRENGTH );
	mMoveSpeed = (float)pQuery->GetFloatField( COL_MOVESPEED );
	mAttackSpeed = (float)pQuery->GetFloatField( COL_ATTACKSPEED );
	mAttackType = (gint32)pQuery->GetIntField( COL_ATTACKTYPE );
	mAttackCount = (guint32)pQuery->GetIntField( COL_ATTACKCOUNT );
	mPush = (guint32)pQuery->GetIntField( COL_PUSH );
	
	guint32 uilise = (gint32)pQuery->GetIntField( COL_LISEHP );
	mHP += GetLevel() * uilise;
	uilise = (guint32)pQuery->GetIntField( COL_LISEPOWER );
	mStrength += GetLevel() * uilise;
	float flise = (float)pQuery->GetFloatField( COL_LISEATTACKSPEED );
	mAttackSpeed += GetLevel() * flise;
}
