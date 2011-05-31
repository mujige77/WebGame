#pragma once
#include "GcPropertyEntity.h"
#include "GcPropertyGridCtrl.h"

class GcCollectionEntities
{
protected:
	typedef GtTCStringMap<GcPropertyEntityPtr>::Iterator EntitiesIter;
	typedef GtTCStringMap<GcPropertyEntityPtr>::Entry Entry;

	GtTCStringMap<GcPropertyEntityPtr> mEntities;
	GcPropertyGridCtrl* mpRootPropertyCtrl;
	GtObject* mpsObject;
	
public:
	GcCollectionEntities(GcPropertyGridCtrl* pPropertyCtrl = NULL);
	~GcCollectionEntities(void);

//	bool ParseToObjectFromPropertyEntity();

	void AttachEntity(GcPropertyEntity* pEntity);
	void DetachEntity(GcPropertyEntity* pEntity);
	void AttachEntity(GcPropertyEntity* pEntity, CString name);
	void DetachEntity(GcPropertyEntity* pEntity, CString name);

	void DetachAllEntity();
	void RemoveAllPropertyFromCtrl();

	GcPropertyEntity* GetEntity(CMFCPropertyGridProperty* pProp);

	void GetEntities(GnTPrimitiveArray<GcPropertyEntity*>& entits);

	inline GtObject* GetObject() {
		return mpsObject;
	}
	inline void SetObject(GtObject* val) {
		mpsObject = val;
	}
	inline int GetEntityCount() {
		return mEntities.Count();
	}
	inline void AddProperty(GcPropertyEntity* pEntity)
	{
		GnAssert(pEntity);
		if( mpRootPropertyCtrl )
			mpRootPropertyCtrl->AddProperty( pEntity->GetProperty() );
	}

	inline void RemovePropertyFromCtrl(GcPropertyEntity* pEntity, const gtchar* pcName = NULL)
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

	inline GcPropertyEntity* GetEntity(CString name)
	{
		GcPropertyEntityPtr entity;
		mEntities.GetAt( name, entity );
		return entity;
	}

	void NullPropertyAll();

protected:
	CMFCPropertyGridProperty* FindProp(CMFCPropertyGridProperty* pRootProp
		, CMFCPropertyGridProperty* pFindProp);

	inline void DeleteProperty(GcPropertyEntity* pEntity)
	{
		GnAssert(pEntity);
		if( mpRootPropertyCtrl )
		{
			if( mpRootPropertyCtrl->GetSafeHwnd() )
				mpRootPropertyCtrl->DeleteProperty( pEntity->GetProperty() );
			pEntity->SetNullProperty();
		}
	}
};
	
#define GetEntityFromClassNameDef(entities, className) \
	(className*)entities->GetEntity(className::StaticClassName())

#define GetEntityFromNameDef(entities, str, className) \
	(className*)entities->GetEntity(str)