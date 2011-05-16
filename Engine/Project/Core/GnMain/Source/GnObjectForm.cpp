#include "GnMainPCH.h"
#include "GnObjectForm.h"

GnImplementRTTI(GnObjectForm, GnObject);

GnObjectForm::GnObjectForm()
{

}

GnObjectForm* GnObjectForm::GetObjectByName(const GnSimpleString& kName)
{
	if( kName.Exists() == false )
		return NULL;

	if( GetName() != kName )
		return NULL;

	return this;
}

void GnObjectForm::LoadStream(GnObjectStream* pStream)
{
	GnObject::LoadStream( pStream );
	
	pStream->LoadFixedString( mName );
	GnAssert( mName.GetHandle() );
}

void GnObjectForm::LinkObject(GnObjectStream* pStream)
{
	GnObject::LinkObject( pStream );
}

void GnObjectForm::SaveStream(GnObjectStream* pStream)
{
	GnObject::SaveStream( pStream );

	pStream->SaveFixedString( mName );
	GnAssert( mName.GetHandle() );
}

void GnObjectForm::RegisterSaveObject(GnObjectStream* pStream)
{
	GnObject::RegisterSaveObject( pStream );

	pStream->RegisterFixedString( mName );
}
