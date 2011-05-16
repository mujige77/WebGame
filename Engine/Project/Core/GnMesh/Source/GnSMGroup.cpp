#include "GnMeshPCH.h"
#include "GnSMGroup.h"

GnImplementRTTI(GnSMGroup, GnSMElement);

GnSMGroup::GnSMGroup(gtuint uiChildSize /*= 0*/) : mChildern(uiChildSize, 10)
{

}

void GnSMGroup::Update(float fTime)
{
	GnSMElement::Update( fTime );
	GnSMElement* pChild = NULL;
	for( gtuint i = 0 ; i < mChildern.GetSize() ; i++ )
	{
		pChild = mChildern.GetAt(i);
		if( pChild )
		{
			pChild->Update( fTime );
		}
	}
}

void GnSMGroup::UpdateRect(bool bUpdateMeshData)
{
	GnSMElement* pChild = NULL;
	for( gtuint i = 0 ; i < mChildern.GetSize() ; i++ )
	{
		pChild = mChildern.GetAt(i);
		if( pChild )
		{
			pChild->UpdateRect( bUpdateMeshData );
		}
	}
}

void GnSMGroup::AttachChild(GnSMElement* pObject)
{
	if( pObject == NULL )
		return;

	pObject->AttachParent(this);
	mChildern.Add(pObject);
}

GnSMElementPtr GnSMGroup::DetachChild(GnSMElement* pChild)
{
	for( gtuint i = 0 ; i < mChildern.GetSize() ; i++ )
	{
		GnSMElementPtr object = mChildern.GetAt(i);
		if( object && object == pChild )
		{
			object->DetachParent();
			mChildern.RemoveAt(i);
			return object;
		}
	}

	return NULL;
}

GnSMElementPtr GnSMGroup::DetachChildAt(gtuint uiIndex)
{
	if( uiIndex < mChildern.GetSize() )
	{
		GnSMElementPtr object = mChildern.GetAt(uiIndex);
		if( object )
		{
			object->DetachParent();
			mChildern.RemoveAt(uiIndex);
		}
		return object;
	}
	else
	{
		return NULL;
	}
}

GnObjectForm* GnSMGroup::GetObjectByName(const GnSimpleString& strName)
{
	GnObjectForm* getObject = GnSMElement::GetObjectByName(strName);
	if( getObject )
		return getObject;

	GnObjectForm* pChild = NULL;
	for( gtuint i = 0 ; i < mChildern.GetSize() ; i++ )
	{
		pChild = mChildern.GetAt(i);
		if( pChild )
		{
			getObject = pChild->GetObjectByName(strName);
			if( getObject )
				return getObject;
		}
	}
	return NULL;
}

GnImplementCreateObject(GnSMGroup);
void GnSMGroup::LoadStream(GnObjectStream* pStream)
{
	GnSMElement::LoadStream( pStream );

	pStream->LoadMultipleLinkIDs();
}

void GnSMGroup::LinkObject(GnObjectStream* pStream)
{
	GnSMElement::LinkObject( pStream );

	guint32 size = pStream->GetNumberOfLinkIDs();
	if( size )
	{
		mChildern.SetSize( size );
		for( guint32 i = 0 ; i < size ; i++ )
		{
			GnSMElement* obj = (GnSMElement*)pStream->GetObjectFromLinkID();
			mChildern.SetAt( i, obj );
		}
	}
}

void GnSMGroup::SaveStream(GnObjectStream* pStream)
{
	GnSMElement::SaveStream( pStream );

	guint32 childCount = mChildern.GetSize();
	pStream->SaveStream( childCount );

	for( gtuint i = 0 ; i < childCount ; i++ )
	{
		GnSMElement* object = mChildern.GetAt(i);
		if( object )
			pStream->SaveLinkID( object );
	}
}

void GnSMGroup::RegisterSaveObject(GnObjectStream* pStream)
{
	GnSMElement::RegisterSaveObject( pStream );

	for( gtuint i = 0 ; i < mChildern.GetSize() ; i++ )
	{
		GnSMElement* object = mChildern.GetAt(i);
		if( object )
			object->RegisterSaveObject( pStream );
	}
}