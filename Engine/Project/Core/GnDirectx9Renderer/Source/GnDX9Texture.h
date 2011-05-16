#ifndef GNDX9TEXTURE_H
#define GNDX9TEXTURE_H

#include "GnTexture.h"

class GnDX9Texture : public GnTexture
{
protected:
	LPDIRECT3DTEXTURE9 mpTexture;	
	
public:
	GnDX9Texture();
	virtual ~GnDX9Texture();

	virtual bool DoCreateTexture(const gchar* tcPathName);

	inline LPDIRECT3DTEXTURE9 GetDX9Texture()
	{
		return mpTexture;
	}
};

#endif // GNDX9TEXTURE_H