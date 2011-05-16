#include "GnMainPCH.h"
#include "GnRenderView.h"

GnRenderView::GnRenderView()
{
	SetActive(true);
}

GnRenderView::~GnRenderView()
{

}

void GnRenderView::Render()
{
	GnRenderer* pkRenderer = GnRenderer::GetRenderer();
	GnAssert(pkRenderer);

	mCollactRenderObject.RemoveAll();

	GnListIterator<GnObjectFormPtr> iter = mList.GetIterator();
	while( iter.Valid() )
	{
		GnObjectForm* object = iter.Item();
		if( object )
			AddToPVGeometryArray( object );

		iter.Forth();
	}

	for( gtuint i = 0 ; i < mCollactRenderObject.GetCount() ; i++ )
	{
		GnRenderObject* object = mCollactRenderObject.GetAt(i);
		if( object )
			object->RnderObject(pkRenderer);
	}
}

void GnRenderView::AddToPVGeometryArray(GnObjectForm* pObject)
{
	if( GnRenderObject* renderObject = GnDynamicCast(GnRenderObject, pObject) ) 
	{
		mCollactRenderObject.Add(renderObject);
	}
	else if( GnNode* node = GnDynamicCast(GnNode, pObject) )
	{
		for( gtuint i = 0 ; i < node->GetChildCount() ; i++ )
		{
			GnAVObject* childObject = node->GetAt(i);
			AddToPVGeometryArray(childObject);
		}
	}
}

void GnRenderView::Update(float fTime)
{
	GnListIterator<GnObjectFormPtr> iter = mList.GetIterator();
	while( iter.Valid() )
	{
		GnObjectForm* object = iter.Item();
		if( object )
		{
			((GnAVObject*)object)->Update(fTime);
		}

		iter.Forth();
	}
}