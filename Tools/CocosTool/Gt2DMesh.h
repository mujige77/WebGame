#pragma once
#include "GtObject.h"

class Gt2DMesh : public GtObject
{
	GnDeclareRTTI;
public:
	const static  gint OBJECT_TYPE = 2;

private:
	Gn2DMeshObjectPtr mpsMesh;
	GnSimpleString mGMFileName;

public:
	Gt2DMesh(void);
	~Gt2DMesh(void);

	Gn2DMeshObject* Get2DMeshObjecct() {
		return mpsMesh;
	}
};

