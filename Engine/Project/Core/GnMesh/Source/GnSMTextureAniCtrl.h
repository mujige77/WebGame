#ifndef GNSMTEXTUREANICTRL_H
#define GNSMTEXTUREANICTRL_H
#include "GnObjectStream.h"

class GnTextureProperty;
class GNMESH_ENTRY GnSMTextureAniCtrl : public GnTimeController
{
	GnDeclareRTTI;
	GnDeclareStream;
public:
	class TextureAni : public GnMemoryObject
	{
		//GnDeclareDataStream;
	public:
		float mStartTime;
		float mEndTime;
		GnTexturePropertyPtr mpsPrperty;
	};	

protected:
	GnTObjectArray<TextureAni> mAnis;
	gtuint mCurrentAniIndex;
	TextureAni* mpCurrentAni;
	GnIRect mImageRect;

public:
	GnSMTextureAniCtrl(gtuint uiNumAni = 0);
	virtual ~GnSMTextureAniCtrl();
	
	virtual bool SetTargetObject(GnObjectForm* pObject);

	virtual void Update(float fTime);
	virtual void SetAniInfo(gtuint uiIndex, GnTextureProperty* pTexture, float fStartTime, float fEndTime);	
	virtual bool ReCreate(gtuint uiNumAni, bool bSaveAniData);	

	virtual void Playing(float fTime);
	virtual void Stop();

	inline TextureAni* GetAniInfo(gtuint uiIndex){
		return &mAnis.GetAt( uiIndex );
	}
	inline gtuint GetAniInfoCount() {
		return mAnis.GetSize();
	}
};

#endif // GNSMTEXTUREANICTRL_H