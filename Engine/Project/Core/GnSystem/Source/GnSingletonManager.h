#ifndef __Core__GnSingletoneManager__
#define __Core__GnSingletoneManager__
#include "GnMemoryManager.h"
#include "GnMemoryObject.h"

class GNSYSTEM_ENTRY GnSingletonManager 
{
private:
	template<class T>
	class GnCreateFuncArray : public GnTArray<GnTExternalNewInterface<T>, T>
	{
	public:
		GnCreateFuncArray(gtuint uiSize =  0, gushort usGrowBy = 5)
        : GnTArray<GnTExternalNewInterface<T>, T>(uiSize, usGrowBy)
		{}
	};
public:
	typedef GnMemoryObject* (*CreateSingletonFunc)();
	
public:
	template<class T>
	class CreateObject : public GnMemoryObject
	{
	public:
		static T* Create() {
			if( GnMemoryManager::IsInitialized() == false )
			{
				GnSingletonManager::AddSingletonCreateFunc( T::Create );
				return NULL;
			}
			T* object = (T*)T::Create();
			GnSingletonManager::AddSingletonObject( object );
			return object;
		}
	};
	
private:
	static GnTPrimitiveArray<GnMemoryObject*> mSingletonObjects;
	static GnCreateFuncArray<CreateSingletonFunc>* mCreateFuncs;
	
public:
	static void EBMStartup();
	static void EBMShutdown();

	
private:
	static void AddSingletonObject(GnMemoryObject* pObject);
	static void AddSingletonCreateFunc(CreateSingletonFunc pFunc);
};

#define CreateSingletonObjects(className) \
	GnSingletonManager::CreateObject<className>::Create()

#define GnDeclareSingleton(className) \
private: \
	static className* mpSingleton; \
public: \
	static className* GetSingleton(); \
	static GnMemoryObject* Create()

#define GnImplementSingleton(className) \
className* className::mpSingleton = CreateSingletonObjects(className); \
className* className::GetSingleton() \
{ \
	return mpSingleton; \
} \
GnMemoryObject* className::Create() \
{ \
	mpSingleton = GnNew className(); \
	return mpSingleton; \
}

#endif
