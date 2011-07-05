//
//  GMobController.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GMobController__
#define __HiroCat__GMobController__

class GEnemyController : public GActorController
{
public:
	static GEnemyController* Create(const gchar* pcID, guint32 uiLevel);
	
protected:
	GEnemyController();

protected:
	bool InitActionComponents();
	bool InitInfoCompenent(const gchar* pcID, guint32 uiLevel);
};

#endif
