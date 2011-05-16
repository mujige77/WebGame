#include "GnMeshPCH.h"
#include "GnSequence.h"

GnImplementRTTI(GnSequence, GnObject);

void GnSequence::SetTargetObject(GnObjectForm* pObject)
{
	GnTimeController* pkControl = mpsTimeControls;
	while( pkControl )
	{
		bool failed = pkControl->SetTargetObject(pObject);
		if( failed == false )
		{
			GnLogA( "Warning : Failed sequence targeting = %s",
				pkControl->GetTargetName().Exists() ? pkControl->GetTargetName() : "NULL Controller TargetName");
		}
		pkControl = pkControl->GetNext();
	}
}

void GnSequence::Start(float fTime)
{
	GnTimeController* pkControl = mpsTimeControls;
	while( pkControl )
	{
		pkControl->Start(fTime);
		pkControl = pkControl->GetNext();
	}
}

void GnSequence::Stop()
{
	GnTimeController* pkControl = mpsTimeControls;
	while( pkControl )
	{
		pkControl->Stop();
		pkControl = pkControl->GetNext();
	}
}

GnImplementCreateObject(GnSequence);
void GnSequence::LoadStream(GnObjectStream* pStream)
{
	pStream->LoadFixedString( mName );
	pStream->LoadLinkID(); // mpsTimeControls
	
	pStream->LoadStream( mStartTime );
	pStream->SaveStream( mEndTime );
}

void GnSequence::LinkObject(GnObjectStream* pStream)
{
	mpsTimeControls = (GnTimeController*)pStream->GetObjectFromLinkID();
}

void GnSequence::SaveStream(GnObjectStream* pStream)
{
	pStream->SaveFixedString( mName );

	GnTimeController* control = mpsTimeControls;
	while( control && control->IsStreamable() == false )
		control = control->GetNext();
	pStream->SaveLinkID( control );

	pStream->SaveStream( mStartTime );
	pStream->SaveStream( mEndTime );
}

void GnSequence::RegisterSaveObject(GnObjectStream* pStream)
{
	GnObject::RegisterSaveObject( pStream );
	pStream->RegisterFixedString( mName );

	if( mpsTimeControls )
		mpsTimeControls->RegisterSaveObject( pStream );
}
//void GnSequence::LoadStream(GnActorStream* pStream)
//{
//	pStream->SaveStream(mSequenceID);
//	pStream->savefi
//	mFileName;
//}
//
//void GnSequence::SaveStream(GnActorStream* pStream)
//{
//}