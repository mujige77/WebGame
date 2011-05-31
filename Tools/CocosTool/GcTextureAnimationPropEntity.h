#pragma once
#include "GcPropertyEntity.h"

class Gn2DTextureAni;
class GcTextureAnimationPropEntity : public GcPropertyEntity
{
	GtDeclareEntity(GcTextureAnimationPropEntity);
public:
	enum eMessage
	{
		MSG_ANIINDEX = 100,
		MSG_FILENAME,
		MSG_STARTTIME,	
		MSG_ENDTIME,
	};

	enum
	{
		PROP_ANIINDEX,
		//PROP_FILENAME,
		PROP_STARTTIME,
		PROP_ENDTIME,
	};

	struct EntityDataTextureAni : public GcPropertyEntity::EntityData
	{
		long mIndex;
		Gn2DTextureAni* mpAni;
	};

protected:
	Gt2DActor* mpActor;
	Gn2DTextureAni* mpAni;
	GnMemberSlot1<GcTextureAnimationPropEntity, GcPropertyGridProperty*> mUpdateEventSlot;

public:
	GcTextureAnimationPropEntity(void);
	virtual ~GcTextureAnimationPropEntity(void);

	virtual bool Init();

	//CString GetTargetName();
	//CString GetFileName();
	float GetStartTime();
	float GetEndTime();	

	inline CMFCPropertyGridProperty* GetAniIndexProperty() {
		return mpProperty->GetSubItem(PROP_ANIINDEX);
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

	void UpdateEvent(GcPropertyGridProperty* pChangedGridProperty);
	virtual bool ParseToEntity(EntityData* pObject);
	virtual bool ParseToObject(EntityData* pObject);
	virtual void ApplyObjectData(CMFCPropertyGridProperty* pChangeProp, EntityData* pCurrentObject);
};

