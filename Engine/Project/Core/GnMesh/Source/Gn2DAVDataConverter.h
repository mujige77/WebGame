#ifndef GN2DAVDATACONVERTER_H
#define GN2DAVDATACONVERTER_H

GnVector2 GetMaxSize(Gn2DTextureAni* ani);
GnVector2 GetMaxSize(GnVector2& size1, GnVector2& size2);
GnIRect ConvertGnRectToCocosRect(GnIRect srcRect, CCSize baseSize);

#endif // GN2DAVDATACONVERTER_H