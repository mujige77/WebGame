#include "GnMainPCH.h"
#include "GnTimeController.h"

GnImplementRootRTTI(GnTimeController);

GnTimeController::GnTimeController() : mpTarget( NULL ), mIsMeshSteram( true )
{
	mCycleType = LOOP;
	mPlayFlags = PLAY;
}

GnTimeController::~GnTimeController()
{
}

void GnTimeController::Start()
{
	mPlayFlags = PLAY;
}

void GnTimeController::Stop()
{
	mPlayFlags = STOP;
}

bool GnTimeController::SetTargetObject(GnObjectForm* pObject)
{
	if( pObject == NULL )
	{
		mpTarget = NULL;
		return true;
	}
	
	mpTarget = pObject;
	mpTarget->SetTimeController( this );
	return true;
}

void GnTimeController::Playing(float fTime)
{
	mPlayFlags = PLAYING;
	mStartTime = fTime;
	mAccumulateDeltaTime = 0.0f;
}


void GnTimeController::LoadStream(GnObjectStream* pStream)
{
	GnObject::LoadStream( pStream );	
	pStream->LoadEnumStream( mCycleType );

	pStream->LoadLinkID(); // mpsNext;
	pStream->LoadLinkID(); // mpTarget;
}

void GnTimeController::LinkObject(GnObjectStream* pStream)
{
	GnObject::LinkObject( pStream );
	mpsNext = (GnTimeController*)pStream->GetObjectFromLinkID();

	mpTarget = (GnObjectForm*)pStream->GetObjectFromLinkID();
}

void GnTimeController::SaveStream(GnObjectStream* pStream)
{
	GnObject::SaveStream( pStream );
	pStream->SaveEnumStream( mCycleType );

	GnTimeController* control = mpsNext;
	if( control && control->IsStreamable() == false )
		control = control->GetNext();
	
	pStream->SaveLinkID( control );
	pStream->SaveLinkID( mpTarget );
}

void GnTimeController::RegisterSaveObject(GnObjectStream* pStream)
{
	GnObject::RegisterSaveObject( pStream );	

	if( mpsNext )
		mpsNext->RegisterSaveObject( pStream );
}