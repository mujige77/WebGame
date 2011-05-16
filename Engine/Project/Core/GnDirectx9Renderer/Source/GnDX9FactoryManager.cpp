#include "GnDirectx9RendererPCH.h"
#include "GnDX9FactoryManager.h"
#include "GnDX9MeshData.h"
#include "GnDX9Texture.h"

GnFactoryManager* GnDX9FactoryManager::Create()
{
	mpSingletone = GnNew GnDX9FactoryManager();
	return mpSingletone;
}

void GnDX9FactoryManager::Destory()
{
	if( mpSingletone )
		GnDelete mpSingletone;
}

GnMeshData* GnDX9FactoryManager::CreateMeshDataImp()
{
	return GnNew GnDX9MeshData();
}

GnTexture* GnDX9FactoryManager::CreateTextureImp()
{
	return GnNew GnDX9Texture();
}