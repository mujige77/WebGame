#pragma once
#include "GtPropertyEntity.h"
#include "GtPropertyGridCtrl.h"

class GtCollectionEntities
{
protected:
	typedef GnTCStringMap<GtPropertyEntityPtr>::Iterator EntitiesIter;
	typedef GnTCStringMap<GtPropertyEntityPtr>::Entry Entry;

	GnTCStringMap<GtPropertyEntityPtr> mEntities;
	GtPropertyGridCtrl* mpRootPropertyCtrl;
	GtObjectPtr mpsObject;
	
public:
	GtCollectionEntities(GtPropertyGridCtrl* pPropertyCtrl = NULL);
	~GtCollectionEntities(void);

	bool ParseToObjectFromPropertyEntity();

	void AttachEntity(GtPropertyEntity* pEntity);
	void DetachEntity(GtPropertyEntity* pEntity);
	void AttachEntity(GtPropertyEntity* pEntity, CString name);
	void DetachEntity(GtPropertyEntity* pEntity, CString name);

	void DetachAllEntity();
	void RemoveAllPropertyFromCtrl();

	GtPropertyEntity* GetEntity(CMFCPropertyGridProperty* pProp);

	void GetEntities(GnTPrimitiveArray<GtPropertyEntity*>& entits);

	inline GtObjectPtr GetObject() {
		return mpsObject;
	}
	inline void SetObject(GtObjectPtr val) {
		mpsObject = val;
	}
	inline int GetEntityCount() {
		return mEntities.Count();
	}
	inline void AddProperty(GtPropertyEntity* pEntity)
	{
		GnAssert(pEntity);
		if( mpRootPropertyCtrl )
			mpRootPropertyCtrl->AddProperty( pEntity->GetProperty() );
	}

	inline void RemovePropertyFromCtrl(GtPropertyEntity* pEntity, const gtchar* pcName = NULL)
	{
		GnAssert(pEntity);
		if( mpRootPropertyCtrl )
			mpRootPropertyCtrl->RemoveProperty( pEntity->GetProperty() );
		if( pcName )
			mEntities.Remove( pcName );
	}

	inline void RemoveAllEntity() {
		NullPropertyAll();
		mEntities.RemoveAll();
	}

	inline GtPropertyEntity* GetEntity(CString name)
	{
		GtPropertyEntityPtr entity;
		mEntities.GetAt( name, entity );
		return entity;
	}

	void NullPropertyAll();

protected:
	CMFCPropertyGridProperty* FindProp(CMFCPropertyGridProperty* pRootProp
		, CMFCPropertyGridProperty* pFindProp);

	inline void DeleteProperty(GtPropertyEntity* pEntity)
	{
		GnAssert(pEntity);
		if( mpRootPropertyCtrl )
		{
			mpRootPropertyCtrl->DeleteProperty(pEntity->GetProperty());
			pEntity->SetNullProperty();
		}
	}
};
	
#define GetEntityFromClassNameDef(entities, className) \
	(className*)entities->GetEntity(className::StaticClassName())

#define GetEntityFromNameDef(entities, str, className) \
	(className*)entities->GetEntity(str)