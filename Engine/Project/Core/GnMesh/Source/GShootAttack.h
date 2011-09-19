//
//  GShootAttack.h
//  Core
//
//  Created by Max Yoon on 11. 8. 8..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GShootAttack_h
#define Core_GShootAttack_h
#include "GFarAttack.h"

class GShootAttack : public GFarAttack
{
	GnDeclareCreateAttack;
	
protected:
	GnVector2 mShootDirection;
	GnTimer mShootTimer;
public:
	static GFarAttack* CreateAttack(guint32 uiIndex);

public:
	void InitShooting(float fDirectionX, float fDirectionY);
	
public:
	virtual void Update(float fTime);
	virtual void SetPosition(GnVector2 cPos);
	virtual void SetFilpX(bool val);
};


#endif
