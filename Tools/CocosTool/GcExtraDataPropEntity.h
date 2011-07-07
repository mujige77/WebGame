#pragma once
#include "GcPropertyEntity.h"

class GcExtraDataPropEntity : public GcPropertyEntity
{
	GtDeclareEntity(GcExtraDataPropEntity);
public:
	enum eMessage
	{
		MSG_EXTRA_ID = 450,
		MSG_EXTRA_POSITIONX,
		MSG_EXTRA_POSITIONY,
		MSG_EXTRA_INT,
	};

	enum
	{
		PROP_EXTRA_ID,
		PROP_EXTRA_POSITIONX,
		PROP_EXTRA_POSITIONY,
		PROP_EXTRA_INT,
		MAX_USEPROP
	};

	struct ThisEntityData : public EntityData
	{
		Gn2DMeshObject* mpMeshObject;
		int mSelectRectIndex;
	};

private:
	GtObject* mpObject;
	Gn2DMeshObject* mpMeshObject;
	GnExtraData* mCurrentModifyExtraData;
	gint mNumEditExtraData;
	GcPropertyGridProperty* mpUseGridProperty[MAX_USEPROP];
	GcPropertyGridProperty* mpPropExtraPositionGroup;
	GcPropertyGridProperty* mpPropExtraIntGroup;
	GnMemberSlot1<GcExtraDataPropEntity, GcPropertyGridProperty*> mUpdateEventSlot;

public:
	GcExtraDataPropEntity(void);
	~GcExtraDataPropEntity(void);

	virtual bool Init();
	virtual bool ParseToEntity(EntityData* pData);
	inline GcPropertyGridProperty* GetExtraIDProp() {
		return mpUseGridProperty[PROP_EXTRA_ID];
	}
	inline GcPropertyGridProperty* GetExtraPointXProp() {
		return mpUseGridProperty[PROP_EXTRA_POSITIONX];
	}
	inline GcPropertyGridProperty* GetExtraPointYProp() {
		return mpUseGridProperty[PROP_EXTRA_POSITIONY];
	}
	inline GcPropertyGridProperty* GetExtraIntProp() {
		return mpUseGridProperty[PROP_EXTRA_INT];
	}
protected:	
	void UpdateEvent(GcPropertyGridProperty* pChangedGridProperty);
	void ParsePostion(GnExtraData* pExtra);
	void ParseInt(GnExtraData* pExtra);
};