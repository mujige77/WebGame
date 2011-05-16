#include "GnMainPCH.h"
#include "GnObject.h"
#include "GnStream.h"

GnImplementRootRTTI(GnObject);

GnObject::GnObject()
{
}

bool GnObject::GetRTTINameForStream(gchar* outName, gtuint uiMaxSize)
{
	return GetRTTI()->CopyName(outName, uiMaxSize);
}

void GnObject::LoadStream(GnObjectStream* pStream)
{
}

void GnObject::LinkObject(GnObjectStream* pStream)
{

}

void GnObject::SaveStream(GnObjectStream* pStream)
{
}

void GnObject::RegisterSaveObject(GnObjectStream* pStream)
{
	pStream->RegisterSaveObject(this);
}
