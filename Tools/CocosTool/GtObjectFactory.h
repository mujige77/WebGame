#pragma once
#include "GtObject.h"
#include <map>

class GtObjectFactory
{
	typedef std::map<gtstring, GtObjectPtr>::iterator IterObjectMap;

private:
	static GtObjectFactory* mpSingleton;
	std::map<gtstring, GtObjectPtr> mObjects;

public:
	GtObjectFactory(void);
	~GtObjectFactory(void);

	static void EBMStartup();
	static void EBMShutdown();

	static GtObjectFactory* GetSingleton();
	
	GtObject* CreateObject(gint iObjectType, const gtchar* pcName);
	GtObject* GetObject(const gtchar* pcName);	
	void AddObject(GtObject* pObject);
	void RemoveObject(const gtchar* pcName);
	void RemvoeAllObject();	
	void RemvoeAndDeleteAllObject();
	void SaveObjects(bool bRemoveAll);	
};

#define GetObjectFactory GtObjectFactory::GetSingleton