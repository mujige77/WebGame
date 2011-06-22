#include "GnSystemPCH.h"
#include "GnSingletonManager.h"

GnTPrimitiveArray<GnMemoryObject*> GnSingletonManager::mSingletonObjects;
GnSingletonManager::GnCreateFuncArray<GnSingletonManager::CreateSingletonFunc>*
	GnSingletonManager::mCreateFuncs = NULL;

void GnSingletonManager::EBMStartup()
{
	if( mCreateFuncs )
	{
		for ( gtuint i = 0 ; i < mCreateFuncs->GetSize(); i++ )
		{
			GnMemoryObject *pObject = mCreateFuncs->GetAt( i )();
			AddSingletonObject( pObject );
		}
	}
}

void GnSingletonManager::EBMShutdown()
{
	for ( gtuint i = 0 ; i < mSingletonObjects.GetSize(); i++ )
	{
		GnDelete mSingletonObjects.GetAt( i );
	}
	if( mCreateFuncs )
		delete mCreateFuncs;
}

void GnSingletonManager::AddSingletonObject(GnMemoryObject* pObject)
{
	mSingletonObjects.Add( pObject );
}

void GnSingletonManager::AddSingletonCreateFunc(CreateSingletonFunc pFunc)
{
	
	if( mCreateFuncs == NULL )
		mCreateFuncs = new 
		GnSingletonManager::GnCreateFuncArray<GnSingletonManager::CreateSingletonFunc>;
	mCreateFuncs->Add( pFunc );
}