//
//  GCastleForces.h
//  Core
//
//  Created by Max Yoon on 11. 7. 19..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GCastleForces__
#define __Core__GCastleForces__

#include "GCastle.h"

class GIconGage;
class GCastleForces : public GCastle
{
public:
	static GCastleForces* CreateCastle(GLayer* pInterfaceLayer, GLayer* pCastleLayer
		, GStageInfo* pStageInfo, GStageInfo::GCastleFiles* pFiles
		, GStageInfo::GCastlePositions* pPositions);

protected:
	static bool CreateCastleGage(GLayer* pInterfaceLayer, GIconGage& cOutGage);
	
protected:
	void Init();
};

#endif
