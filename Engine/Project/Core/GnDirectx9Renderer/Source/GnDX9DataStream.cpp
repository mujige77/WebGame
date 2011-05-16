#include "GnDirectx9RendererPCH.h"
#include "GnDX9DataStream.h"

GnDX9DataStream::GnDX9DataStream(const GnDataStream::eFormat format, guint32 uiCount) :
	GnDataStream(format, uiCount), mpVBBuffer(NULL)
{
	Allocate();	
}

GnDX9DataStream::~GnDX9DataStream()
{
	Deallocate();
}

gtuint GnDX9DataStream::GetStride(const GnDataStream::eFormat format)
{
	switch(format)
	{
	case GnDataStream::POSTION_STREAM:
		return 12;
	case GnDataStream::TEXTURE_STREAM:
		return 8;
	case GnDataStream::NORMAL_STREAM:
		return 12;
	case GnDataStream::COLOR_STREAM:
		return 4;
	}
	return GnDataStream::GetStride(format);
}

void* GnDX9DataStream::MapBuffer(guint8 uiLockType, gtuint uiReadLockCount, gtuint uiWriteLockCount)
{
	GnAssert(mpLocalBuffer);
	return mpLocalBuffer;
}

void GnDX9DataStream::UnmapBuffer(guint8 uiLockType, gtuint uiReadLockCount, gtuint uiWriteLockCount)
{
	if( mpLocalBuffer && uiLockType == GnDataStream::LOCK_WRITE )
	{
		mUnshaped = true;
	}
}

void GnDX9DataStream::Allocate()
{
	GnAssert(mpLocalBuffer == NULL);
	mpLocalBuffer = GnMalloc( GetBufferSize() );
}

void GnDX9DataStream::Deallocate()
{
	if( mpLocalBuffer )
	{
		GnFree(mpLocalBuffer);
		mpLocalBuffer = NULL;
	}
	DX9Deallocate();
}

void GnDX9DataStream::DX9Allocate()
{
	GnDirectx9Renderer* renderer = GnDirectx9Renderer::GetRenderer();
	GnAssert(renderer);
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	device->CreateVertexBuffer( GetBufferSize(), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &mpVBBuffer, NULL );
}

void GnDX9DataStream::DX9Deallocate()
{
	GnDxRelease(mpVBBuffer);
}

void GnDX9DataStream::MakeBuffer()
{
	if( mUnshaped )
	{
		if( mpVBBuffer == NULL )
			DX9Allocate();
		
		void* bufferData = DX9Lock(GnDataStream::LOCK_WRITE);
		memcpy( bufferData, mpLocalBuffer, GetBufferSize() );
		DX9Unlock();
		mUnshaped = false;
	}
}

void* GnDX9DataStream::DX9Lock(guint8 uiLockMask)
{
	GnAssert(mpVBBuffer);

	void* retData = NULL;	
	HRESULT eD3dRet =  mpVBBuffer->Lock( 0, 0, &retData, 0 );
	if( FAILED(eD3dRet) )
	{
		GnLog( GnText("Error Failed to VertexBuffer Lock\n") );
		return NULL;
	}
	return retData;
}

void GnDX9DataStream::DX9Unlock()
{
	GnAssert(mpVBBuffer);

	mpVBBuffer->Unlock();
}

bool GnDX9DataStream::GetD3DDeclType(D3DDECLTYPE& outType)
{
	switch(mFormat)
	{
	case GnDataStream::POSTION_STREAM:
		outType = D3DDECLTYPE_FLOAT3;
		break;
	case GnDataStream::TEXTURE_STREAM:
		outType = D3DDECLTYPE_FLOAT2;
		break;
	case GnDataStream::NORMAL_STREAM:
		outType = D3DDECLTYPE_FLOAT3;
		break;
	case GnDataStream::COLOR_STREAM:
		outType = D3DDECLTYPE_D3DCOLOR;
		break;
	default:
		return false;
	}
	return true;
}

bool GnDX9DataStream::GetD3DDeclUsage(D3DDECLUSAGE& outUsage)
{
	switch(mFormat)
	{
	case GnDataStream::POSTION_STREAM:
		outUsage = D3DDECLUSAGE_POSITION;
		break;
	case GnDataStream::TEXTURE_STREAM:
		outUsage = D3DDECLUSAGE_TEXCOORD;
		break;
	case GnDataStream::NORMAL_STREAM:
		outUsage = D3DDECLUSAGE_NORMAL;
		break;
	case GnDataStream::COLOR_STREAM:
		outUsage = D3DDECLUSAGE_COLOR;
		break;
	default:
		return false;
	}
	return true;
}

