//
//  GInfoEnemyBasic.cpp
//  Core
//
//  Created by Max Yoon on 11. 6. 25..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GInfoEnemyBasic.h"

void GInfoEnemyBasic::LoadDataFromQuery(GnSQLiteQuery *pQuery)
{
	GnAssert( pQuery->GetColumnCount() == ENEMYCOL_MAX );
	GInfoBasic::LoadDataFromQuery( pQuery );
}
