#include "GnMeshPCH.h"
#include "Gn2DNode.h"

GnImplementRTTI(Gn2DNode, Gn2DMeshObject);

Gn2DNode::Gn2DNode(gtuint uiChildSize /*= 0*/) : mChildern(uiChildSize, 10)
{

}

void Gn2DNode::Update(float fTime)
{
	Gn2DMeshObject::Update( fTime );
	Gn2DMeshObject* pChild = NULL;
	for( gtuint i = 0 ; i < mChildern.GetSize() ; i++ )
	{
		pChild = mChildern.GetAt(i);
		if( pChild )
		{
			pChild->Update( fTime );
		}
	}
}

//void Gn2DNode::UpdateRect(bool bUpdateMeshData)
//{
//	Gn2DMeshObject* pChild = NULL;
//	for( gtuint i = 0 ; i < mChildern.GetSize() ; i++ )
//	{
//		pChild = mChildern.GetAt(i);
//		if( pChild )
//		{
//			pChild->UpdateRect( bUpdateMeshData );
//		}
//	}
//}

void Gn2DNode::AttachChild(Gn2DMeshObject* pObject)
{
	if( pObject == NULL )
		return;

	pObject->AttachParent(this);
	mChildern.Add(pObject);
}

Gn2DMeshObjectPtr Gn2DNode::DetachChild(Gn2DMeshObject* pChild)
{
	for( gtuint i = 0 ; i < mChildern.GetSize() ; i++ )
	{
		Gn2DMeshObjectPtr object = mChildern.GetAt(i);
		if( object && object == pChild )
		{
			object->DetachParent();
			mChildern.RemoveAt(i);
			return object;
		}
	}

	return NULL;
}

Gn2DMeshObjectPtr Gn2DNode::DetachChildAt(gtuint uiIndex)
{
	if( uiIndex < mChildern.GetSize() )
	{
		Gn2DMeshObjectPtr object = mChildern.GetAt(uiIndex);
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

GnObjectForm* Gn2DNode::GetObjectByName(const GnSimpleString& strName)
{
	GnObjectForm* getObject = Gn2DMeshObject::GetObjectByName(strName);
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

GnImplementCreateObject(Gn2DNode);
void Gn2DNode::LoadStream(GnObjectStream* pStream)
{
	Gn2DMeshObject::LoadStream( pStream );

	pStream->LoadMultipleLinkIDs();
}

void Gn2DNode::LinkObject(GnObjectStream* pStream)
{
	Gn2DMeshObject::LinkObject( pStream );

	guint32 size = pStream->GetNumberOfLinkIDs();
	if( size )
	{
		mChildern.SetSize( size );
		for( guint32 i = 0 ; i < size ; i++ )
		{
			Gn2DMeshObject* obj = (Gn2DMeshObject*)pStream->GetObjectFromLinkID();
			mChildern.SetAt( i, obj );
		}
	}
}

void Gn2DNode::SaveStream(GnObjectStream* pStream)
{
	Gn2DMeshObject::SaveStream( pStream );

	guint32 childCount = mChildern.GetSize();
	pStream->SaveStream( childCount );

	for( gtuint i = 0 ; i < childCount ; i++ )
	{
		Gn2DMeshObject* object = mChildern.GetAt(i);
		if( object )
			pStream->SaveLinkID( object );
	}
}

void Gn2DNode::RegisterSaveObject(GnObjectStream* pStream)
{
	Gn2DMeshObject::RegisterSaveObject( pStream );

	for( gtuint i = 0 ; i < mChildern.GetSize() ; i++ )
	{
		Gn2DMeshObject* object = mChildern.GetAt(i);
		if( object )
			object->RegisterSaveObject( pStream );
	}
}