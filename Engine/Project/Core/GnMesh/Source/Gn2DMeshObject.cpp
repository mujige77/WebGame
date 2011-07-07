#include "GnMeshPCH.h"
#include "Gn2DMeshObject.h"
#include "Gn2DMeshData.h"
GnImplementRTTI( Gn2DMeshObject, GnObjectForm );
Gn2DMeshObject::Gn2DMeshObject() : mpParent( NULL )
{
	mpMesh = new GnReal2DMesh;
	mpMesh->setScale( GetGameState()->GetGameScale() );
	SetVisible( true );
}

Gn2DMeshObject::Gn2DMeshObject(GnReal2DMesh* pMesh) : mpMesh( pMesh )
{
	mpMesh->setScale( GetGameState()->GetGameScale() );
}
Gn2DMeshObject::~Gn2DMeshObject()
{
	if( mpMesh )
		mpMesh->release();
}

Gn2DMeshObject* Gn2DMeshObject::CreateFromTextureFile(const gchar* pcFilePath)
{
	
	gchar textureWorkPath[GN_MAX_PATH] = { 0, };
	GnStrcpy( textureWorkPath, GnSystem::GetWorkDirectory(), sizeof(textureWorkPath) );
	GnStrcat( textureWorkPath, pcFilePath, sizeof(textureWorkPath) );
	GnReal2DMesh* mesh = CCSprite::spriteWithFile( textureWorkPath ); 
	if( mesh == NULL )
	{
		mesh = CCSprite::spriteWithFile( pcFilePath );
		if( mesh == NULL )
			return NULL;		
	}
	mesh->retain();
	Gn2DMeshObject* meshObject = GnNew Gn2DMeshObject( mesh );
	return meshObject;
}

void Gn2DMeshObject::SetMesh(GnReal2DMesh* pMesh)
{
	mpMesh = pMesh;
}

void Gn2DMeshObject::SetAVData(Gn2DAVData* val)
{
	mpsAVData = val;
	if( mpMesh && val )
	{
		mpMesh->setAnchorPoint( CCPointMake( val->GetAnchorPoint().x, val->GetAnchorPoint().y ) );
		SetPosition( GetPosition() );
		SetFlipX( mpMesh->isFlipX() );
	}
}

void Gn2DMeshObject::AttachParent(Gn2DMeshObject* pParent)
{
	if( mpParent )
		mpParent->DetachChild( this );

	mpParent = pParent;
}

void Gn2DMeshObject::SetScale(float val)
{
	mpMesh->setScale( val * GetGameState()->GetGameScale() );
}

void Gn2DMeshObject::SetPosition(GnVector2 val)
{
	SetOriginalPosition( val );
	if( GetAVData() )
	{
		if( mpMesh->isFlipX() )
		{
			val = GetOriginalPosition() - GetAVData()->GetImageCenter();
			mpMesh->setPosition( CCPointMake(val.x, val.y) );
		}
		else
		{			
			mpMesh->setPosition( CCPointMake(val.x, val.y) );
		}
		GetAVData()->Move( GetOriginalPosition() );
	}
	else
	{
		mpMesh->setPosition( CCPointMake(val.x, val.y) );
	}
}

void Gn2DMeshObject::SetFlipX(bool val)
{
	mpMesh->setFlipX( val );
	SetPosition( GetOriginalPosition() );
	if( GetAVData() )
	{
		if( val )
		{
			GetAVData()->FlipX( val, GetOriginalPosition().x );
		}
		else
		{			
			GetAVData()->FlipX( val, GetOriginalPosition().x );
		}
	}	
	//if( mpsAVData )
	//{
	//	if( mpMesh->isFlipX() )
	//	{
	//		mpMesh->setPosition( GetOriginalPosition() - GetAVData()->GetAnchorPoint() );
	//	}
	//	else
	//	{
	//		mpMesh->setPosition( GetOriginalPosition() + GetAVData()->GetAnchorPoint() );
	//	}
	//}
}

void Gn2DMeshObject::Update(float fTime)
{
	GnObjectForm::Update( fTime );
}

GnObjectForm* Gn2DMeshObject::GetObjectByName(const GnSimpleString& kName)
{
	if( kName.Exists() && GetName() == kName )
		return this;

	return NULL;
}

GnObject* Gn2DMeshObject::CreateObject()
{
	Gn2DMeshObject* object = GnNew Gn2DMeshObject(new Gn2DMeshData() );
	GnAssert(object != NULL);
	return object;
}

void Gn2DMeshObject::LoadStream(GnObjectStream* pStream)
{
	GnObjectForm::LoadStream( pStream );

	pStream->LoadLinkID();
}

void Gn2DMeshObject::LinkObject(GnObjectStream* pStream)
{
	GnObjectForm::LinkObject( pStream );

	mpsAVData = (Gn2DAVData*)pStream->GetObjectFromLinkID();
}

void Gn2DMeshObject::SaveStream(GnObjectStream* pStream)
{
	GnObjectForm::SaveStream( pStream );

	if( mpsAVData && mpsAVData->IsMeshStream() )
		pStream->SaveLinkID( mpsAVData );
	else
		pStream->SaveLinkID( NULL );
}

void Gn2DMeshObject::RegisterSaveObject(GnObjectStream* pStream)
{
	GnObjectForm::RegisterSaveObject( pStream );

	if( mpsAVData->IsMeshStream() )
		mpsAVData->RegisterSaveObject( pStream );
}