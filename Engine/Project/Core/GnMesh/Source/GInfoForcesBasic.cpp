//
//  GInfoForceBasic.cpp
//  Core
//
//  Created by Max Yoon on 11. 6. 25..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GInfoForcesBasic.h"
#include "GActorInfoDatabase.h"

void GInfoForcesBasic::LoadDataFromQuery(GnSQLiteQuery *pQuery)
{
	GnAssert( pQuery->GetColumnCount() == FORCESCOL_MAX );
	GInfoBasic::LoadDataFromQuery( pQuery );
}
