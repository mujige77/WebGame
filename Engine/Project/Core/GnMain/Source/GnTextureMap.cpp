#include "GnMainPCH.h"
#include "GnTextureMap.h"


GnTextureMap* GnTextureMap::CreateMap(eMapType mapType)
{
	GnTextureMap* retMap = NULL;
	switch(mapType)
	{
	case BASE_MAP:
		retMap = GnNew GnTextureMap(mapType);
		break;
	}
	return retMap;
}

GnTextureMap::GnTextureMap(eMapType mapType) : mMapType(mapType)
{

}