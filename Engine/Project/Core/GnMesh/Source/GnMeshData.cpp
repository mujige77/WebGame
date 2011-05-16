#include "GnMeshPCH.h"
#include "GnMeshData.h"
#include "GnFactoryManager.h"

GnDataStreamList::GnDataStreamList() : mStride(0)
{
}

void GnDataStreamList::AddDataStream(GnDataStream* pStream)
{
	pStream->SetOffset(mStride);
	mStride += pStream->GetStrideSize();
	
	guint8 index = 0;
	GnListIterator<GnDataStream*> iter = GetIterator();
	while( iter.Valid() )
	{
		GnDataStream* data = iter.Item();
		if( data->GetFormat() == pStream->GetFormat() )
		{
			++index;
		}

		iter.Forth();
	}	
	pStream->SetNumStream(GetCount());
	pStream->SetUsageIndex(index);
	Append(pStream);
}

void GnDataStreamList::RemoveAllStream()
{
	GnListIterator<GnDataStream*> iter = GetIterator();
	while( iter.Valid() )
	{
		GnDelete iter.Item();
		iter.Forth();
	}	
}

GnImplementRTTI(GnMeshData, GnObject);
GnMeshData::~GnMeshData()
{
	mDataStreams.RemoveAllStream();
}

GnDataStream* GnMeshData::AddDataStream(const GnDataStream::eFormat format, guint32 uiVertexCount)
{
	GnDataStream* element = CreateDataStream(format, uiVertexCount);
	mDataStreams.AddDataStream(element);
	SetAddDataStream(true);
	return element;
}

GnDataStream* GnMeshData::GetDataStream(const GnDataStream::eFormat format, guint8 uiIndex)
{
	GnListIterator<GnDataStream*> iter = mDataStreams.GetIterator();
	while ( iter.Valid() )
	{
		GnDataStream* data = iter.Item();
		if( data->GetFormat() == format && data->GetUsageIndex() == uiIndex )
		{
			return data;
		}

		iter.Forth();
	}	
	return NULL;
}

GnObject* GnMeshData::CreateObject()
{
	GnObject* meshData = GnFactoryManager::CreateMeshData();
	return meshData;
}

void GnMeshData::LoadStream(GnObjectStream* pStream)
{
	GnObject::LoadStream( pStream );

	guint32 size = 0;
	pStream->LoadStream( size );
	
	for( guint32 i = 0 ; i < size ; i++ )
	{
		guint8 format = GnDataStream::SEMANTICS_DATASTREAM_MAX;
		guint32 vertexCount = 0;
		pStream->LoadStream( format );
		pStream->LoadStream( vertexCount );
		GnDataStream* data = AddDataStream( (GnDataStream::eFormat)format, vertexCount );
		pStream->LoadStream( data );
	}
}

void GnMeshData::LinkObject(GnObjectStream* pStream)
{
	GnObject::LinkObject( pStream );
}

void GnMeshData::SaveStream(GnObjectStream* pStream)
{
	GnObject::SaveStream( pStream );

	guint32 size = mDataStreams.GetCount();
	pStream->SaveStream( size );

	GnListIterator<GnDataStream*> iter = mDataStreams.GetIterator();
	while ( iter.Valid() )
	{
		GnDataStream* data = iter.Item(); 
		guint8 format = data->GetFormat();
		guint32 vertexCount = data->GetVertexCount();
		pStream->SaveStream( format );		
		pStream->SaveStream( vertexCount );
		pStream->SaveStream( data ); 
		iter.Forth();
	}
}

void GnMeshData::RegisterSaveObject(GnObjectStream* pStream)
{
	GnObject::RegisterSaveObject( pStream );
}
