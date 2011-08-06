//
//  GCastleEnemy.h
//  Core
//
//  Created by Max Yoon on 11. 7. 20..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GCastleEnemy__
#define __Core__GCastleEnemy__

#include "GCastle.h"

class GIconGage;
class GCastleEnemy : public GCastle
{
public:
	static GCastleEnemy* CreateCastle(GLayer* pInterfaceLayer, GLayer* pCastleLayer
		, GStageInfo* pStageInfo, GStageInfo::GCastleFiles* pFiles
		, GStageInfo::GCastlePositions* pPositions);
	
protected:
	static bool CreateCastleGage(GLayer* pInterfaceLayer, GIconGage& cOutGage);
};

#endif
