#include "GnMeshPCH.h"
#include "GnMesh.h"
GnImplementRTTI(GnMesh, GnRenderObject);

GnMesh::GnMesh(GnTransform* pTrans) : GnRenderObject(pTrans)
{
	if( mpTransform == NULL )
		mpTransform = GnNew Gn3DTransform();
}

GnMesh::~GnMesh()
{
	GnDelete mpMeshData;
}

guint32 GnMesh::GetPrimitiveCount(gtuint numVertexCount)
{
	guint32 primitiveCount = 0;
	switch (mPrimitiveType)
	{
	case GnMesh::PRIMITIVE_TRISTRIPS:
		primitiveCount = numVertexCount - 2; 
		break;
	case GnMesh::PRIMITIVE_TRIANGLES: 
		primitiveCount = numVertexCount / 3; 
		break;
	case GnMesh::PRIMITIVE_LINES:
		primitiveCount = numVertexCount >> 1; // div 2
		break;
	case GnMesh::PRIMITIVE_LINESTRIPS:
		primitiveCount = numVertexCount - 1;
		break;
	case GnMesh::PRIMITIVE_POINTS:
		primitiveCount = numVertexCount; 
		break;
	case GnMesh::PRIMITIVE_QUADS:
		primitiveCount = numVertexCount >> 2; // div 4
		break;
	default:
		break;
	}
	return primitiveCount;
}

GnImplementCreateObject(GnMesh);
void GnMesh::LoadStream(GnObjectStream* pStream)
{
	GnRenderObject::LoadStream( pStream );

	pStream->LoadStream( mNumVertex );
	gshort primitiveType;
	pStream->LoadStream( primitiveType );
	mPrimitiveType = (ePrimitiveType)primitiveType;
	pStream->LoadLinkID();
}

void GnMesh::LinkObject(GnObjectStream* pStream)
{
	GnRenderObject::LinkObject( pStream );
	mpMeshData = (GnMeshData*)pStream->GetObjectFromLinkID();
}

void GnMesh::SaveStream(GnObjectStream* pStream)
{
	GnRenderObject::SaveStream( pStream );
	
	pStream->SaveStream( mNumVertex );
	gshort primitiveType = (gshort)mPrimitiveType;
	pStream->SaveStream( primitiveType );
	pStream->SaveLinkID( mpMeshData );
}

void GnMesh::RegisterSaveObject(GnObjectStream* pStream)
{
	GnRenderObject::RegisterSaveObject( pStream );
	mpMeshData->RegisterSaveObject( pStream );
}
