#ifndef GNDATASTREAMFACTORY_H
#define GNDATASTREAMFACTORY_H

class GnMeshData;
class GnFactoryManager : public GnMemoryObject
{
protected:
	static GnFactoryManager* mpSingletone;

public:
	static GnMeshData* CreateMeshData();
	static GnTexture* CreateTexture();

protected:
	virtual GnMeshData* CreateMeshDataImp() = 0;
	virtual GnTexture* CreateTextureImp() = 0;
	
private:
};

#endif // GNDATASTREAMFACTORY_H