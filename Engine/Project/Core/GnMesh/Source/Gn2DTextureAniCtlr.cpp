#include "GnMeshPCH.h"
#include "Gn2DTextureAniCtlr.h"


Gn2DTextureAniCtlr::TextureAniInfo::TextureAniInfo() : mTextureName(NULL)
{
}

Gn2DTextureAniCtlr::TextureAniInfo::~TextureAniInfo()
{
	if( mTextureName  )
		GnFree( mTextureName );
	if( mpMesh )
		mpMesh->release();
}

void Gn2DTextureAniCtlr::TextureAniInfo::LoadStream(GnStream* pStream)
{
	pStream->LoadStream( mStartTime );
	pStream->LoadStream( mEndTime );
	pStream->LoadStream( mTextureName );
}

void Gn2DTextureAniCtlr::TextureAniInfo::SaveStream(GnStream* pStream)
{
	pStream->SaveStream( mStartTime );
	pStream->SaveStream( mEndTime );
	pStream->SaveStream( mTextureName );
}

GnImplementRTTI(Gn2DTextureAniCtlr, GnTimeController);

GnImplementCreateObject(Gn2DTextureAniCtlr);
void Gn2DTextureAniCtlr::LoadStream(GnObjectStream* pStream)
{
	GnTimeController::LoadStream( pStream );

	guint16 size = 0;
	pStream->LoadStream( size );
	mInfos.SetSize( (gtuint)size, 1 );

	for( gtuint i = 0 ; i < (gtuint)size ; i++)
	{
		TextureAniInfo* info = GnNew TextureAniInfo();
		info->LoadStream( pStream );
		mInfos.SetAt( i, info );
	}
}

void Gn2DTextureAniCtlr::LinkObject(GnObjectStream* pStream)
{
	GnTimeController::LinkObject( pStream );
}

void Gn2DTextureAniCtlr::SaveStream(GnObjectStream* pStream)
{
	GnTimeController::SaveStream( pStream );

	guint16 size = (guint16)mInfos.GetSize();
	pStream->SaveStream( size );

	for( gtuint i = 0 ; i < (gtuint)size ; i++)
	{
		mInfos.GetAt( i )->SaveStream( pStream );
	}
}

void Gn2DTextureAniCtlr::RegisterSaveObject(GnObjectStream* pStream)
{
	GnTimeController::RegisterSaveObject( pStream );
}

Gn2DTextureAniCtlr::Gn2DTextureAniCtlr() : mpCurrentAni( NULL )
{	
	CreateData();
}

Gn2DTextureAniCtlr::~Gn2DTextureAniCtlr()
{
	RemoveData();
}

bool Gn2DTextureAniCtlr::CreateData()
{
	CCMutableArray<CCSpriteFrame*> animFrames( mInfos.GetSize() );		
	float aniTime = 0.1f;
	for( gtuint i = 0 ; i < mInfos.GetSize() ; i++ )
	{
		TextureAniInfo* info = mInfos.GetAt( i );

		gchar textureWorkPath[GN_MAX_PATH] = { 0, };
		GnStrcpy( textureWorkPath, GnSystem::GetWorkDirectory(), sizeof(textureWorkPath) );
		GnStrcat( textureWorkPath, info->GetTextureName(), sizeof(textureWorkPath) );
		GnReal2DMesh* mesh = GnReal2DMesh::spriteWithFile( textureWorkPath );
		if( mesh == NULL )
			mesh= GnReal2DMesh::spriteWithFile( info->GetTextureName() );
	}
	return true;
}

void Gn2DTextureAniCtlr::RemoveData()
{
	for( gtuint i = 0 ; i < mInfos.GetSize() ; i++ )
	{
		TextureAniInfo* info = mInfos.GetAt( i );
		if( info )
			GnDelete info;
	}
	//if( mpAnimate )
	//{
	//	if( Get2DMeshObject() )
	//	{
	//		GnReal2DMesh* mesh = Get2DMeshObject()->GetMesh();
	//		mesh->stopAction( mpAnimate );
	//	}
	//	mpAnimate->release();
	//}
	//mpAnimate = NULL;
	//SetCreateData( false );
}

void Gn2DTextureAniCtlr::Start(float fTime)
{
	GnTimeController::Start( fTime );
	GnAssert( Get2DMeshObject() );

	if( mpCurrentAni )	
		Get2DMeshObject()->GetMesh()->removeChild( mpCurrentAni->GetMesh(), true );
	
	GnAssert( mInfos.GetSize() );
	mCurrentAniIndex = 0;
	mpCurrentAni = mInfos.GetAt( mCurrentAniIndex++ );
	

	if( mpCurrentAni  )
		Get2DMeshObject()->GetMesh()->addChild( mpCurrentAni->GetMesh() );
}

void Gn2DTextureAniCtlr::Stop()
{
	GnTimeController::Stop();
}

void Gn2DTextureAniCtlr::Update(float fDeltaTime)
{
	if( mPlayFlags != PLAY )
		return;

	GnRenderObject* object = GnDynamicCast(GnRenderObject, mpTarget);
	if( mpCurrentAni == NULL )
		return;

	float deltaTime = fDeltaTime + GetAccumulateTime();
	if( mpCurrentAni->GetEndTime() < deltaTime )
	{
		if( mCurrentAniIndex < mInfos.GetSize() )
		{
			if( mpCurrentAni )	
				Get2DMeshObject()->GetMesh()->removeChild( mpCurrentAni->GetMesh(), true );

			SetAccumulateTime( 0.0f );
			mpCurrentAni = mInfos.GetAt(mCurrentAniIndex++);

			if( mpCurrentAni  )
				Get2DMeshObject()->GetMesh()->addChild( mpCurrentAni->GetMesh() );
		}
		else
		{
			if( IsLoop() )
			{
				Start( 0.0f );
			}
			else
				Stop();
		}
	}
}