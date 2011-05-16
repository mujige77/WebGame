#include "GnMainPCH.h"
#include "GnNode.h"

GnImplementRTTI(GnNode, GnAVObject);
GnNode::GnNode(gtuint uiChildSize, GnTransform* pTrans) : GnAVObject(pTrans), mChildern(uiChildSize)
{

}

GnNode::~GnNode()
{

}

void GnNode::AttachChild(GnAVObject* pObject)
{
	if( pObject == NULL )
		return;

	pObject->AttachParent(this);
	mChildern.Add(pObject);
}

GnAVObjectPtr GnNode::DetachChild(GnAVObject* pChild)
{
	for( gtuint i = 0 ; i < mChildern.GetSize() ; i++ )
	{
		GnAVObject* object = mChildern.GetAt(i);
		if( object && object == pChild )
		{
			object->DetachParent();
			mChildern.RemoveAt(i);
			return object;
		}
	}

	return NULL;
}

GnAVObjectPtr GnNode::DetachChildAt(gtuint uiIndex)
{
	if( uiIndex < mChildern.GetSize() )
	{
		GnAVObject* object = mChildern.GetAt(uiIndex);
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

GnAVObject* GnNode::GetObjectByName(const GnSimpleString& strName)
{
	GnObjectForm* getObject = GnAVObject::GetObjectByName(strName);
	if( getObject )
		return (GnAVObject*)getObject;
	 
	GnAVObject* pChild = NULL;
	for( gtuint i = 0 ; i < mChildern.GetSize() ; i++ )
	{
		pChild = mChildern.GetAt(i);
		if( pChild )
		{
			getObject = pChild->GetObjectByName(strName);
			if( getObject )
				return (GnAVObject*)getObject;
		}
	}
	return NULL;
}

void GnNode::Update(float fTime)
{
	for( gtuint i = 0 ; i < mChildern.GetSize() ; i++ )
	{
		GnAVObject* object = mChildern.GetAt(i);
		if( object )
			object->Update( fTime );
	}
}


GnImplementCreateObject(GnNode);
void GnNode::LoadStream(GnObjectStream* pStream)
{
	GnAVObject::LoadStream( pStream );

	pStream->LoadMultipleLinkIDs();
}

void GnNode::LinkObject(GnObjectStream* pStream)
{
	GnAVObject::LinkObject( pStream );

	guint32 size = pStream->GetNumberOfLinkIDs();
	if( size )
	{
		mChildern.SetSize( size );
		for( guint32 i = 0 ; i < size ; i++ )
		{
			GnAVObject* obj = (GnAVObject*)pStream->GetObjectFromLinkID();
			mChildern.SetAt( i, obj );
		}
	}
}

void GnNode::SaveStream(GnObjectStream* pStream)
{
	GnAVObject::SaveStream( pStream );

	guint32 childCount = mChildern.GetSize();
	pStream->SaveStream( childCount );

	for( gtuint i = 0 ; i < childCount ; i++ )
	{
		GnAVObject* object = mChildern.GetAt(i);
		if( object )
			object->SaveStream( pStream );
	}
}

void GnNode::RegisterSaveObject(GnObjectStream* pStream)
{
	GnAVObject::RegisterSaveObject( pStream );

	for( gtuint i = 0 ; i < mChildern.GetSize() ; i++ )
	{
		GnAVObject* object = mChildern.GetAt(i);
		if( object )
			object->RegisterSaveObject( pStream );
	}
}
