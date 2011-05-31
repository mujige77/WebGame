#include "GnMeshPCH.h"
#include "Gn2DMeshObject.h"

template<class newObject>
class GnObjectNew
{
public:
	template<class V1>
	static newObject* Create(V1 val1)
	{
		return new newObject( val1 );
	}

	static newObject* Create()
	{
		return new newObject();
	}

	static void Delete(newObject* pObject)
	{
		delete pObject;
	}
};

GnImplementRTTI( Gn2DMeshObject, GnObjectForm );
Gn2DMeshObject::Gn2DMeshObject() : mpParent(NULL)
{
	mpMesh = GnObjectNew<GnReal2DMesh>::Create();
	SetVisible( true );
}

Gn2DMeshObject::~Gn2DMeshObject()
{
	if( mpMesh )
		mpMesh->release();
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
	}
}

void Gn2DMeshObject::AttachParent(Gn2DMeshObject* pParent)
{
	if( mpParent )
		mpParent->DetachChild( this );

	mpParent = pParent;
}

void Gn2DMeshObject::Update(float fTime)
{
}

GnObjectForm* Gn2DMeshObject::GetObjectByName(const GnSimpleString& kName)
{
	if( kName.Exists() && GetName() == kName )
		return this;

	return NULL;
}

GnImplementCreateObject(Gn2DMeshObject);
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