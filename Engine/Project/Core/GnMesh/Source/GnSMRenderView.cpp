#include "GnMeshPCH.h"
#include "GnSMRenderView.h"

void GnSMRenderView::AddToPVGeometryArray(GnObjectForm* pObject)
{
	//if( Gn2DNode* group = GnDynamicCast(Gn2DNode, pObject) )
	//{
	//	if( group->GetMesh() && group->IsVisible() )
	//		mCollactRenderObject.Add( group->GetMesh() );

	//	for( gtuint i = 0 ; i < group->GetChildCount() ; i++ )
	//	{
	//		Gn2DMeshObject* childObject = group->GetAt(i);
	//		AddToPVGeometryArray(childObject);
	//	}
	//}
	//else 	if( Gn2DMeshObject* element = GnDynamicCast(Gn2DMeshObject, pObject) ) 
	//{
	//	if( element->GetMesh() && element->IsVisible() )
	//	{
	//		mCollactRenderObject.Add( element->GetMesh() );
	//	}
	//}
}

void GnSMRenderView::Update(float fTime)
{
	GnListIterator<GnObjectFormPtr> iter = mList.GetIterator();
	while( iter.Valid() )
	{
		GnObjectForm* object = iter.Item();
		if( object )
		{
			((Gn2DMeshObject*)object)->Update(fTime);
		}

		iter.Forth();
	}
}