//
//  GMultiShootAttack.h
//  Core
//
//  Created by Max Yoon on 11. 8. 29..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GMultiShootAttack_h
#define Core_GMultiShootAttack_h

#include "GShootAttack.h"

class GMultiShootAttack : public GShootAttack
{
	GnDeclareCreateAttack;
	
protected:
	GnVector2 mShootDirection;
	GnTimer mShootTimer;
public:
	static GFarAttack* CreateAttack(guint32 uiIndex);
	
public:
	virtual inline void SendedAttackTo() {
		++mCurrentAttackCount;
	}
	virtual inline void EndedAttackTo() {
		if( GetCurrentAttackCount() >= GetAttackCount() )
			SetIsEnableAttack( false );
	}
};

#endif
