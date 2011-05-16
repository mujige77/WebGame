#include "GnMainPCH.h"
#include "GnFactoryManager.h"

GnFactoryManager* GnFactoryManager::mpSingletone = NULL;

GnMeshData* GnFactoryManager::CreateMeshData()
{
	if( mpSingletone )
	{
		return mpSingletone->CreateMeshDataImp();
	}
	return NULL;
}

GnTexture* GnFactoryManager::CreateTexture()
{
	if( mpSingletone )
	{
		return mpSingletone->CreateTextureImp();
	}
	return NULL;
}