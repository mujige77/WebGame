#include "GnMainPCH.h"
#include "GnRenderObject.h"

GnImplementRTTI(GnRenderObject, GnAVObject);

GnRenderObject::GnRenderObject(GnTransform* pObject) : GnAVObject(pObject)
{
}

void GnRenderObject::LoadStream(GnObjectStream* pStream)
{
	GnAVObject::LoadStream( pStream );

	pStream->LoadMultipleLinkIDs();
}

void GnRenderObject::LinkObject(GnObjectStream* pStream)
{
	GnAVObject::LinkObject( pStream );

	guint32 size = pStream->GetNumberOfLinkIDs();
	if( size )
	{
		mPropertys.SetSize( size );
		for( gtuint i = 0 ; i < size ; i++ )
		{
			GnProperty* prop = (GnProperty*)pStream->GetObjectFromLinkID();
			mPropertys.SetAt( i, prop );
		}
	}
	
}

void GnRenderObject::SaveStream(GnObjectStream* pStream)
{
	GnAVObject::SaveStream( pStream );

	guint32 savePropertyCount = 0;
	for( gtuint i = 0 ; i < mPropertys.GetSize() ; i++ )
	{
		GnProperty* prop = mPropertys.GetAt( i );
		if( prop->IsControllerProperty() == false )
			savePropertyCount++;
	}

	pStream->SaveStream( savePropertyCount );
	for( gtuint i = 0 ; i < mPropertys.GetSize() ; i++ )
	{
		GnProperty* prop = mPropertys.GetAt( i );
		if( prop->IsControllerProperty() == false )
			prop->SaveStream( pStream );
	}	
}

void GnRenderObject::RegisterSaveObject(GnObjectStream* pStream)
{
	GnAVObject::RegisterSaveObject( pStream );

	for( gtuint i = 0 ; i < mPropertys.GetSize() ; i++ )
	{
		GnProperty* prop = mPropertys.GetAt( i );
		if( prop->IsControllerProperty() == false )
			prop->RegisterSaveObject( pStream );
	}	
}
