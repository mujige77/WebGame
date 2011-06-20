#ifndef GN2DAVDATACONVERTER_H
#define GN2DAVDATACONVERTER_H

GNMESH_ENTRY static GnVector2 GetMaxSize(Gn2DTextureAni* ani);
GNMESH_ENTRY static GnVector2 GetMaxSize(GnVector2& size1, GnVector2& size2);
static GnIRect ConvertGnRectToCocosRect(GnIRect srcRect, CCSize baseSize)
{
	srcRect.top = (int)baseSize.height - srcRect.top;
	srcRect.bottom = (int)baseSize.height - srcRect.bottom;
	return srcRect;
}

#endif // GN2DAVDATACONVERTER_H