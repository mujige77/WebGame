#pragma once
#include "GnSMTextureAniCtrl.h"
#include "GnTextureProperty.h"

template<class newObject>
class GnObjectNew : public GnMemoryObject
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

	static void Delete(newObject* pObject)
	{
		GnDelete pObject;
	}
};
