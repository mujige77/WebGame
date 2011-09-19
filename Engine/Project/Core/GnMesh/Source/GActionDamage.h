//
//  GActionDamage.h
//  Core
//
//  Created by Max Yoon on 11. 7. 13..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GActionDamage__
#define __Core__GActionDamage__

#include "GAction.h"
#include "GAttackDamageInfo.h"

class GnIProgressBar;
class GActionDamage : public GAction
{
	GnDeclareFlags(guint16);
	enum
	{
		MASK_PUSHDAMAGE = 0x0001,
		MASK_DOWNDAMGE = 0x0002,
		MASK_DONTMOVE = 0x0004,		
		MASK_ENDMOTION = 0x0010,
		MASK_ENDEFFECTANIMATION = 0x0020,
		MASK_ENDPUSHPOSITION = 0x0040,
		MASK_ICE = 0x0100,
		MASK_ENABLE_SETSTARTACTION = 0x0200,
	};
protected:
	GLayer* mpActorLayer;
	gint mEffectIndex;
	Gn2DMeshObjectPtr mpsMeshObject;
	GAttackDamageInfo mAttackDamage;
	float mDownTime;
	float mDownAcumTime;
	GnTimer mPushTimer;
	GnVector2 mPushDownPosition;
	GnVector2 mPushDamagePosition;
	GnVector2 mPushDelta;
	GnVector2 mPushAcum;
	float mDontMoveTime;
	float mDontMoveAcumTime;
	
public:
	GActionDamage(GActorController* pController);
	virtual ~ GActionDamage();
	GnVector2ExtraData* CreateDamageEffect();
	void SetAttackDamage(GAttackDamageInfo* pInfo);
	bool IsEnableDamage();
	
public:
	void Update(float fTime);
	void AttachActionToController();
	void DetachActionToController();
	inline gtint GetActionType() {
		return ACTION_DAMAGE;
	}
	
protected:
	bool UpdatePush(float fTime, GnVector2& cPosition);
	
public:
	inline void SetActorLayer(GLayer* pActorLayer) {
		mpActorLayer = pActorLayer;
	}
	inline gint GetEffectIndex() {
		return mEffectIndex;
	}
	inline void SetEffectIndex(gint uiIndex) {
		mEffectIndex = uiIndex;
	}
	inline bool IsPushDamage() {
		return GetBit( MASK_PUSHDAMAGE );
	}
	inline void SetIsPushDamage(bool val) {
		SetBit( val, MASK_PUSHDAMAGE );
	}	
	inline bool IsDownDamage() {
		return GetBit( MASK_DOWNDAMGE );
	}
	inline void SetIsDownDamage(bool val) {
		SetBit( val, MASK_DOWNDAMGE );
	}
	inline bool IsDontMove() {
		return GetBit( MASK_DONTMOVE );
	}
	inline bool IsIce() {
		return GetBit( MASK_ICE );
	}
	inline void SetIsIce(bool val) {
		SetBit( val, MASK_ICE );
	}
	inline void SetIsDontMove(bool val, bool bIce = true) {
		SetBit( val, MASK_DONTMOVE );
		SetBit( bIce, MASK_ICE );
	}
	inline bool IsEnableSetStartAction() {
		return GetBit( MASK_ENABLE_SETSTARTACTION );
	}
	inline void SetIsEnableSetStartAction(bool val) {
		SetBit( val, MASK_ENABLE_SETSTARTACTION );
	}	
	inline void SetPushDelta(GnVector2 cPos) {
		mPushDelta = cPos;
	}
	inline void SetDontMoveTime(float val) {
		mDontMoveTime = val;
		mDontMoveAcumTime = 0.0f;
	}
protected:
	inline bool IsEndMotion() {
		return GetBit( MASK_ENDMOTION );
	}
	inline void SetIsEndMotion(bool val) {
		SetBit( val, MASK_ENDMOTION );
	}
	inline bool IsEndEffectAnimation() {
		return GetBit( MASK_ENDEFFECTANIMATION );
	}
	inline void SetIsEndEffectAnimation(bool val) {
		SetBit( val, MASK_ENDEFFECTANIMATION );
	}
	inline bool IsEndPushPosition() {
		return GetBit( MASK_ENDPUSHPOSITION );
	}
	inline void SetIsEndPushPosition(bool val) {
		SetBit( val, MASK_ENDPUSHPOSITION );
	}
protected:	
	GAttackDamageInfo* GetAttackDamageInfo() {
		return &mAttackDamage;
	}
	
protected:
	inline GLayer* GetActorLayer() {
		return mpActorLayer;
	}
	inline void RemoveMeshParent() {
		if( mpsMeshObject && mpsMeshObject->GetMesh()->getParent() )
			GetActorLayer()->RemoveChild( mpsMeshObject );
	}
};

//class GnIProgressBar;
//class GActionDownDamage : public GActionDamage
//{
//public:
//	GActionDownDamage(GActorController* pController);
//	virtual ~GActionDownDamage();
//	
//public:
//	void Update(float fTime);
//	void AttachActionToController();
//	
//public:
//	inline gtint GetActionType() {
//		return ACTION_DOWNDAMAGE;
//	}
//	inline void DetachActionToController() {
//		if( mpsMeshObject && mpsMeshObject->GetMesh()->getParent() )
//			GetActorLayer()->RemoveChild( mpsMeshObject );
//	};
//};

#endif
