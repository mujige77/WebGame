#ifndef GN2DAVDATACONVERTER_H
#define GN2DAVDATACONVERTER_H

GNMESH_ENTRY static GnVector2 GetMaxSize(Gn2DTextureAni* ani);
GNMESH_ENTRY static GnVector2 GetMaxSize(GnVector2& size1, GnVector2& size2);
GNMESH_ENTRY static GnFRect ConvertGnRectToCocosRect(GnFRect srcRect, CCSize baseSize)
#endif // GN2DAVDATACONVERTER_H