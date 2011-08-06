#include "GnMeshPCH.h"
#include "Gn2DTextureAni.h"


Gn2DTextureAni::TextureAniInfo::TextureAniInfo() : mTextureName(NULL)
{
}

Gn2DTextureAni::TextureAniInfo::~TextureAniInfo()
{
	if( mTextureName  )
		GnFree( mTextureName );
}

void Gn2DTextureAni::TextureAniInfo::LoadStream(GnStream* pStream)
{
	GnAnimation::AniInfo::LoadStream( pStream );

	pStream->LoadStream( mTextureName );
}

void Gn2DTextureAni::TextureAniInfo::SaveStream(GnStream* pStream)
{
	GnAnimation::AniInfo::SaveStream( pStream );

	pStream->SaveStream( mTextureName );
}

GnImplementRTTI(Gn2DTextureAni, GnAnimation);

GnImplementCreateObject(Gn2DTextureAni);
void Gn2DTextureAni::LoadStream(GnObjectStream* pStream)
{
	GnAnimation::LoadStream( pStream );

	guint16 size = 0;
	pStream->LoadStream( size );
	mInfos.SetSize( (gtuint)size, 1 );

	for( gtuint i = 0 ; i < (gtuint)size ; i++)
	{
		TextureAniInfo* info = GnNew TextureAniInfo();
		info->LoadStream( pStream );
		mInfos.SetAt( i, info );
	}
	CreateData();
}

void Gn2DTextureAni::LinkObject(GnObjectStream* pStream)
{
	GnAnimation::LinkObject( pStream );
}

void Gn2DTextureAni::SaveStream(GnObjectStream* pStream)
{
	GnAnimation::SaveStream( pStream );

	guint16 size = (guint16)mInfos.GetSize();
	pStream->SaveStream( size );

	for( gtuint i = 0 ; i < (gtuint)size ; i++)
	{
		mInfos.GetAt( i )->SaveStream( pStream );
	}
}

void Gn2DTextureAni::RegisterSaveObject(GnObjectStream* pStream)
{
	GnAnimation::RegisterSaveObject( pStream );
}

Gn2DTextureAni::Gn2DTextureAni() : mpAnimate(NULL)
{	
}

Gn2DTextureAni::~Gn2DTextureAni()
{
	RemoveData();
}

bool Gn2DTextureAni::CreateData()
{
	if( mpAnimate )
		return true;

	CCMutableArray<CCSpriteFrame*> animFrames( mInfos.GetSize() );		
	float aniTime = 0.1f;
	for( gtuint i = 0 ; i < mInfos.GetSize() ; i++ )
	{
		TextureAniInfo* info = (TextureAniInfo*)(AniInfo*)mInfos.GetAt( i );

		gchar textureWorkPath[GN_MAX_PATH] = { 0, };
		GnStrcpy( textureWorkPath, GnSystem::GetWorkDirectory(), sizeof(textureWorkPath) );
		GnStrcat( textureWorkPath, info->GetTextureName(), sizeof(textureWorkPath) );
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(
			textureWorkPath );

		if( texture == NULL )
		{
			texture = CCTextureCache::sharedTextureCache()->addImage(
				info->GetTextureName() );
		}
		if( texture )
		{
			CCSize size = texture->getContentSize();
			CCRect rect( 0,0, size.width, size.height );
			CCSpriteFrame* frame =
				CCSpriteFrame::frameWithTexture( texture, rect );
			animFrames.addObject( frame );
			aniTime = info->GetEndTime();
		}
		else
		{
			return false;
		}
	}

	CCAnimation* animation = CCAnimation::animationWithFrames( &animFrames, aniTime );
	mpAnimate = CCAnimate::actionWithAnimation( animation, false );

	mpAnimate->retain(); // 에니가 끝나면 자동으로 삭제되는 것을 방지
	SetCreateData( true );
	return true;
}

void Gn2DTextureAni::RemoveData()
{
	if( mpAnimate )
	{
		if( Get2DMeshObject() )
		{
			GnReal2DMesh* mesh = Get2DMeshObject()->GetMesh();
			mesh->stopAction( mpAnimate );
		}
		mpAnimate->release();
	}
	mpAnimate = NULL;
	SetCreateData( false );
}

void Gn2DTextureAni::Start(float fTime)
{
	GnAssert( Get2DMeshObject() );
	if( mpAnimate == NULL )
	{
		if( CreateData() == false )
			return;
	}	
	
	GnAssert( mpAnimate );
	mpAnimate->setDuration( fTime );

	GnReal2DMesh* mesh = Get2DMeshObject()->GetMesh();
	mesh->runAction( mpAnimate );
	//mesh->setScale( 0.5f );
}

void Gn2DTextureAni::Stop()
{
	GnAssert( Get2DMeshObject() );
	GnReal2DMesh* mesh = Get2DMeshObject()->GetMesh();
	mesh->stopAction( mpAnimate );
}