#include "GnMainPCH.h"
#include "GnRTTI.h"

GnRTTI::GnRTTI( const gchar* pName, const GnRTTI* pBaseRTTI ) : mpName(pName), mpBaseRTTI(pBaseRTTI)
{
}

bool GnRTTI::CopyName( gchar* nameBuffer, gtuint uiMaxSize ) const
{
	const char* pcName = GetName();
	if (!pcName || !nameBuffer)
	{
		GnStrcpy(nameBuffer, "\0", uiMaxSize);
		return false;
	}

	GnStrcpy(nameBuffer, pcName, uiMaxSize);
	return true;
}