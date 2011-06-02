#include "StdAfx.h"
#include "GtCollisionModify.h"
#include "GnLayer.h"


GtCollisionModify::GtCollisionModify(void)
{
}


GtCollisionModify::~GtCollisionModify(void)
{
	GetSceneManager()->GetMainGameLayer()->removeChild( mpDrawLayer, true );
	mpDrawLayer->release();
}

GtCollisionModify* GtCollisionModify::Create(float fWidth, float fHeight)
{
	GnLayerDrawPrimitives* drawLayer = new GnLayerDrawPrimitives;	
	drawLayer->setColor( ccc3(0,0,255) );
	drawLayer->setOpacity( 150 );
	drawLayer->setContentSize( CCSizeMake(fWidth, fHeight) );
	drawLayer->setIsVisible( false );
	GetSceneManager()->GetMainGameLayer()->addChild( drawLayer, 100, 1 );

	GtCollisionModify* thisVal = new GtCollisionModify;
	thisVal->mpDrawLayer = drawLayer;
	return thisVal;
}

bool GtCollisionModify::LoadBasicActor(const char* pcFilePath)
{
	GnObjectStream objStream;
	mpsBasicCollisionActor = Gn2DActor::Create( pcFilePath, objStream, false );
	if( mpsBasicCollisionActor )
		return true;

	if( mpsBasicMeshObject )
	{
		GetSceneManager()->GetMainGameLayer()->RemoveChild( mpsBasicMeshObject );
		mpsBasicMeshObject = NULL;
	}
	MessageBoxA( NULL, "gat파일이 존재 하지 않습니다. 먼저 파일을  저장해주세요", "error", MB_OK );
	return false;
}

void GtCollisionModify::SetBasicSequenceID(guint32 uiID)
{
	if( mpsBasicCollisionActor == NULL )
		return;
	
	mpsBasicCollisionActor->SetTargetAnimation( uiID );
	mpsBasicCollisionActor->Update( 0.0f );
	Gn2DSequence* sequence = NULL;
	if( mpsBasicCollisionActor->GetSequence( uiID, sequence ) == false )
	{
		if( mpsBasicMeshObject )
		{
			GetSceneManager()->GetMainGameLayer()->RemoveChild( mpsBasicMeshObject );
			mpsBasicMeshObject = NULL;
		}
		MessageBoxA( NULL, "1번 애니메이션이 존재 하지 않습니다. 기본이 되는 캐릭터를 그릴 수 없습니다"
			, "error", MB_OK );
		return;
	}

	gtuint size = sequence->GetTextureAnis().GetSize();
	if( size == NULL )
		return;

	Gn2DTextureAni* ani = sequence->GetTextureAnis().GetAt( 0 );
	if( ani->GetAniInfoCount() <= 0 )
		return;

	Gn2DTextureAni::TextureAniInfo* aniInfo = (Gn2DTextureAni::TextureAniInfo*)ani->GetAniInfo( 0 );
	if( aniInfo == NULL || aniInfo->GetTextureName() == NULL )
		return;
	
	if( mpDrawLayer->getIsVisible() && mpsBasicMeshObject )
		GetSceneManager()->GetMainGameLayer()->RemoveChild( mpsBasicMeshObject );

	mpsBasicMeshObject = Gn2DMeshObject::CreateFromTextureFile( aniInfo->GetTextureName() );
	if( mpsBasicMeshObject == NULL )
	{
		GnAssert(mpsBasicMeshObject);
		return;
	}	
	mpsBasicMeshObject->SetAVData( sequence->GetAVData() );
	mpsBasicMeshObject->GetMesh()->setOpacity( 255 );
	mpsBasicMeshObject->GetMesh()->setColor( ccc3( 0, 255 , 255 ) );
}

void GtCollisionModify::SetVisible(bool val, Gn2DMeshObject* pMesh)
{
	mpDrawLayer->setIsVisible( val );

	if( val )
	{
		GnAssert( pMesh );
		if( mpsDrawSequenceRect )
			mpDrawLayer->RemoveChild( mpsDrawSequenceRect );

		GnDraw2DObjectRect* drawObject = GtObjectNew<GnDraw2DObjectRect>::Create();
		drawObject->SetThickness( 3.0f );
		drawObject->SetColor( GnColorA(1.0f, 1.0f, 0.0f, 1.0f) );
		drawObject->SetObject( pMesh );
		mpDrawLayer->AddChild( drawObject );
		mpsDrawSequenceRect = drawObject;

		if( mpsBasicMeshObject )
		{
			GetSceneManager()->GetMainGameLayer()->AddChild( mpsBasicMeshObject, mZrOder );
		}
	}
	else
	{
		if( mpsDrawSequenceRect )
			mpDrawLayer->RemoveChild( mpsDrawSequenceRect );

		if( mpsBasicMeshObject )
		{
			GetSceneManager()->GetMainGameLayer()->RemoveChild( mpsBasicMeshObject );
			mpsBasicMeshObject = NULL;
		}
	}
}

void GtCollisionModify::SetScale(float val)
{
	if( mpsBasicMeshObject )
		mpsBasicMeshObject->SetScale( val );
}