#include "GnDirectx9RendererPCH.h"
#include "GnDX9MeshData.h"
#include "GnDX9DataStream.h"
#include "GnDataStreamLockPolicy.h"

GnDX9MeshData::GnDX9MeshData() : mpDeclaration(NULL)
{
}

GnDX9MeshData::~GnDX9MeshData()
{
	GnDxRelease(mpDeclaration);
}

GnDataStream* GnDX9MeshData::CreateDataStream(GnDataStream::eFormat format, guint32 vertexCount)
{
	return GnNew NiDX9LockableDataStream<GnDataStreamLockPolicy<GnDX9DataStream>>(format, vertexCount);
}

void GnDX9MeshData::UpdateData()
{
	if( IsAddDataStream() )
	{
		GnAssert( MAX_DECLARATION_SIZE > mDataStreams.GetCount() );
		D3DVERTEXELEMENT9 declarations[MAX_DECLARATION_SIZE];

		D3DVERTEXELEMENT9 endDecl[] = { D3DDECL_END() };
		declarations[mDataStreams.GetCount()] = endDecl[0];

		gtuint numDecl = 0;
		GnListIterator<GnDataStream*> iter = mDataStreams.GetIterator();
		while ( iter.Valid() )
		{
			GnDX9DataStream* data = (GnDX9DataStream*)iter.Item();
			if( GetVertexElement9(data, declarations[numDecl++]) == false )
			{
				GnAssert(false);
				continue;
			}
			data->MakeBuffer();
			iter.Forth();
		}

		GnDirectx9Renderer* renderer = GnDirectx9Renderer::GetRenderer();
		GnAssert(renderer);
		LPDIRECT3DDEVICE9 device = renderer->GetDevice();

		GnDxRelease(mpDeclaration);
		device->CreateVertexDeclaration( declarations, &mpDeclaration );

		SetAddDataStream(false);
		
	}
	else
	{
		GnListIterator<GnDataStream*> iter = mDataStreams.GetIterator();
		while ( iter.Valid() )
		{
			GnDX9DataStream* data = (GnDX9DataStream*)iter.Item();		
			data->MakeBuffer();
			iter.Forth();
		}
	}
}

bool GnDX9MeshData::GetVertexElement9(GnDX9DataStream* pDataStream, D3DVERTEXELEMENT9& outVertexElement)
{
	D3DDECLTYPE eD3DType;
	D3DDECLUSAGE eD3DUsage;

	if( pDataStream->GetD3DDeclType( eD3DType ) == false || pDataStream->GetD3DDeclUsage( eD3DUsage ) == false )
		return false;

	outVertexElement.Stream = pDataStream->GetNumStream();     // Stream index
	outVertexElement.Offset = 0;//pDataStream->GetOffset();     // Offset in the stream in bytes
	outVertexElement.Type = eD3DType;       // Data type
	outVertexElement.Method = D3DDECLMETHOD_DEFAULT;     // Processing method
	outVertexElement.Usage = eD3DUsage;      // Semantics
	outVertexElement.UsageIndex = pDataStream->GetUsageIndex(); // Semantic index

	return true;
}