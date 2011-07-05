//
//  GInfoBasic.cpp
//  Core
//
//  Created by Max Yoon on 11. 6. 22..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GInfoBasic.h"
#include "GActorInfoDatabase.h"


void GInfoBasic::LoadDataFromQuery(GnSQLiteQuery* pQuery)
{
	mHP = (gint32)pQuery->GetIntField( COL_HP );
	mStrength = (guint32)pQuery->GetIntField( COL_STRENGTH );
	mMoveRangeX = (float)pQuery->GetFloatField( COL_MOVERANGE );
}
