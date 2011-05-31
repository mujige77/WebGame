#include "StdAfx.h"
#include "GcCollectionEntities.h"


GcCollectionEntities::GcCollectionEntities(GcPropertyGridCtrl* pPropertyCtrl /*= NULL*/) :
	mpRootPropertyCtrl(pPropertyCtrl)
{

}

GcCollectionEntities::~GcCollectionEntities(void)
{
	NullPropertyAll();
	mEntities.RemoveAll();
}

void GcCollectionEntities::NullPropertyAll()
{
	EntitiesIter iter;
	mEntities.GetFirstIter(iter);
	while( iter.Valid() )
	{
		Entry& ent = iter.Item();
		ent.m_data->SetNullProperty();
		mEntities.GetNextIter(iter);
	}
}

//bool GcCollectionEntities::ParseToObjectFromPropertyEntity()
//{
//	bool ret = true;
//	EntitiesIter iter;
//	mEntities.GetFirstIter(iter);
//	while( iter.Valid() )
//	{
//		Entry& ent = iter.Item();
//		ent.m_data->ParseToObject( mpsObject );
//		mEntities.GetNextIter(iter);
//	}
//
//	return ret;
//}

void GcCollectionEntities::DetachEntity(GcPropertyEntity* pEntity)
{
	GnAssert(pEntity);
	DeleteProperty( pEntity );
	mEntities.Remove(pEntity->GetClassName());
}
void GcCollectionEntities::AttachEntity(GcPropertyEntity* pEntity)
{
	GnAssert(pEntity);
	if( mpRootPropertyCtrl )
	{
		mpRootPropertyCtrl->AddProperty(pEntity->GetProperty());
	}
	mEntities.Insert(pEntity->GetClassName(), pEntity);
}

void GcCollectionEntities::AttachEntity(GcPropertyEntity* pEntity, CString name)
{
	GnAssert(pEntity);
	if( mpRootPropertyCtrl )
	{
		mpRootPropertyCtrl->AddProperty(pEntity->GetProperty());
	}
	mEntities.Insert(name, pEntity);
}

void GcCollectionEntities::DetachEntity(GcPropertyEntity* pEntity, CString name)
{
	GnAssert(pEntity);
	DeleteProperty(pEntity);
	mEntities.Remove(name);
}

void GcCollectionEntities::DetachAllEntity()
{
	EntitiesIter iter;
	mEntities.GetFirstIter(iter);
	mpRootPropertyCtrl->SetCurSel( NULL, false );
	while( iter.Valid() )
	{
		Entry& ent = iter.Item();
		DeleteProperty( ent.m_data );
		mEntities.GetNextIter(iter);
	}
	mEntities.RemoveAll();
}

void GcCollectionEntities::RemoveAllPropertyFromCtrl()
{
	EntitiesIter iter;
	mEntities.GetFirstIter(iter);
	mpRootPropertyCtrl->SetCurSel( NULL, false );
	while( iter.Valid() )
	{
		Entry& ent = iter.Item();
		if( mpRootPropertyCtrl )
		{
			mpRootPropertyCtrl->RemoveProperty(ent.m_data->GetProperty());
		}
		mEntities.GetNextIter(iter);
	}
	
}

GcPropertyEntity* GcCollectionEntities::GetEntity(CMFCPropertyGridProperty* pProp)
{
	EntitiesIter iter;
	mEntities.GetFirstIter(iter);
	mpRootPropertyCtrl->SetCurSel( NULL, false );
	while( iter.Valid() )
	{
		Entry& ent = iter.Item();
		CMFCPropertyGridProperty* prop = FindProp( ent.m_data->GetProperty(), pProp );
		if( prop )
			return ent.m_data;

		mEntities.GetNextIter(iter);
	}
	return NULL;
}

CMFCPropertyGridProperty* GcCollectionEntities::FindProp(CMFCPropertyGridProperty* pRootProp
	, CMFCPropertyGridProperty* pFindProp)
{
	if( pRootProp == pFindProp )
		return pRootProp;

	for( int i  = 0 ; i < pRootProp->GetSubItemsCount() ; i++  )
	{
		CMFCPropertyGridProperty* sub = pRootProp->GetSubItem( i );
		FindProp( sub, pFindProp );
	}

	return NULL;
}

void GcCollectionEntities::GetEntities(GnTPrimitiveArray<GcPropertyEntity*>& entits)
{
	EntitiesIter iter;
	mEntities.GetFirstIter(iter);
	while( iter.Valid() )
	{
		Entry& ent = iter.Item();
		entits.Add( ent.m_data );
		mEntities.GetNextIter(iter);
	}
}