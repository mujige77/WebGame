#ifndef GNTEXTUREPROPERTY_H
#define GNTEXTUREPROPERTY_H

class GNMAIN_ENTRY GnTextureProperty : public GnProperty
{
	GnDeclareRTTI;
	GnDeclareStream;
protected:
	GnTexturePtr mpTextures[GnTextureMap::MAPTYPE_MAX];

public:
	GnTextureProperty(const gchar* tcPathName);
	GnTextureProperty();
	virtual ~GnTextureProperty();

	void SetTexture(GnTexture* pTexture);
	void SetNullTexture(gtuint uiIndex);

	inline GnTexture* GetTexture(gtuint uiIndex)
	{
		GnAssert( uiIndex < GnTextureMap::MAPTYPE_MAX );
		return mpTextures[uiIndex];
	}

	virtual gtuint GetType();
	static gtuint GetPropertyType();
};

GnSmartPointer(GnTextureProperty);
#endif // GNTEXTUREPROPERTY_H