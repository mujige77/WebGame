#pragma once
#include "GcPropertyEntity.h"
class GnAnimationKeyManager;
class GcAnimationKeyPropEntity : public GcPropertyEntity
{
	GtDeclareEntity(GcAnimationKeyPropEntity);
public:
	enum eMessage
	{
		MSG_KEYTIME = 350,
		MSG_TEGID,
	};

	struct ThisEntityData : public EntityData
	{
		int mAniKeyIndex;
	};
private:
	Gt2DSequence* mpsSequence;
	GnAnimationKeyManager* mpAniKeyManager;
	int mAniKeyIndex;
	GnMemberSlot1<GcAnimationKeyPropEntity, GcPropertyGridProperty*> mUpdateEventSlot;
	

protected:
	GcPropertyGridProperty* mpKeyTime;
	GcPropertyGridProperty* mpTegID;	
	
public:
	GcAnimationKeyPropEntity(void);
	~GcAnimationKeyPropEntity(void);

	virtual bool Init();

	virtual bool ParseToEntity(EntityData* ppData);
	void UpdateEvent(GcPropertyGridProperty* pChangedGridProperty);	

	void SetCurrentTime(float val);

	inline GcPropertyGridProperty* GetKeyTimeProp() {
		return mpKeyTime;
	}
	inline GcPropertyGridProperty* GetTegIDProp() {
		return mpTegID;
	}
};

