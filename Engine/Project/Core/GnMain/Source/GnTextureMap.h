#ifndef GNTEXTUREMAP_H
#define GNTEXTUREMAP_H

class GnTextureMap : public GnMemoryObject
{
private:
	gtuint mMapType;
	
	
public:
	enum eMapType
	{
		BASE_MAP,
		//DARK_MAP,
		//DETAIL_MAP,
		//GLOSS_MAP,
		//GLOW_MAP,
		//BUMP_MAP,
		//NORMAL_MAP,
		//PARALLAX_MAP,
		//DECAL_MAP,
		//SHADER_MAP,
		MAPTYPE_MAX
	};

public:	
	virtual ~GnTextureMap(){};
	static GnTextureMap* CreateMap(eMapType mapType);
	
	inline gtuint GetMapType() const { return mMapType; }
private:
	GnTextureMap(eMapType mapType);
};


#endif // GNTEXTUREMAP_H