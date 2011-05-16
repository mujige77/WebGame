#include "GnDirectx9RendererPCH.h"
#include "GnDX9Texture.h"

GnDX9Texture::GnDX9Texture() : mpTexture( NULL )
{

}

GnDX9Texture::~GnDX9Texture()
{

}

bool GnDX9Texture::DoCreateTexture(const gchar* tcPathName)
{
	GnDirectx9Renderer* renderer = GnDirectx9Renderer::GetRenderer();
	
	HRESULT hr = D3DXCreateTextureFromFileA( renderer->GetDevice(), tcPathName, &mpTexture );
	if ( FAILED(hr) )
		return false;

	return true;
}