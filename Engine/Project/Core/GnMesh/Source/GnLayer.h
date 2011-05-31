#ifndef GnLayer_H
#define GnLayer_H
#include "GnDrawPrimitives.h"
class GnLayer : public CCLayerColor
{
public:
	GnLayer(){};
	virtual ~GnLayer(){};
	void AddChild(Gn2DMeshObject* pObject, int iZOrder = 50);
	void RemoveChild(Gn2DMeshObject* pObject);
};

class GnLayerDrawPrimitives : public GnLayer
{
protected:
	GnTObjectArray<GnDrawPrimitivesPtr> mDrawObjects;

public:
	GnLayerDrawPrimitives();
	virtual ~GnLayerDrawPrimitives(){};
	virtual void draw();
	void AddChild(GnDrawPrimitives* pObject);
	void RemoveChild(GnDrawPrimitives* pObject);
};

#endif // GnLayer_H