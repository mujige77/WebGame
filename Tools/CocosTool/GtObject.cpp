#include "StdAfx.h"
#include "GtObject.h"


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