//
//  GgGameEBM.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 13..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GgGameEBM__
#define __HiroCat__GgGameEBM__

#include <GnSystemEBM.h>
#include <GnMainEBM.h>
#include <GnMeshEBM.h>
#include <GnMainHeader.h>
#include <GnMeshHeader.h>
#include <cocos2d.h>
#include <GnPathUtil.h>

#include "GBoltAttack.h"
#include "GShootAttack.h"
#include "GFallBoomAttack.h"
#include "GMultiShootAttack.h"
#include "GFireAttack.h"

static std::string gFilePath;

static inline void StartupEBM()
{
	// 라이브러리 문저
	GnSystemEBM::StartupEBM();
	GnMainEBM::StartupEBM();
	GnMeshEBM::StartupEBM();
	
	GnRegsterCreateFunction(GBoltAttack);
	GnRegsterCreateFunction(GShootAttack);
	GnRegsterCreateFunction(GFallBoomAttack);
	GnRegsterCreateFunction(GMultiShootAttack);
	GnRegsterCreateFunction(GFireAttack);
	
	gFilePath = GetFullPath( "Data" );
	gFilePath += "/";
	GnTexture::SetTextureWorkPath( gFilePath.c_str() );
	GnSystem::SetWorkDirectory( gFilePath.c_str() );
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	GetGameState()->SetGameDisplaySize( size.width, size.height );
}

static inline void ShoutdownEBM()
{
	GnMeshEBM::ShutdownEBM();
	GnMainEBM::ShutdownEBM();
	GnSystemEBM::ShutdownEBM();
}

#endif
