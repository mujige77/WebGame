#pragma once
#include <string>
#include "GtConvertString.h"

class GnFrame;
class GtObjectManager : public GnMemoryObject
{
protected:
	typedef GtTStringMap<GtObjectPtr>::Iterator GtObjectIter;
	typedef GtTStringMap<GtObjectPtr>::Entry GtObjectEntry;

protected:
	static GtObjectManager* mspInstane;
	GtTStringMap<GtObjectPtr> mObjectList;

public:
	GtObjectManager(void);
	~GtObjectManager(void);

	static void EBMStartup();
	static void EBMShutdown();
	static GtObjectManager* GetSingletone();

	GtActorObject* CreateActorObject(const gchar* strNodeName, const gtchar* strName);
	GtObject* ChangeObjectName(const gtchar* strBeforeName, const gtchar* strAfterName);

	inline GtObject* GetObject(const gtchar* strName) {
		GtObjectPtr object;
		mObjectList.GetAt( strName, object );
		return object;
	}
};

#define  GetObjectManager GtObjectManager::GetSingletone