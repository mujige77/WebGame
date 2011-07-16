#ifndef __Core__GnICoolTime__
#define __Core__GnICoolTime__

#include "GnInterface.h"

class GnICoolTime : public GnInterface
{
private:
	Gn2DMeshObjectPtr mpsBlindMesh;
	Gn2DMeshObjectPtr mpsCoolTimeMesh;
	float mCoolTime;
	float mAcumtime;
	
public:
	static GnICoolTime* Create(float fWidth, float fHeight);
	
public:
	void Update(float fDeltaTime);
	
public:
	virtual void SetPosition(GnVector2& cPos);
	
protected:
	GnICoolTime(Gn2DMeshObject* pBlindMesh, Gn2DMeshObject* pCoolTimeMesh);
	
public:
	inline void SetVisibleBlind(bool bVal) {
		mpsBlindMesh->SetVisible( bVal );
	}
	inline void SetBlindColor(GnColor cColor) {
		mpsBlindMesh->SetColor( cColor );
	}
	inline void SetBlindAlpha(float val) {
		mpsBlindMesh->SetAlpha( val );
	}
	inline void SetVisibleCoolTime(bool bVal) {
		mpsBlindMesh->SetVisible( bVal );
	}
	inline void SetCoolTime(float fTime) {
		mCoolTime = fTime;
	}
	inline void SetCoolTimeColor(GnColor cColor) {
		mpsBlindMesh->SetColor( cColor );
	}
	inline void SetCoolTimeAlpha(float val) {
		mpsBlindMesh->SetAlpha( val );
	}
};

#endif
