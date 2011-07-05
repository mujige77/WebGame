//
//  GGameEnvironment.cpp
//  Core
//
//  Created by Max Yoon on 11. 6. 30..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GnGamePCH.h"
#include "GMainGameEnvironment.h"

GGameEnvironment* GGameEnvironment::mpSingleton = NULL;

GGameEnvironment* GGameEnvironment::GetSingleton()
{
	return mpSingleton;
}