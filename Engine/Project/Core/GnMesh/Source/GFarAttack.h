//
//  GFarAttack.h
//  Core
//
//  Created by Max Yoon on 11. 8. 24..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef Core_GFarAttack_h
#define Core_GFarAttack_h
#include "GAttackMacro.h"
#include "GGameDefine.h"
#include "GAttackDamageInfo.h"

class GLayer;
class GFarAttack : public GnSmartObject
{
	GnDeclareFlags( guint32 );
	enum
	{
		MASK_DESTORY = 0x00000001,
		MASK_ENABLEATTACK = 0x00000002,
	};
public:
	enum eBasicStartPosition
	{
		eUserPosition,
		eExtraPosition,
	};
	
public:
	typedef GFarAttack* (*CreateAttackFunc)(guint32);
	
protected:
	static std::map<gtuint, CreateAttackFunc> mCreateFuncs;
	
public:
	static void RegCreateFunction(gtuint uiIndex, GFarAttack::CreateAttackFunc pFunc);
	static GFarAttack* CreateAttack(guint32 uiIndex);
	static GFarAttack* CreateAttackFromEffectIndex(guint32 uiIndex, guint32 uiEffectFileIndex);
	
private:
	Gn2DMeshObjectPtr mpsAttackMesh;
	GnFRect mOriginalAttackRect;
	GnFRect mAttackRect;
	float mStartAttackTime;
	float mAccumulateTime;
	guint32 mAttackCount;
	bool mStopAnimation;
	guint32 mAttackIndex;
	GAttackDamageInfo mAttackDamage;
protected:
	guint32 mCurrentAttackCount;
#ifdef GNDEBUG
private:
	GLayer* mpDebugLayer;
public:
	GLayer* GetDebugLayer() {
		return mpDebugLayer;
	}
	void SetDebugLayer(GLayer* pDebugLayer)	{
		mpDebugLayer = pDebugLayer;
	}
#endif // GNDEBUG

public:
	GFarAttack();
	bool CreateAttackMesh(gtuint uiIndex);
	void Reset();
	
public:
	virtual void Update(float fTime);
	virtual void SetPosition(GnVector2 cPos);
	virtual inline eBasicStartPosition GetBasicStartPosition() {
		return eExtraPosition;
	}
	virtual inline void SendedAttackTo() {
		++mCurrentAttackCount;
	}
	virtual inline void EndedAttackTo() {
		SetIsEnableAttack( false );
	}
	virtual inline bool EnableNextAttack() {
		return mCurrentAttackCount < mAttackCount;
	}
	virtual inline void SetFilpX(bool val) {
		mpsAttackMesh->SetFlipX( val );
	}
	virtual inline bool GetFilpX() {
		return mpsAttackMesh->GetFlipX();
	}
public:
	inline GnFRect& GetAttackRect() {
		return mAttackRect;
	}
	inline void SetAttackRect(GnFRect cRect) {
		mAttackRect = cRect;
	}
	inline Gn2DMeshObject* GetAttackMesh() {
		return mpsAttackMesh;
	}
	inline bool IsStopAnimation() {
		return mStopAnimation;
	}
	inline void SetAttackCount(guint32 val) {
		mAttackCount = val;
	}
	inline guint32 GetAttackCount() {
		return mAttackCount;
	}
	inline guint32 GetCurrentAttackCount() {
		return mCurrentAttackCount;
	}
	inline void SetStartAttackTime(float val) {
		mStartAttackTime = val;
	}
	inline bool IsReadyAttack() {
		return mAccumulateTime >= mStartAttackTime;
	}
	inline bool IsDestory() {
		return GetBit( MASK_DESTORY );
	};
	inline void SetIsDestory(bool val) {
		SetBit( val, MASK_DESTORY );
	};
	inline bool IsEnableAttack() {
		return GetBit( MASK_ENABLEATTACK );
	};
	inline void SetIsEnableAttack(bool val) {
		SetBit( val, MASK_ENABLEATTACK );
	};
	inline void SetAttackIndex(guint32 val) {
		mAttackIndex = val;
	}
	inline guint32 GetAttackIndex() {
		return mAttackIndex;
	}
	inline GAttackDamageInfo* GetAttackDamageInfo() {
		return &mAttackDamage;
	}
protected:
	inline GnFRect& GetOriginalAttackRect() {
		return mOriginalAttackRect;
	}
	inline void SetOriginalAttackRect(GnFRect cRect) {
		mOriginalAttackRect = cRect;
	}
};

GnSmartPointer(GFarAttack);
#endif
