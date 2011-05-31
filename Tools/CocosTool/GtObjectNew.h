#pragma once
#include "GnMemoryObject.h"

template<class newObject>
class GtObjectNew : public GnMemoryObject
{
public:
	template<class V1>
	static newObject* Create(V1 val1)
	{
		return GnNew newObject( val1 );
	}

	static newObject* Create()
	{
		return GnNew newObject();
	}

	static newObject* CreateArray(gtuint uiNum)
	{
		return GnNew newObject[uiNum];
	}

	static void Delete(newObject* pObject)
	{
		GnDelete pObject;
	}

	static void DeleteArray(newObject* pObject)
	{
		GnDelete[] pObject;
	}
};