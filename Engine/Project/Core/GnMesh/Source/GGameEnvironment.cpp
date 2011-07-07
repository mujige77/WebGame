#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GMainGameEnvironment.h"

GGameEnvironment* GGameEnvironment::mpSingleton = NULL;

GGameEnvironment* GGameEnvironment::GetSingleton()
{
	return mpSingleton;
}