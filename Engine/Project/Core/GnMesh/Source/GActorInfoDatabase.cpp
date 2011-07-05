//
//  GActorInfoManager.cpp
//  Core
//
//  Created by Max Yoon on 11. 6. 23..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GActorInfoDatabase.h"

GnImplementSingleton(GActorInfoDatabase)

GActorInfoDatabase::GActorInfoDatabase() : mSqlite( GetFullPath( "ActorInfo.sqlite" ) )
{

}