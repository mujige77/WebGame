#include "GnMainPCH.h"
#include "GnTimeController.h"

GnImplementRootRTTI(GnTimeController);

GnTimeController::GnTimeController() : mpTarget(NULL)
{
	SetLoop( true );
}

GnTimeController::~GnTimeController()
{
}

void GnTimeController::Start(float fTime)
{
	mStartTime = fTime;
}

void GnTimeController::Stop()
{
}

bool GnTimeController::SetTargetObject(GnObjectForm* pObject)
{
	if( pObject  == NULL )
	{
		mpTarget = NULL;
		return true;
	}
	GnAssert(mTargetName.Exists());
	mpTarget = (GnAVObject*)pObject->GetObjectByName(mTargetName);
	if( mpTarget == NULL )
		return false;

	mpTarget->SetControllers( this );
	return true;
}

GnImplementCreateObject(GnTimeController);
void GnTimeController::LoadStream(GnObjectStream* pStream)
{
	GnObject::LoadStream( pStream );
	pStream->LoadFixedString( mTargetName );
	pStream->LoadLinkID(); // mpsNext;
}

void GnTimeController::LinkObject(GnObjectStream* pStream)
{
	GnObject::LinkObject( pStream );
	mpsNext = (GnTimeController*)pStream->GetObjectFromLinkID();
}

void GnTimeController::SaveStream(GnObjectStream* pStream)
{
	GnObject::SaveStream( pStream );
	pStream->SaveFixedString( mTargetName );

	GnTimeController* control = mpsNext;
	if( control && control->IsStreamable() == false )
		control = control->GetNext();

	pStream->SaveLinkID( control );
}

void GnTimeController::RegisterSaveObject(GnObjectStream* pStream)
{
	GnObject::RegisterSaveObject( pStream );
	pStream->RegisterFixedString( mTargetName );

	if( mpsNext )
		mpsNext->RegisterSaveObject( pStream );
}