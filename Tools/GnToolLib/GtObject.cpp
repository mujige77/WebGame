#include "GnToolLibPCH.h"
#include "GtObject.h"

GnImplementRootRTTI(GtObject);

GtObject::GtObject() : mIndex(0), mNewItem(false)
{

}

bool GtObject::EnableLoadGnObject()
{
	if( mNewItem )
		return false;

	return true;
}