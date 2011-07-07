#include "GnMainPCH.h"
#include "GnObjectForm.h"

GnImplementRTTI(GnObjectForm, GnObject);

GnObjectForm::GnObjectForm()
{

}
void GnObjectForm::Update(float fDeltaTime)
{
	GnTimeController* ctrl = mpsControls;
	while( ctrl )
	{
		ctrl->Update( fDeltaTime );
		ctrl = ctrl->GetNext();
	}
}

GnObjectForm* GnObjectForm::GetObjectByName(const GnSimpleString& kName)
{
	if( kName.Exists() == false )
		return NULL;

	if( GetName() != kName )
		return NULL;

	return this;
}

void GnObjectForm::SetController(GnTimeController* pCtlr)
{
	GnTimeController* ctlr = GetControllers();
	if( ctlr == NULL )
		SetControllers( pCtlr  );

	do
	{
		if( ctlr->GetNext() == NULL )
		{
			ctlr->SetNext( pCtlr );
			break;
		}
		ctlr = ctlr->GetNext();
	}
	while( ctlr );
}

void GnObjectForm::LoadStream(GnObjectStream* pStream)
{
	GnObject::LoadStream( pStream );
	
	pStream->LoadFixedString( mName );
	GnAssert( mName.GetHandle() );

	if( pStream->GetFileVersion() > GnStream::GetVersion( 1, 0, 0, 1 ) )
		pStream->LoadMultipleLinkIDs(); // mExtraDatas

	pStream->LoadLinkID(); // mpsControls
}

void GnObjectForm::LinkObject(GnObjectStream* pStream)
{
	GnObject::LinkObject( pStream );
	if( pStream->GetFileVersion() > GnStream::GetVersion( 1, 0, 0, 1 ) )
	{
		guint32 size = pStream->GetNumberOfLinkIDs();
		if( size )
		{
			mExtraDatas.SetSize( size );
			for( gtuint i = 0 ; i < size ; i++ )
			{
				GnExtraData* extra = (GnExtraData*)pStream->GetObjectFromLinkID();
				mExtraDatas.SetAt( i, extra );
			}
		}
	}
	mpsControls = (GnTimeController*)pStream->GetObjectFromLinkID();
}

void GnObjectForm::SaveStream(GnObjectStream* pStream)
{
	GnObject::SaveStream( pStream );

	pStream->SaveFixedString( mName );
	GnAssert( mName.GetHandle() );

	guint32 size = mExtraDatas.GetSize();
	pStream->SaveStream( size );
	for( gtuint i = 0 ; i < size ; i++ )
	{
		GnExtraData* extra = mExtraDatas.GetAt( i );
		pStream->SaveLinkID( extra );
	}

	GnTimeController* control = GetControllers();
	while( control && control->IsStreamable() == false )
		control = control->GetNext();
	pStream->SaveLinkID( control );
}

void GnObjectForm::RegisterSaveObject(GnObjectStream* pStream)
{
	GnObject::RegisterSaveObject( pStream );

	pStream->RegisterFixedString( mName );

	for( gtuint i = 0 ; i < mExtraDatas.GetSize() ; i++ )
	{
		GnExtraData* extra = mExtraDatas.GetAt( i );
		extra->RegisterSaveObject( pStream );
	}

	GnTimeController* control = GetControllers();
	if( control )
		control->RegisterSaveObject( pStream );
}