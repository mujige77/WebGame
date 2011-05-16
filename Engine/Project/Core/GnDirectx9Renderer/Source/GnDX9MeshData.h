#ifndef GNDX9DATASTREAM_H
#define GNDX9DATASTREAM_H

#include "GnMeshData.h"

class GnDX9DataStream;
class GNDIRECTX9RENDERER_ENTRY GnDX9MeshData : public GnMeshData
{
protected:
	enum
	{
		MAX_DECLARATION_SIZE = 10,
	};
protected:
	LPDIRECT3DVERTEXDECLARATION9 mpDeclaration;
	
public:
	GnDX9MeshData();
	virtual ~GnDX9MeshData();

	virtual GnDataStream* CreateDataStream(GnDataStream::eFormat format, guint32 vertexCount);
	// IsChangedDataStream가 true면 GnDataStream의 버퍼만 다시 만들고
	// IsAddDataStream이 true이면 LPDIRECT3DVERTEXDECLARATION9다시 생성하고 GnDataStream의 버퍼도 다시 만든다
	virtual void UpdateData();

	inline LPDIRECT3DVERTEXDECLARATION9 GetDeclaration() const { return mpDeclaration; }
	

protected:
	// 데이터 스트림을 토대로 
	bool GetVertexElement9(GnDX9DataStream* pDataStream, D3DVERTEXELEMENT9& outVertexElement);

};

#endif // GNDX9DATASTREAM_H