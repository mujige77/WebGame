#pragma once
#include "GtPropertyEntity.h"
#include "GtPropertyGridProperty.h"
#include "GtSMTextureAniCtrl.h"

class Gt2DTexturePropEntity : public GtPropertyEntity
{
	GtDeclareEntity(Gt2DTexturePropEntity);
	enum
	{
		//PROP_NUMBER,
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

protected:
	GtSMTextureAniCtrl::AniInfo* mpAniInfo;

public:
	Gt2DTexturePropEntity(void);
	virtual  ~Gt2DTexturePropEntity(void);

	virtual bool Init();

	virtual void SetClearValues();
	virtual bool ParseToEntity(GtStreamObject* pObject);	
	virtual bool ParseToObject(GtObject* pObject);
	virtual void ApplyObjectData(CMFCPropertyGridProperty* pChangeProp, GtObject* pCurrentObject);

	//GtPropertyGridProperty*  GetTextureNumberProperty() {
	//	return (GtPropertyGridProperty*)mpProperty->GetSubItem( PROP_NUMBER );
	//}
	GtPropertyGridProperty*  GetTextureGridFileProperty() {
		return (GtPropertyGridProperty*)mpProperty->GetSubItem( PROP_TEXTUREFILENAME );
	}
	GtPropertyGridProperty*  GetStartTimeProperty() {
		return (GtPropertyGridProperty*)mpProperty->GetSubItem( PROP_STARTTIME );
	}
	GtPropertyGridProperty*  GetEndTimeProperty() {
		return (GtPropertyGridProperty*)mpProperty->GetSubItem( PROP_ENDTIME );
	}

	//void SetIndex(int iIndex);
	void SetTextureFilePath(CString strPath);
	void SetStartTime(float fTime);
	void SetEndTime(float fTime);
	//int GetIndex();
	CString GetTextureFilePath();
	CString GetTextureFileName();
	float GetStartTime();	
	float GetEndTime();
};

