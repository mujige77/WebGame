#include "GnMainPCH.h"
#include "GnTexture.h"
#include "GnFactoryManager.h"

gchar GnTexture::msTextureWorkPath[GN_MAX_PATH] = {0,};

GnImplementRTTI(GnTexture, GnObject);
GnTexture::GnTexture() : mFileName(NULL)
{
	
}

GnTexture::~GnTexture()
{
	if( mpTextureMap )
		GnDelete mpTextureMap;
} 
gchar* GnTexture::GetTextureWorkPath()
{
	return msTextureWorkPath;
}

void GnTexture::SetTextureWorkPath(gchar* val)
{
	GnStrcpy( msTextureWorkPath, val, sizeof(msTextureWorkPath) );
}

bool GnTexture::CreateTexture(GnTextureMap::eMapType mapType)
{
	mpTextureMap = GnTextureMap::CreateMap( mapType );

	gchar textureWorkPath[GN_MAX_PATH] = { 0, };
	GnStrcpy( textureWorkPath, msTextureWorkPath, sizeof(textureWorkPath) );
	GnStrcat( textureWorkPath, mFileName, sizeof(textureWorkPath) );
	if( DoCreateTexture( textureWorkPath ) == false )
	{
		if( DoCreateTexture( mFileName ) == false )
			return false;
	}
	
	return true;
}

GnObject* GnTexture::CreateObject()
{
	return GnFactoryManager::CreateTexture();
}

void GnTexture::LoadStream(GnObjectStream* pStream)
{
	pStream->LoadFixedString( mFileName );
	
	gushort mapType = 0;
	pStream->LoadStream( mapType );
	GnAssert( mapType < GnTextureMap::MAPTYPE_MAX );
	GnVerify( CreateTexture( (GnTextureMap::eMapType)mapType ) );
}

void GnTexture::LinkObject(GnObjectStream* pStream)
{
}

void GnTexture::SaveStream(GnObjectStream* pStream)
{
	pStream->SaveFixedString( mFileName );

	gushort mapType = mpTextureMap->GetMapType();
	pStream->SaveStream( mapType );
}

void GnTexture::RegisterSaveObject(GnObjectStream* pStream)
{
	GnObject::RegisterSaveObject( pStream );

	pStream->RegisterFixedString( mFileName );
}