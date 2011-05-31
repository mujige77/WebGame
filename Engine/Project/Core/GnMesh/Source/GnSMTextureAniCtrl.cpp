#include "GnMeshPCH.h"
#include "GnSMTextureAniCtrl.h"


GnImplementRTTI(GnSMTextureAniCtrl, GnTimeController);

GnSMTextureAniCtrl::GnSMTextureAniCtrl(gtuint uiNumAni) : mpCurrentAni(NULL)
{
	ReCreate(uiNumAni, false);
}
GnSMTextureAniCtrl::~GnSMTextureAniCtrl()
{
	GnRenderObject* object = GnDynamicCast(GnRenderObject, mpTarget);
	if( mpCurrentAni && object )
	{
		object->DetachProperty( mpCurrentAni->mpsPrperty );
	}
}

void GnSMTextureAniCtrl::Update(float fTime)
{
	if( mPlayFlags != PLAY )
		return;

	GnRenderObject* object = GnDynamicCast(GnRenderObject, mpTarget);
	if( mpCurrentAni == NULL )
		return;
	
	float deltaTime = fTime - mStartTime;
	if( mpCurrentAni->mEndTime < deltaTime )
	{
		if( mCurrentAniIndex < mAnis.GetSize() )
		{
			if( mpCurrentAni )
				object->DetachProperty( mpCurrentAni->mpsPrperty );

			mStartTime = fTime;
			mpCurrentAni = &mAnis.GetAt(mCurrentAniIndex++);
			
			if( mpCurrentAni )
				object->AttachProperty( mpCurrentAni->mpsPrperty );			
		}
		else
		{
			if( IsLoop() )
			{
				Start(fTime);
				GnLogA( "start" );
			}
			else
				Stop();
		}
	}
}

void GnSMTextureAniCtrl::SetAniInfo(gtuint uiIndex, GnTextureProperty* pTexture, float fStartTime
	, float fEndTime)
{
	if( pTexture )
		pTexture->SetControllerProperty( true );

	TextureAni ani;
	ani.mpsPrperty = pTexture;
	ani.mStartTime = fStartTime;
	ani.mEndTime = fEndTime;
	mAnis.SetAt(uiIndex, ani);
}

bool GnSMTextureAniCtrl::ReCreate(gtuint uiNumAni, bool bSaveAniData)
{
	mAnis.Resize(uiNumAni, bSaveAniData);

	Stop();

	mpCurrentAni = NULL;
	return true;
}

void GnSMTextureAniCtrl::Stop()
{	
	mPlayFlags = STOP;
	GnRenderObject* object = GnDynamicCast( GnRenderObject, mpTarget );
	if( mpCurrentAni && object )
		object->DetachProperty( mpCurrentAni->mpsPrperty );
}

void GnSMTextureAniCtrl::Start(float fTime)
{
	mPlayFlags = PLAY;
	GnTimeController::Start(fTime);
	GnRenderObject* object = GnDynamicCast( GnRenderObject, mpTarget );
	GnAssert( object );

	if( mpCurrentAni )
		object->DetachProperty( mpCurrentAni->mpsPrperty );

	mCurrentAniIndex = 0;
	mpCurrentAni = &mAnis.GetAt( mCurrentAniIndex++ );
	if( mpCurrentAni )
	{
		if( object )
			object->AttachProperty( mpCurrentAni->mpsPrperty );
	}
}


GnImplementCreateObject(GnSMTextureAniCtrl);
void GnSMTextureAniCtrl::LoadStream(GnObjectStream* pStream)
{
	GnTimeController::LoadStream( pStream );
	
	mImageRect.LoadStream( pStream );

	guint32 numAni = pStream->LoadMultipleLinkIDs(); // mAnis
	mAnis.SetSize( numAni );
	for( gtuint i = 0 ; i < numAni ; i++ )
	{
		TextureAni& texAni = mAnis[i];
		pStream->LoadStream( texAni.mStartTime );
		pStream->LoadStream( texAni.mEndTime );
		mAnis.SetAt( i, texAni );
	}
}

void GnSMTextureAniCtrl::LinkObject(GnObjectStream* pStream)
{
	GnTimeController::LinkObject( pStream );

	guint32 numAni = pStream->GetNumberOfLinkIDs();
	GnAssert( numAni == mAnis.GetSize() );

	for( guint32 i = 0 ; i < numAni ; i++ )
	{
		mAnis[i].mpsPrperty = (GnTextureProperty*)pStream->GetObjectFromLinkID();
		mAnis[i].mpsPrperty->SetControllerProperty( true );
	}
}

void GnSMTextureAniCtrl::SaveStream(GnObjectStream* pStream)
{
	GnTimeController::SaveStream( pStream );

	mImageRect.SaveStream( pStream );

	guint32 numProperty = (guint32)mAnis.GetSize();
	pStream->SaveStream( numProperty );
	for( gtuint i = 0 ; i < mAnis.GetSize() ; i++ )
	{
		GnAssert( mAnis[i].mpsPrperty );
		pStream->SaveLinkID( mAnis[i].mpsPrperty );
	}

	for( gtuint i = 0 ; i < mAnis.GetSize() ; i++ )
	{
		TextureAni& texAni = mAnis[i];
		pStream->SaveStream( texAni.mStartTime );
		pStream->SaveStream( texAni.mEndTime );
	}
}

void GnSMTextureAniCtrl::RegisterSaveObject(GnObjectStream* pStream)
{
	GnTimeController::RegisterSaveObject( pStream );

	for( gtuint i = 0 ; i < mAnis.GetSize() ; i++ )
	{
		GnAssert( mAnis[i].mpsPrperty );
		mAnis[i].mpsPrperty->RegisterSaveObject( pStream );
	}
}

bool GnSMTextureAniCtrl::SetTargetObject(GnObjectForm* pObject)
{
	if( GnTimeController::SetTargetObject( pObject ) == false )
		return false;

	//Gn2DMeshObject* element =  GnDynamicCast( Gn2DMeshObject, pObject );
	//GnAssert( element );
	//element->SetDisplayRect( mImageRect );
	return true;
}