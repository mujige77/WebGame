#pragma once
#include "GtPropertyEntity.h"

class GtSMTextureAniCtrl;

class GtTextureAnimationPropEntity : public GtPropertyEntity
{
public:
	enum eMessage
	{
		MSG_TARGETNAME = 100,
		MSG_FILENAME,
		MSG_STARTTIME,	
		MSG_ENDTIME,
	};

	enum
	{
		PROP_TARGETNAME,
		//PROP_FILENAME,
		PROP_STARTTIME,
		PROP_ENDTIME,
	};

	GtDeclareEntity(GtTextureAnimationPropEntity);

protected:
	GtSMTextureAniCtrl* mpCurrentAniCtrl;

public:
	GtTextureAnimationPropEntity(void);
	virtual ~GtTextureAnimationPropEntity(void);

	virtual bool Init();

	CString GetTargetName();
	//CString GetFileName();
	float GetStartTime();
	float GetEndTime();	

	inline CMFCPropertyGridProperty* GetTargetNameProperty() {
		return mpProperty->GetSubItem(PROP_TARGETNAME);
	}
	//inline CMFCPropertyGridProperty* GetFileNameProperty() {
	//	return mpProperty->GetSubItem(PROP_FILENAME);
	//}
	inline CMFCPropertyGridProperty* GetStartTimeProperty() {
		return mpProperty->GetSubItem(PROP_STARTTIME);
	}
	inline CMFCPropertyGridProperty* GetEndTimeProperty() {
		return mpProperty->GetSubItem(PROP_ENDTIME);
	}

	virtual bool ParseToEntity(GtStreamObject* pObject);
	virtual bool ParseToObject(GtObject* pObject);
	virtual void ApplyObjectData(CMFCPropertyGridProperty* pChangeProp, GtObject* pCurrentObject);
};

