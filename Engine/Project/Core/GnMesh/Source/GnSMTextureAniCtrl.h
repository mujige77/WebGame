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

public:
	GnSMTextureAniCtrl(gtuint uiNumAni = 0);
	virtual ~GnSMTextureAniCtrl();
	
	virtual void Update(float fTime);
	virtual void SetAniInfo(gtuint uiIndex, GnTextureProperty* pTexture, float fStartTime, float fEndTime);
	TextureAni* GetAniInfo(gtuint uiIndex ){
		return &mAnis.GetAt( uiIndex );
	}
	inline gtuint GetAniInfoCount() {
		return mAnis.GetSize();
	}
	virtual bool ReCreate(gtuint uiNumAni, bool bSaveAniData);	

	virtual void Start(float fTime);
	virtual void Stop();
};

#endif // GNSMTEXTUREANICTRL_H