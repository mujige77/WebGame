#pragma once
#include "GcPropertyEntity.h"
#include "GcPropertyGridProperty.h"

class Gc2DTexturePropEntity : public GcPropertyEntity
{
	GtDeclareEntity(Gc2DTexturePropEntity);
	enum
	{
		PROP_NUMBER,
		PROP_TEXTUREFILENAME,
		PROP_STARTTIME,
		PROP_ENDTIME,
	};

	enum eMessage
	{
		MSG_TEXTUREPATH = 150,
		MSG_STARTTIME,
		MSG_ENDTIME,
	};

	struct ThisEntity : public EntityData
	{
		gtuint mAniInfoIndex;
		long mTextureAniIndex;
		Gn2DTextureAni::TextureAniInfo* mpAniInfo;
	};

protected:
	Gt2DActor* mpActor;
	guint32 mTextureAniIndex;
	GnMemberSlot1<Gc2DTexturePropEntity, GcPropertyGridProperty*> mUpdateEventSlot;

public:
	Gc2DTexturePropEntity(void);
	virtual  ~Gc2DTexturePropEntity(void);

	void SetIndex(int iIndex);
	void SetTextureFilePath(CString strPath);
	void SetStartTime(float fTime);
	void SetEndTime(float fTime);
	int GetIndex();
	CString GetTextureFilePath();
	CString GetTextureFileName();
	float GetStartTime();	
	float GetEndTime();

	virtual bool Init();

	virtual void SetClearValues();
	virtual void UpdateEvent(GcPropertyGridProperty* pChangeProp);
	virtual bool ParseToEntity(EntityData* pEntityData);

	inline guint32 GetTextureAniIndex() {
		return mTextureAniIndex;
	}
	inline void SetTextureAniIndex(guint32 val) {
		mTextureAniIndex = val;
	}
	inline GcPropertyGridProperty*  GetTextureNumberProperty() {
		return (GcPropertyGridProperty*)mpProperty->GetSubItem( PROP_NUMBER );
	}
	inline GcPropertyGridProperty*  GetTextureGridFileProperty() {
		return (GcPropertyGridProperty*)mpProperty->GetSubItem( PROP_TEXTUREFILENAME );
	}
	inline GcPropertyGridProperty*  GetStartTimeProperty() {
		return (GcPropertyGridProperty*)mpProperty->GetSubItem( PROP_STARTTIME );
	}
	inline GcPropertyGridProperty*  GetEndTimeProperty() {
		return (GcPropertyGridProperty*)mpProperty->GetSubItem( PROP_ENDTIME );
	}
};

