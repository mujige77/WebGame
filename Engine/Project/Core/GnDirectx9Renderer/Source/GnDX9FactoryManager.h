#ifndef GNDX9DATASTREAMFACTORY_H
#define GNDX9DATASTREAMFACTORY_H

#include "GnFactoryManager.h"

class GnMeshData;
class GnDX9FactoryManager : public GnFactoryManager
{
public:
	static GnFactoryManager* Create();
	static void Destory();

protected:	
	virtual GnMeshData* CreateMeshDataImp();
	virtual GnTexture* CreateTextureImp();
};

#endif // GNDX9DATASTREAMFACTORY_H