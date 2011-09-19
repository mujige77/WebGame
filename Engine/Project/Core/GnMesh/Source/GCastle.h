//
//  GCastle.h
//  Core
//
//  Created by Max Yoon on 11. 7. 19..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//

#ifndef __Core__GCastle__
#define __Core__GCastle__

#include "GStageInfo.h"

class GnIProgressBar;
class GCastle : public GnSmartObject
{
public:
	enum eCastelState
	{
		eNormal,
		eBreak,
		eDestroy,
	};
	
private:
	eCastelState mCastleStateFlag;
	gint32 mHP;
	gint32 mCurrentHP;
	GnInterface* mpGageIcon;
	GnIProgressBar* mpCastleGage;
	Gn2DMeshObjectPtr mpsCastleNormal;
	Gn2DMeshObjectPtr mpsCastleBreak;
	Gn2DMeshObjectPtr mpsCastleDestroy;
	Gn2DMeshObjectPtr mpsCastleBottom;
	Gn2DMeshObjectPtr mpsDamageEffectNormal;
	Gn2DMeshObjectPtr mpsDamageEffectBreak;
	Gn2DMeshObjectPtr mpsDamageEffectBottom;
	Gn2DMeshObjectPtr mpsDeckEffect;
	Gn2DMeshObject* mpTopCastle;
	Gn2DMeshObject* mpBottomCastle;
	Gn2DMeshObject* mpTopDamageEffect;
	Gn2DMeshObject* mpBottomDamageEffect;	
	GnFRect mTopBodyRect;
	GnFRect mBottomBodyRect;
	bool mIsDamage;
	float mDamageEffectTime;
	float mDamageEffectAcumTime;
	GnTimer mAutoRecoveryHPTimer;
	gint32 mAutoRecoveryHP;
	
public:
	void Update(float fTime);
	void UpdateDamageEffect(float fTime);
	void UpdateBreak(float fTime);
	void ReceveAttack(gint32 iDamage);
	
public:
	inline gint32 GetHP() {
		return mHP;
	}
	inline void SetHP(gint32 uiHP) {
		mHP = uiHP;
	}
	inline gint32 GetCurrentHP() {
		return mCurrentHP;
	}
	inline void SetCurrentHP(gint32 uiHP) {
		mCurrentHP = uiHP;
	}
	inline GnFRect& GetTopBodyRect() {
		return mTopBodyRect;
	}
	inline GnFRect& GetBottomBodyRect() {
		return mBottomBodyRect;
	}
	inline eCastelState GetCastelStateFlag() {
		return mCastleStateFlag;
	}
	
protected:
	GCastle();
	bool CreateCastleData(GLayer* pCastleLayer, GStageInfo* pStageInfo, GStageInfo::GCastleFiles* pFiles
		, GStageInfo::GCastlePositions* pPositions);
	void SetCurrentState();
	void SetStopDamageEffect();
	void UpdateHP(float fTime);
	
protected:
	inline void SetGageIcon(GnInterface* pGageIcon) {
		mpGageIcon = pGageIcon;
	};
	inline GnInterface* GetGageIcon() {
		return mpGageIcon;
	}
	inline void SetCastleGage(GnIProgressBar* pGege) {
		mpCastleGage = pGege;
	}
	inline GnIProgressBar* GetCastleGege() {
		return mpCastleGage;
	}
	inline gint32 GetAutoRecoveryHP() {
		return mAutoRecoveryHP;
	}
	inline void SetAutoRecoveryHP(gint32 uiHP) {
		mAutoRecoveryHP = uiHP;
	}
};

GnSmartPointer(GCastle);

#endif
