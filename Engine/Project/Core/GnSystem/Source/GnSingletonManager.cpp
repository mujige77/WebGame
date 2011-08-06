#include "GnSystemPCH.h"
#include "GnSingletonManager.h"

GnTPrimitiveArray<GnMemoryObject*> GnSingletonManager::mSingletonObjects;
GnSingletonManager::GnCreateFuncArray<GnSingletonManager::CreateSingletonFunc>*
	GnSingletonManager::mCreateFuncs = NULL;
GnSingletonManager::GnCreateFuncArray<GnSingletonManager::DestroyFunc>*
GnSingletonManager::mDestroyFuncs;

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
		GnMemoryObject *pObject = mSingletonObjects.GetAt( i );
		mDestroyFuncs->GetAt( i )( pObject );
	}
	if( mCreateFuncs )
		delete mCreateFuncs;
	if( mDestroyFuncs )
		delete mDestroyFuncs;
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

void GnSingletonManager::AddSingletonDestroyFunc(DestroyFunc pFunc)
{
	
	if( mDestroyFuncs == NULL )
		mDestroyFuncs = new 
		GnSingletonManager::GnCreateFuncArray<GnSingletonManager::DestroyFunc>;
	mDestroyFuncs->Add( pFunc );
}