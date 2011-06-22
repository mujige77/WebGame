#pragma once
#include "GcPropertyEntity.h"

class Gc2DAnchorPropEntity : public GcPropertyEntity
{
	GtDeclareEntity(Gc2DAnchorPropEntity	);
public:
	enum eMessage
	{
		MSG_ANCHORPOINTX = 400,
		MSG_ANCHORPOINTY,
		MSG_IMAGECENTERX,
		MSG_IMAGECENTERY,
	};

	enum
	{
		PROP_ANCHORPOINTX,
		PROP_ANCHORPOINTY,
		PROP_IMAGECENTERX,
		PROP_IMAGECENTERY,
		MAX_USEPROP
	};

	struct ThisEntityData : public EntityData
	{
		Gt2DSequence* mpSequenceObject;
	};

private:
	Gt2DActor* mp2DActor;
	Gt2DSequence* mpSequenceObject;
	GcPropertyGridProperty* mpUseGridProperty[MAX_USEPROP];
	GnMemberSlot1<Gc2DAnchorPropEntity, GcPropertyGridProperty*> mUpdateEventSlot;

public:
	Gc2DAnchorPropEntity(void);
	~Gc2DAnchorPropEntity(void);

	virtual bool Init();
	virtual bool ParseToEntity(EntityData* pData);
	inline GcPropertyGridProperty* GetAnchorPointXProp() {
		return mpUseGridProperty[PROP_ANCHORPOINTX];
	}
	inline GcPropertyGridProperty* GetAnchorPointYProp() {
		return mpUseGridProperty[PROP_ANCHORPOINTY];
	}
	inline GcPropertyGridProperty* GetImageCenterXProp() {
		return mpUseGridProperty[PROP_IMAGECENTERX];
	}
	inline GcPropertyGridProperty* GetImageCenterYProp() {
		return mpUseGridProperty[PROP_IMAGECENTERY];
	}
protected:	
	void UpdateEvent(GcPropertyGridProperty* pChangedGridProperty);
	Gn2DAVData* Get2DAVData();
};

