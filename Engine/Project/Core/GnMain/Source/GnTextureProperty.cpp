#include "GnMainPCH.h"
#include "GnTextureProperty.h"
#include "GnFactoryManager.h"

GnImplementRTTI(GnTextureProperty, GnProperty);
GnTextureProperty::GnTextureProperty()
{
}

GnTextureProperty::GnTextureProperty(const gchar* tcPathName)
{
	GnTexture* texture = GnFactoryManager::CreateTexture();
	texture->CreateTexture(GnTextureMap::BASE_MAP, tcPathName);
	SetTexture(texture);
}
GnTextureProperty::~GnTextureProperty()
{
}

gtuint GnTextureProperty::GetType()
{
	return GnProperty::TEXTURE_PROPERTY;
}

gtuint GnTextureProperty::GetPropertyType()
{
	return GnProperty::TEXTURE_PROPERTY;
}

void GnTextureProperty::SetTexture(GnTexture* pTexture)
{
	GnAssert(pTexture && pTexture->GetIndex() < GnTextureMap::MAPTYPE_MAX);
	mpTextures[pTexture->GetIndex()] = pTexture;
}

void GnTextureProperty::SetNullTexture(gtuint uiIndex)
{
	GnAssert(uiIndex < GnTextureMap::MAPTYPE_MAX);
	mpTextures[uiIndex] = NULL;
}


GnImplementCreateObject(GnTextureProperty);
void GnTextureProperty::LoadStream(GnObjectStream* pStream)
{
	GnProperty::LoadStream( pStream );

	pStream->LoadMultipleLinkIDs(); // mpTextures
}

void GnTextureProperty::LinkObject(GnObjectStream* pStream)
{
	GnProperty::LinkObject( pStream );

	guint32 numTexture = pStream->GetNumberOfLinkIDs();
	for( guint32 i = 0 ; i < numTexture ; i++ )
	{
		GnTexture* getTexture = (GnTexture*)pStream->GetObjectFromLinkID();
		GnAssert( getTexture->GetTextureMap() );
		mpTextures[getTexture->GetTextureMap()->GetMapType()] = getTexture;
	}
}

void GnTextureProperty::SaveStream(GnObjectStream* pStream)
{
	GnProperty::SaveStream( pStream );

	guint32 numTexture = 0;
	for( gtuint i = 0 ; i < GnTextureMap::MAPTYPE_MAX ; i++ )
	{
		if( mpTextures[i] )
			++numTexture;
	}
	pStream->SaveStream( numTexture );
	for( gtuint i = 0 ; i < GnTextureMap::MAPTYPE_MAX ; i++ )
	{
		if( mpTextures[i] )
			pStream->SaveLinkID( mpTextures[i] );
	}
}

void GnTextureProperty::RegisterSaveObject(GnObjectStream* pStream)
{
	GnProperty::RegisterSaveObject( pStream );
	
	for( gtuint i = 0 ; i < GnTextureMap::MAPTYPE_MAX ; i++ )
	{
		if( mpTextures[i] )
			mpTextures[i]->RegisterSaveObject( pStream );
	}
}
