#ifndef GNOBJECT_H
#define GNOBJECT_H
#include "GnSmartObject.h"


class GNMAIN_ENTRY GnObject : public GnSmartObject
{
	GnDeclareRootRTTI(GnObject);
	GnDeclareAbstractStream;
public:
	GnObject();
	virtual ~GnObject(){};
	virtual bool GetRTTINameForStream(gchar* outName, gtuint uiMaxSize);
};

#endif // GNOBJECT_H