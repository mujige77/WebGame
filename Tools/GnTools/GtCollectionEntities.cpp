#include "StdAfx.h"
#include "GtCollectionEntities.h"


GtCollectionEntities::GtCollectionEntities(GtPropertyGridCtrl* pPropertyCtrl /*= NULL*/) :
	mpRootPropertyCtrl(pPropertyCtrl)
{

}

GtCollectionEntities::~GtCollectionEntities(void)
{
	NullPropertyAll();
	mEntities.RemoveAll();
}

void GtCollectionEntities::NullPropertyAll()
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

bool GtCollectionEntities::ParseToObjectFromPropertyEntity()
{
	bool ret = true;
	EntitiesIter iter;
	mEntities.GetFirstIter(iter);
	while( iter.Valid() )
	{
		Entry& ent = iter.Item();
		ent.m_data->ParseToObject( mpsObject );
		mEntities.GetNextIter(iter);
	}

	return ret;
}

void GtCollectionEntities::DetachEntity(GtPropertyEntity* pEntity)
{
	GnAssert(pEntity);
	DeleteProperty( pEntity );
	mEntities.Remove(pEntity->GetClassName());
}
void GtCollectionEntities::AttachEntity(GtPropertyEntity* pEntity)
{
	GnAssert(pEntity);
	if( mpRootPropertyCtrl )
	{
		mpRootPropertyCtrl->AddProperty(pEntity->GetProperty());
	}
	mEntities.Insert(pEntity->GetClassName(), pEntity);
}

void GtCollectionEntities::AttachEntity(GtPropertyEntity* pEntity, CString name)
{
	GnAssert(pEntity);
	if( mpRootPropertyCtrl )
	{
		mpRootPropertyCtrl->AddProperty(pEntity->GetProperty());
	}
	mEntities.Insert(name, pEntity);
}

void GtCollectionEntities::DetachEntity(GtPropertyEntity* pEntity, CString name)
{
	GnAssert(pEntity);
	DeleteProperty(pEntity);
	mEntities.Remove(name);
}

void GtCollectionEntities::DetachAllEntity()
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

void GtCollectionEntities::RemoveAllPropertyFromCtrl()
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

GtPropertyEntity* GtCollectionEntities::GetEntity(CMFCPropertyGridProperty* pProp)
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

CMFCPropertyGridProperty* GtCollectionEntities::FindProp(CMFCPropertyGridProperty* pRootProp
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

void GtCollectionEntities::GetEntities(GnTPrimitiveArray<GtPropertyEntity*>& entits)
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