#include "GnMeshPCH.h"
#include "Gn2DSequence.h"

GnImplementRTTI(Gn2DSequence, GnSequence);

Gn2DSequence::Gn2DSequence()
{

}

Gn2DSequence::~Gn2DSequence()
{
}

GnImplementCreateObject(Gn2DSequence);
void Gn2DSequence::LoadStream(GnObjectStream* pStream)
{
	GnObject::LoadStream( pStream );

	mAnimationKeyManager.LoadStream( pStream );

	pStream->LoadStream( mID );
	pStream->LoadStream( mStartTime );
	pStream->LoadStream( mEndTime );

	pStream->LoadLinkID();

	pStream->LoadMultipleLinkIDs();
}

void Gn2DSequence::LinkObject(GnObjectStream* pStream)
{
	GnObject::LinkObject( pStream );

	mpsAVData = (Gn2DAVData*)pStream->GetObjectFromLinkID();
	if( mpsAVData )
		mpsAVData->SetMeshStream( false );

	guint32 size = pStream->GetNumberOfLinkIDs();
	if( size )
	{
		mTextureAni.SetSize( size );
		for( gtuint i = 0 ; i < mTextureAni.GetAllocatedSize() ; i++ )
		{
			Gn2DTextureAni* ani = (Gn2DTextureAni*)pStream->GetObjectFromLinkID();
			ani->SetMeshStream( false );
			mTextureAni.SetAt( i, ani );
		}
	}
}

void Gn2DSequence::SaveStream(GnObjectStream* pStream)
{
	GnObject::SaveStream( pStream );

	mAnimationKeyManager.SaveStream( pStream );

	pStream->SaveStream( mID );
	pStream->SaveStream( mStartTime );
	pStream->SaveStream( mEndTime );

	pStream->SaveLinkID( mpsAVData );

	guint32 size = mTextureAni.GetSize();
	pStream->SaveStream( size );
	for( gtuint i = 0 ; i < mTextureAni.GetSize() ; i++)
	{
		Gn2DTextureAni* ani =  mTextureAni.GetAt( i );
		pStream->SaveLinkID( ani );
	}
}

void Gn2DSequence::RegisterSaveObject(GnObjectStream* pStream)
{
	GnObject::RegisterSaveObject( pStream );

	if( mpsAVData )
		mpsAVData->RegisterSaveObject( pStream );

	for( gtuint i = 0 ; i < mTextureAni.GetSize() ; i++)
	{
		Gn2DTextureAni* ani =  mTextureAni.GetAt( i );
		ani->RegisterSaveObject( pStream );
	}
}

void Gn2DSequence::SetTargetObject(GnObjectForm* pObject)
{
	mpsTarget = (Gn2DMeshObject*)pObject;
	for( gtuint i = 0 ; i < mTextureAni.GetSize() ; i++)
	{
		Gn2DTextureAni* ani =  mTextureAni.GetAt( i );	
		ani->SetTarget( pObject );
	}
}
void Gn2DSequence::Update(float fDeltaTime)
{
	mAccumulateDeltaTime += fDeltaTime;
	if( mAccumulateDeltaTime >= mEndTime )
	{
		Stop();
		if( IsLoop() )
		{
			Start( 0.0f );
		}
	}
}

void Gn2DSequence::Start(float fTime)
{
	mAccumulateDeltaTime = 0.0f;
	ResetTargetAV();
	for( gtuint i = 0 ; i < mTextureAni.GetSize() ; i++)
	{
		Gn2DTextureAni* ani =  mTextureAni.GetAt( i );	
		ani->Start( fTime );
	}
}

void Gn2DSequence::Stop()
{
	for( gtuint i = 0 ; i < mTextureAni.GetSize() ; i++)
	{
		Gn2DTextureAni* ani =  mTextureAni.GetAt( i );	
		ani->Stop();
	}
}

void Gn2DSequence::ResetTargetAV()
{
	mpsTarget->SetAVData( mpsAVData );
}