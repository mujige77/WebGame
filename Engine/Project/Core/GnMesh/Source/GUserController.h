//
//  GUserController.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 16..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GUserController__
#define __HiroCat__GUserController__

class GUserController : public GActorController
{
public:
	static GUserController* Create(const gchar* pcID, guint32 uiLevel);

public:
	void Start();
protected:
	bool InitActionComponents();
	bool InitInfoCompenent(const gchar* pcID, guint32 uiLevel);

};

#endif
