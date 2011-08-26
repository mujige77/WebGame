//
//  GBoltAttack.h
//  Core
//
//  Created by Max Yoon on 11. 8. 24..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GBoltAttack_h
#define Core_GBoltAttack_h

#include "GFarAttack.h"

class GBoltAttack : public GFarAttack
{
	GnDeclareCreateAttack;
public:
	static GFarAttack* CreateAttack(guint32 uIndex);
	
public:
	void Update(float fTime);
	void SetPosition(GnVector2 cPos);
	inline eBasicStartPosition GetBasicStartPosition() {
		return eUserPosition;
	}
	
};

#endif
