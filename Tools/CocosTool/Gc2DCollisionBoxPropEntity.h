#pragma once
#include "GcPropertyEntity.h"
class Gc2DCollisionBoxPropEntity : public GcPropertyEntity
{
	GtDeclareEntity(Gc2DCollisionBoxPropEntity);
public:
	enum eMessage
	{
		MSG_ANCHORPOINTX = 300,
		MSG_ANCHORPOINTY,
		MSG_RECTPOSITIONX,
		MSG_RECTPOSITIONY,
		MSG_RECTWIDTH,
		MSG_RECTHEIGHT,
	};

	enum
	{
		PROP_ANCHORPOINTX,
		PROP_ANCHORPOINTY,		
		PROP_RECT_POSITIONX,
		PROP_RECT_POSITIONY,
		PROP_RECT_SIZEWIDTH,
		PROP_RECT_SIZEHEIGHT,
		MAX_USEPROP,
	};
	struct ThisEntityData : public EntityData
	{
		Gt2DSequence* mpSequenceObject;
		int mSelectRectIndex;
	};

private:
	Gt2DActor* mp2DActor;
	Gt2DSequence* mpSequenceObject;
	int mNumEditCollisionRect;
	GcPropertyGridProperty* mpProperty2;
	GcPropertyGridProperty* mpUseGridProperty[MAX_USEPROP];
	GnMemberSlot1<Gc2DCollisionBoxPropEntity, GcPropertyGridProperty*> mUpdateEventSlot;

public:
	Gc2DCollisionBoxPropEntity(void);
	~Gc2DCollisionBoxPropEntity(void);

	virtual bool Init();

	inline GcPropertyGridProperty* GetProperty2() {
		return mpProperty2;
	}
	inline GcPropertyGridProperty* GetAnchorPointXProp() {
		return mpUseGridProperty[PROP_ANCHORPOINTX];
	}
	inline GcPropertyGridProperty* GetAnchorPointYProp() {
		return mpUseGridProperty[PROP_ANCHORPOINTY];
	}
	inline GcPropertyGridProperty* GetCollisionPostionXProp() {
		return mpUseGridProperty[PROP_RECT_POSITIONX];
	}
	inline GcPropertyGridProperty* GetCollisionPostionYProp() {
		return mpUseGridProperty[PROP_RECT_POSITIONY];
	}
	inline GcPropertyGridProperty* GetCollisionSizeWidthProp() {
		return mpUseGridProperty[PROP_RECT_SIZEWIDTH];
	}
	inline GcPropertyGridProperty* GetCollisionSizeHeightProp() {
		return mpUseGridProperty[PROP_RECT_SIZEHEIGHT];
	}

	virtual bool ParseToEntity(EntityData* pObject);

	void ParseCollisionRect( gtuint i, Gn2DAVData::CollisionRect &rect );
	virtual void ApplyObjectData(CMFCPropertyGridProperty* pChangeProp, EntityData* pCurrentObject);

protected:
	Gn2DAVData* Get2DAVData();
	void UpdateEvent(GcPropertyGridProperty* pChangedGridProperty);
	CString GetCollisionListName(int iIndex, const TCHAR* pcName);
};

