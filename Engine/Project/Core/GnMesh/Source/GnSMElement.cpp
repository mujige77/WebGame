#include "GnMeshPCH.h"
#include "GnSMElement.h"

GnImplementRTTI( GnSMElement, GnObjectForm );
GnSMElement::GnSMElement() : mpParent(NULL)
{
	SetVisible( true );
}

void GnSMElement::SetMesh(GnScreenMesh* pMesh, GnIRect iRect)
{
	SetMesh( pMesh );
	SetDisplayRect( iRect );
	UpdateRect( true );
}

void GnSMElement::SetMesh(GnScreenMesh* pMesh)
{
	mpsMesh = pMesh;
}

void GnSMElement::SetDisplayRect(GnIRect& val)
{
	mDisplayRect = val;
}

void GnSMElement::AttachParent(GnSMElement* pParent)
{
	if( mpParent )
		mpParent->DetachChild( this );

	mpParent = pParent;
}

void GnSMElement::Update(float fTime)
{
	if( mpsMesh )
		mpsMesh->Update( fTime );
}

void GnSMElement::UpdateRect(bool bUpdateMeshData)
{
	GnVerify( GnSMManager::GetSingleton()->ConvertToVertexRect( mDisplayRect, mMeshRect ) );
	if( bUpdateMeshData )
	{
		mpsMesh->SetRectangle( 0, mMeshRect.left, mMeshRect.top, mMeshRect.right, mMeshRect.bottom );
	}
}

GnObjectForm* GnSMElement::GetObjectByName(const GnSimpleString& kName)
{
	if( kName.Exists() && GetName() == kName )
		return this;
	if( mpsMesh )
		return mpsMesh->GetObjectByName( kName );
	return NULL;
}

GnImplementCreateObject(GnSMElement);
void GnSMElement::LoadStream(GnObjectStream* pStream)
{
	GnObjectForm::LoadStream( pStream );

	mDisplayRect.LoadStream( pStream );
	pStream->LoadLinkID();
}

void GnSMElement::LinkObject(GnObjectStream* pStream)
{
	GnObjectForm::LinkObject( pStream );

	mpsMesh = (GnScreenMesh*)pStream->GetObjectFromLinkID();
}

void GnSMElement::SaveStream(GnObjectStream* pStream)
{
	GnObjectForm::SaveStream( pStream );
	
	mDisplayRect.SaveStream( pStream );
	pStream->SaveLinkID( mpsMesh );
}

void GnSMElement::RegisterSaveObject(GnObjectStream* pStream)
{
	GnObjectForm::RegisterSaveObject( pStream );

	if( mpsMesh )
		mpsMesh->RegisterSaveObject( pStream );
}

