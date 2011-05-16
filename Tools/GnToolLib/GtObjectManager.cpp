#include "GnToolLibPCH.h"
#include "GtObjectManager.h"
#include "GnFrame.h"
#include "GtToolSettings.h"

GtObjectManager* GtObjectManager::mspInstane = NULL;

GtObjectManager::GtObjectManager(void)
{
}


GtObjectManager::~GtObjectManager(void)
{
	mObjectList.RemoveAll();
}

void GtObjectManager::EBMStartup()
{
	mspInstane = GnNew GtObjectManager;
}

void GtObjectManager::EBMShutdown()
{
	if( mspInstane )
		GnDelete mspInstane;
}

GtObjectManager* GtObjectManager::GetSingletone()
{
	return mspInstane;
}

GtActorObject* GtObjectManager::CreateActorObject(const gchar* strNodeName, const gtchar* strName)
{
	GtConvertString objectName;
	objectName = strName;

	GtActorObject* pObject = GnNew GtActorObject();	
	pObject->SetObjectName(  objectName.GetAciiString() );

	mObjectList.SetAt( objectName, pObject );
	return pObject;
}

GtObject* GtObjectManager::ChangeObjectName(const gtchar* strBeforeName, const gtchar* strAfterName)
{
	GtObjectEntry* entry =  mObjectList.Find( strBeforeName );
	if( entry == NULL )
		return NULL;

	GtObjectPtr object = entry->m_data;
	mObjectList.Remove( strBeforeName );

	mObjectList.SetAt( strAfterName, object );
	return object;
}