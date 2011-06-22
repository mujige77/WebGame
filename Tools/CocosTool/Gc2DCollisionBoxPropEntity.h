#pragma once
#include "GcPropertyEntity.h"
class Gc2DCollisionBoxPropEntity : public GcPropertyEntity
{
	GtDeclareEntity(Gc2DCollisionBoxPropEntity);
public:
	enum eMessage
	{
		MSG_RECTPOSITIONX,
		MSG_RECTPOSITIONY,
		MSG_RECTWIDTH,
		MSG_RECTHEIGHT,
	};

	enum
	{
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
	GcPropertyGridProperty* mpUseGridProperty[MAX_USEPROP];
	GnMemberSlot1<Gc2DCollisionBoxPropEntity, GcPropertyGridProperty*> mUpdateEventSlot;

public:
	Gc2DCollisionBoxPropEntity(void);
	~Gc2DCollisionBoxPropEntity(void);

	virtual bool Init();
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

	virtual bool ParseToEntity(EntityData* pData);
	void ParseCollisionRect( gtuint i, Gn2DAVData::CollisionRect &rect );

protected:
	Gn2DAVData* Get2DAVData();
	void UpdateEvent(GcPropertyGridProperty* pChangedGridProperty);
	CString GetCollisionListName(int iIndex, const TCHAR* pcName);
};

