#include "GnMeshPCH.h"
#include "GnActorTool.h"

GnImplementRTTI(GnActorTool, GnObject);

void GnActorTool::SequenceInfo::SaveStream(GnStream* pStream)
{
	pStream->SaveStream( mSequenceID );
	const gchar* name =mSequenceName.GetHandle();
	pStream->SaveStream( name );
	name = mFileName.GetHandle();
	// 나중에 지우자
	const gchar* findConstChar = GnStrchr(name, '\\');
	if( findConstChar )
	{
		gchar fileName[MAX_ACTOR_PATH] = {0,};
		GnStrcpy( fileName, name, sizeof(fileName) );
		gchar* findChar = GnStrchr( fileName, '\\' );
		*findChar = '/';
		pStream->SaveStream( fileName );
	}
	else
		pStream->SaveStream( name );
}

void GnActorTool::SequenceInfo::LoadStream(GnStream* pStream)
{
	pStream->LoadStream( mSequenceID );	
	gchar* name = NULL;
	pStream->LoadStream( name );
	mSequenceName.SetHandle( name );
	pStream->LoadStream( name );
	mFileName.SetHandle( name );
}

void GnActorTool::LoadStream(GnStream* pStream)
{
	gchar strData[MAX_ACTOR_PATH] = { 0, };
	pStream->LoadStreams(strData, MAX_ACTOR_PATH);
	
	gchar* filePath = NULL;
	pStream->LoadStream( filePath );
	mGATFilePath.SetHandle( filePath );
	pStream->LoadStream( filePath );
	mGMFilePath.SetHandle( filePath );

	gushort sequenceCount;
	pStream->LoadStream( sequenceCount );

	for( gtuint i = 0 ; i < sequenceCount ; i++ )
	{
		SequenceInfo* sequence = GnNew SequenceInfo();		
		pStream->LoadStream( sequence );
		mpSequences.Insert( sequence->GetSequenceID(), sequence );
	}
}

void GnActorTool::SaveStream(GnStream* pStream)
{
	gchar strData[MAX_ACTOR_PATH] = { 0, };
	pStream->SaveStreams(strData, MAX_ACTOR_PATH);
	
	const char* path = mGATFilePath.GetHandle();
	pStream->SaveStream( path );
	path = mGMFilePath.GetHandle();
	pStream->SaveStream( path );

	gushort sequenceCount = mpSequences.Count();
	pStream->SaveStream( sequenceCount );

	GnTObjectDeleteMap<guint32, SequenceInfo*>::Iterator iter;
	mpSequences.GetFirstIter(iter);	
	while( iter.Valid() )
	{
		GnTObjectDeleteMap<guint32, SequenceInfo*>::Entry& entity = iter.Item();
		SequenceInfo* sequence =entity.m_data;
		pStream->SaveStream( sequence );
		mpSequences.GetNextIter( iter );
	}
}

void GnActorTool::AddSequenceInfo(guint32 uiID, const gchar* pcName, const gchar* pcFileName)
{
	SequenceInfo* info = GnNew SequenceInfo();
	info->SetSequenceID( uiID );
	info->SetFileName( pcFileName );
	info->SetSequenceName( pcName );	
	AddSequenceInfo( uiID, info );
}


void GnActorTool::GetSequenceInfos(GnTPrimitiveArray<SequenceInfo*>& outInfos)
{
	gushort sequenceCount = mpSequences.Count();
	outInfos.SetSize(sequenceCount);

	GnTObjectDeleteMap<guint32, SequenceInfo*>::Iterator iter;
	mpSequences.GetFirstIter(iter);	
	while( iter.Valid() )
	{
		GnTObjectDeleteMap<guint32, SequenceInfo*>::Entry& entity = iter.Item();		
		outInfos.Add(entity.m_data);
		mpSequences.GetNextIter(iter);
	}
}

bool GnActorTool::GetGAFullFileName( SequenceInfo* pSequenceInfo, gchar* pcOutPath, gtuint uiMaxSize )
{
	if( pSequenceInfo->GetFileName() == NULL )
	{
		pcOutPath[0] = '\0';
		return false;
	}
	GnStrcpy( pcOutPath, GnSystem::GetWorkDirectory(), uiMaxSize );
	GnStrcat( pcOutPath, pSequenceInfo->GetFileName(), uiMaxSize );
	GnAssert( GnStrlen(pcOutPath) <= uiMaxSize );
	return true;
}

