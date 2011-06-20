//
//  GMobController.cpp
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#include "GamePCH.h"
#include "GEnemyController.h"

GEnemyController::GEnemyController()
{
	
}

GEnemyController* GEnemyController::Create(const gchar *pcFilePath)
{
	GEnemyController* controller = GnNew GEnemyController();
	controller->LoadActor(pcFilePath);
	return controller;
} 
