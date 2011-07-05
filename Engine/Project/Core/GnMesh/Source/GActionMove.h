//
//  GActionMove.h
//  HiroCat
//
//  Created by Max Yoon on 11. 6. 20..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __HiroCat__GActionMove__
#define __HiroCat__GActionMove__

#include "GAction.h"

class GActionMove : public GAction
{
	GnDeclareFlags( guint32 );
	enum
	{
		MASK_MOVELEFT = 0x00000001,
		MASK_MOVERIGHT = 0x00000002,
		MASK_MOVEUP = 0x00000004,
		MASK_MOVEDOWN = 0x00000008,
	};
public:
	enum eMoveType
	{
		MOVELEFT,
		MOVERIGHT,
		MOVEUP,
		MOVEDOWN,
		MOVE_MAX,
	};
	
protected:
	GnVector2 mMoveRange;
	GnVector2 mMoveVector;
	GLayer* mpActorLayer;
	
public:
	GActionMove(GActorController* pController);
	
public:
	virtual void Update(float fDeltaTime);
	virtual void SetMove(gtuint uiType, bool bCleanMove);
	virtual inline gtint GetActionType() {
		return ACTION_MOVE;
	}
	inline void AttachCompentToController()
	{
		GetController()->AddCurrentAction( this );
		GetController()->GetActor()->SetTargetAnimation( ANI_WALK );
	}
public:
	inline GnVector2& GetMoveRange() {
		return mMoveRange;
	}
	inline void SetMoveRange(GnVector2 val) {
		mMoveRange = val;
	}
	inline void SetMoveRangeX(float val) {
		mMoveRange.x = val;
	}
	inline void SetMoveRangeY(float val) {
		mMoveRange.y = val;
	}
	inline GnVector2& GetMoveVector() {
		return mMoveVector;
	}
	inline virtual void SetMoveVector(GnVector2 val) {
		mMoveVector = val;
	}	
	inline void SetMoveLeft(bool val) {
		SetBit( val, MASK_MOVELEFT );
	}
	inline bool GetMoveLeft() {
		return GetBit( MASK_MOVELEFT );
	}
	inline void SetMoveRight(bool val) {
		SetBit( val, MASK_MOVERIGHT );
	}
	inline bool GetMoveRight() {
		return GetBit( MASK_MOVERIGHT );
	}
	inline void SetMoveUp(bool val) {
		SetBit( val, MASK_MOVEUP );
	}
	inline bool GetMoveUp() {
		return GetBit( MASK_MOVEUP );
	}
	inline void SetMoveDown(bool val) {
		SetBit( val, MASK_MOVEDOWN );
	}
	inline bool GetMoveDown() {
		return GetBit( MASK_MOVEDOWN );
	}
	inline void SetActorLayer(GLayer* pActorLayer) {
		mpActorLayer = pActorLayer;
	}
protected:
	inline GLayer* GetActorLayer() {
		return mpActorLayer;
	}
};

#endif
