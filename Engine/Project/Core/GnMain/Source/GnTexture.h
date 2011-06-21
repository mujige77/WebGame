#ifndef GNTEXTURE_H
#define GNTEXTURE_H

#include "GnTextureMap.h"

class GnTexture : public GnObject
{
	GnDeclareRTTI;
	GnDeclareStream;
protected:
	static gchar msTextureWorkPath[GN_MAX_PATH];
	
	GnTextureMap* mpTextureMap;
	GnSimpleString mFileName;
	guint mWidth;	
	guint mHeight;

public:
	GnTexture();
	virtual ~GnTexture();

public:
	static gchar* GetTextureWorkPath();	
	static void SetTextureWorkPath(const gchar* val);

	inline bool CreateTexture(GnTextureMap::eMapType mapType, const gchar* pcPathName) {	
		mFileName = pcPathName;
		return CreateTexture( mapType );
	}

	inline GnTextureMap* GetTextureMap() { return mpTextureMap; }	
	inline gtuint GetIndex() { return mpTextureMap->GetMapType(); }
	inline guint GetWidth() const { return mWidth; }
	inline guint GetHeight() const { return mHeight; }
	inline const gchar* GetTextureFileName() {
		return mFileName;
	}
	
	
protected:
	virtual bool DoCreateTexture(const gchar* tcPathName) = 0;
	inline void SetWidth(guint val) { mWidth = val; }
	inline void SetHeight(guint val) { mHeight = val; }

private:
	bool CreateTexture(GnTextureMap::eMapType mapType);
};

GnSmartPointer(GnTexture);

#endif // GNTEXTURE_H