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
	GnTPrimitiveArray<GActorController*> mAttackToActors;
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
	virtual inline gtuint GetAttackedControllerSize() {
		return mAttackToActors.GetSize();
	}
	virtual inline GActorController* GetAttackedController(gtuint uiIndex) {
		return mAttackToActors.GetAt( uiIndex );
	}
	virtual inline void AddToAttackController(GActorController* pController) {
		mAttackToActors.Add( pController );
	}
};

#endif
