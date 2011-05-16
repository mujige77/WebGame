#ifndef GNMESH_H
#define GNMESH_H
#include "GnMeshData.h"

class GNMESH_ENTRY GnMesh : public GnRenderObject
{
	GnDeclareRTTI;
	GnDeclareStream;
public:
	enum ePrimitiveType
	{
		PRIMITIVE_TRIANGLES,
		PRIMITIVE_TRISTRIPS,
		PRIMITIVE_LINES,
		PRIMITIVE_LINESTRIPS,
		PRIMITIVE_QUADS,
		PRIMITIVE_POINTS,
	};

protected:
	GnMeshData* mpMeshData;
	guint32 mNumVertex;
	ePrimitiveType mPrimitiveType;

public:
	virtual ~GnMesh();

	guint32 GetPrimitiveCount(gtuint numVertexCount);

	virtual void RnderObject(GnRenderer* pRenderer){};

	inline void AddDataStream(GnDataStream::eFormat format, gtuint uiVertexCount)
	{
		mpMeshData->AddDataStream(format, uiVertexCount);
	}

	inline guint32 GetNumVertex()
	{
		return mNumVertex;
	}

	inline GnMeshData* GetMeshData()
	{
		return mpMeshData;
	}
	inline GnMesh::ePrimitiveType GetPrimitiveType()
	{
		return mPrimitiveType;
	}
	inline void SetPrimitiveType(GnMesh::ePrimitiveType val)
	{
		mPrimitiveType = val;
	}

protected:	
	GnMesh(GnTransform* pTrans = NULL);
};

#endif // GNMESH_H