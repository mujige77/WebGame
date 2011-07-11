#include "StdAfx.h"
#include "GtObjectFactory.h"
#include "Gt2DActor.h"
#include "Gt2DObject.h"

GtObjectFactory* GtObjectFactory::mpSingleton = NULL;

GtObjectFactory::GtObjectFactory(void)
{
}


GtObjectFactory::~GtObjectFactory(void)
{
	IterObjectMap iter = mObjects.begin();
	while( iter != mObjects.end() )
	{
		iter->second = NULL;
		++iter;
	}
}

GtObjectFactory* GtObjectFactory::GetSingleton()
{
	return mpSingleton;
}

void GtObjectFactory::EBMStartup()
{
	mpSingleton = new GtObjectFactory;
}

void GtObjectFactory::EBMShutdown()
{
	if( mpSingleton )
		delete mpSingleton;
}

GtObject* GtObjectFactory::CreateObject(gint iObjectType, const gtchar* pcName)
{
	GtObject* object = GetObject( pcName );
	if( object )
		return object;

	switch(iObjectType)
	{
	case Gt2DActor::OBJECT_TYPE:
		object = GtObjectNew<Gt2DActor>::Create();
		break;
	case Gt2DObject::OBJECT_TYPE:
		object = GtObjectNew<Gt2DObject>::Create();
		break;
	default:
		return NULL;
	}

	mObjects[pcName] = object;
	return object;
}

GtObject* GtObjectFactory::GetObject(const gtchar* pcName)
{
	IterObjectMap iter = mObjects.find( pcName );
	if( iter == mObjects.end() )		
		return NULL;

	return iter->second;
}

void GtObjectFactory::SaveObjects(bool bRemoveAll)
{
	if( GtToolSettings::GetScalePercent() != 100 )
		return;
	IterObjectMap iter = mObjects.begin();
	while( iter != mObjects.end() )
	{
		GnVerify( iter->second->SaveData() );
		++iter;
	}
	if( bRemoveAll )
		RemvoeAllObject();
}

void GtObjectFactory::AddObject(GtObject* pObject)
{
	GtConvertString objName = pObject->GetObjectName();

	GnAssert( objName.length() );
	GnAssert( GetObject( objName.c_str() ) == false );	
	if( GetObject( objName.c_str() ) )
		return;

	mObjects[objName.c_str()] = pObject;
}

void GtObjectFactory::RemoveObject(const gtchar* pcName)
{
	IterObjectMap iter = mObjects.find( pcName );
	if( iter == mObjects.end() )		
		return;

	mObjects.erase( iter );
}

void GtObjectFactory::RemvoeAllObject()
{
	mObjects.clear();
}

void GtObjectFactory::RemvoeAndDeleteAllObject()
{
	IterObjectMap iter = mObjects.begin();
	while( iter != mObjects.end() )
	{
		GnDelete iter->second;
		++iter;
	}
	RemvoeAllObject();
}