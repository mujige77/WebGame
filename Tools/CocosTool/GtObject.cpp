#include "StdAfx.h"
#include "GtObject.h"

GnImplementRootRTTI(GtObject);
GtObject::GtObject(void) : mNewItem(false), mModifed(false)
{
}


GtObject::~GtObject(void)
{
}

void GtObject::SetObjectName(const gchar* pcVal)
{
	mObjectName = pcVal;
}