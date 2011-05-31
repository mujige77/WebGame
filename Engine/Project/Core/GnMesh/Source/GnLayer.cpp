#include "GnMeshPCH.h"
#include "GnLayer.h"

void GnLayer::AddChild(Gn2DMeshObject* pObject, int iZOrder)
{
	addChild( pObject->GetMesh(), iZOrder );
}

void GnLayer::RemoveChild(Gn2DMeshObject* pObject)
{
	removeChild( pObject->GetMesh(), true );
}

GnLayerDrawPrimitives::GnLayerDrawPrimitives() : mDrawObjects(50, 50)
{

}

void GnLayerDrawPrimitives::draw()
{
	GnLayer::draw();
	for( gtuint i = 0 ; i < mDrawObjects.GetSize() ; i++ )
	{
		mDrawObjects.GetAt( i )->Draw();
	}
}

void GnLayerDrawPrimitives::AddChild(GnDrawPrimitives* pObject)
{
	mDrawObjects.Add( pObject );
}

void GnLayerDrawPrimitives::RemoveChild(GnDrawPrimitives* pObject)
{
	mDrawObjects.RemoveAndFill( pObject );
}