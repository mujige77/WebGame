#include "GnMeshPCH.h"
#include "GnDataStream.h"

GnDataStream::GnDataStream(const GnDataStream::eFormat format, guint32 uiCount) : mFormat(format),
	mLocked(false), mUnshaped(true), mNumStream(0), mUsageIndex(0), mpLocalBuffer(NULL), mVertexCount(uiCount)
{
}

GnDataStream::~GnDataStream()
{
	// This assertion detects the deletion of a locked NiDataStream. All 
	// streams should be properly unlocked before deletion.
	GnAssert(!GetLocked());
}

gtuint GnDataStream::GetStride(const GnDataStream::eFormat format)
{
	GnAssert(false);
	return 0;
}

// 포멧과 버텍스 카운트는 GnMeshData에서 저장 로드 한다.
void GnDataStream::SaveStream(GnStream* pStream)
{
	guint32 size = GetBufferSize();
	pStream->SaveStream( size );
	pStream->SaveStreams( (gchar*)mpLocalBuffer, size );
	pStream->SaveStream( mNumStream );
	pStream->SaveStream( mUsageIndex );
	pStream->SaveStream( mOffset );
}

void GnDataStream::LoadStream(GnStream* pStream)
{
	guint32 size = 0;
	pStream->LoadStream( size );
	pStream->LoadStreams( (gchar*)mpLocalBuffer, size );
	pStream->LoadStream( mNumStream );
	pStream->LoadStream( mUsageIndex );
	pStream->LoadStream( mOffset );
}