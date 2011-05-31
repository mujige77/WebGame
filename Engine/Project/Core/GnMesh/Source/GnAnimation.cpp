#include "GnMeshPCH.h"
#include "Gn2DTextureAni.h"

void GnAnimation::AniInfo::LoadStream(GnStream* pStream)
{
	pStream->LoadStream( mStartTime );
	pStream->LoadStream( mEndTime );
}

void GnAnimation::AniInfo::SaveStream(GnStream* pStream)
{
	pStream->SaveStream( mStartTime );
	pStream->SaveStream( mEndTime );
}

GnImplementRTTI(GnAnimation, GnObject);
void GnAnimation::LoadStream(GnObjectStream* pStream)
{
	GnObject::LoadStream( pStream );

	pStream->LoadStream( mAniSpeed );
}

void GnAnimation::LinkObject(GnObjectStream* pStream)
{
	GnObject::LinkObject( pStream );
}

void GnAnimation::SaveStream(GnObjectStream* pStream)
{
	GnObject::SaveStream( pStream );

	pStream->SaveStream( mAniSpeed );
}

void GnAnimation::RegisterSaveObject(GnObjectStream* pStream)
{
	GnObject::RegisterSaveObject( pStream );
}

GnAnimation::GnAnimation() : mAniSpeed(1.0f)
{
	SetCreateData( false );
	SetMeshStream( true );
}

void GnAnimation::SetTarget(GnObjectForm* pObject)
{
	mpTarget = GnDynamicCast( Gn2DMeshObject, pObject );
	GnAssert( mpTarget );
}