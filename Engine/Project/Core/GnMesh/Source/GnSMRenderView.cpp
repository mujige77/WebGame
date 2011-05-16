#include "GnMeshPCH.h"
#include "GnSMRenderView.h"

void GnSMRenderView::AddToPVGeometryArray(GnObjectForm* pObject)
{
	if( GnSMGroup* group = GnDynamicCast(GnSMGroup, pObject) )
	{
		if( group->GetMesh() && group->IsVisible() )
			mCollactRenderObject.Add( group->GetMesh() );

		for( gtuint i = 0 ; i < group->GetChildCount() ; i++ )
		{
			GnSMElement* childObject = group->GetAt(i);
			AddToPVGeometryArray(childObject);
		}
	}
	else 	if( GnSMElement* element = GnDynamicCast(GnSMElement, pObject) ) 
	{
		if( element->GetMesh() && element->IsVisible() )
		{
			mCollactRenderObject.Add( element->GetMesh() );
		}
	}
}

void GnSMRenderView::Update(float fTime)
{
	GnListIterator<GnObjectFormPtr> iter = mList.GetIterator();
	while( iter.Valid() )
	{
		GnObjectForm* object = iter.Item();
		if( object )
		{
			((GnSMElement*)object)->Update(fTime);
		}

		iter.Forth();
	}
}