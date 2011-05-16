#include "GnMeshPCH.h"
#include "GnPlaneActor.h"

GnPlaneActor* GnPlaneActor::Create(const gchar* pcActorToolFileName, GnObjectStream& stream, bool bLoadSequenceFile)
{
	GnStream toolStream;
	if( toolStream.Load( pcActorToolFileName ) )
		return NULL;

	GnActorToolPtr pTool = GnNew GnActorTool();
	pTool->LoadStream( &toolStream );

	return Create( pTool, pcActorToolFileName, stream, bLoadSequenceFile );
}

GnPlaneActor* GnPlaneActor::Create(GnActorTool* pActorTool, const gchar* pcActorToolPath, GnObjectStream& stream,
	bool bLoadSequenceFile)
{
	if( stream.Load(pActorTool->GetGMFilePath()) == false )
		return false;

	GnSMElement* rootNode = (GnSMElement*)stream.GetObject(0);
	GnPlaneActor* pActor = GnNew GnPlaneActor( pActorTool, rootNode );
	if( bLoadSequenceFile )
		pActor->LoadAllSequence( stream );

	return pActor;
}
GnPlaneActor::GnPlaneActor() : mpsActorTool(NULL), mpsRootNode(NULL), mpCurrentSequence(NULL)
{

}
GnPlaneActor::GnPlaneActor(GnActorTool* pActorTool, GnSMElement* pRootObject) : mpsActorTool(pActorTool),
	mpsRootNode(pRootObject), mpCurrentSequence(NULL)
{
}

GnPlaneActor::~GnPlaneActor()
{
	mpSequences.RemoveAll( true );
	mpsActorTool->RemoveAllSequenceInfo();
}

void GnPlaneActor::Update(float fTime)
{
	if( mCurrentID != mTargetID )
	{
		GnSequence* sequence = NULL;
		if( GetSequence( mTargetID, sequence ) )
		{
			mCurrentID = mTargetID;
			if( mpCurrentSequence )
				mpCurrentSequence->Stop();
			mpCurrentSequence = sequence;
			mpCurrentSequence->SetTargetObject( (GnSMElement*)mpsRootNode );
			mpCurrentSequence->Start( fTime );			
		}
	}

	if( mpCurrentSequence == NULL )
		return;

	mpCurrentSequence->Update( fTime );
}

bool GnPlaneActor::SetTargetAnimation(guint32 uiID)
{
	if( mTargetID == uiID )
		return true;

	GnSequence* sequence = NULL;
	if( GetSequence( uiID, sequence ) == false )
		return false;

	mTargetID = uiID;
	return true;
}

void GnPlaneActor::StopAnimation()
{
	mTargetID = NULL_ANI;
	mCurrentID = NULL_ANI;
	mpCurrentSequence = NULL;
}

void GnPlaneActor::ChangeRootNode(GnAVObject* pRootNode)
{
	GnAssert(pRootNode);

	GnTObjectDeleteMap<gtuint, GnSequence*>::Iterator iter;
	mpSequences.GetFirstIter(iter);	
	while( iter.Valid() )
	{
		GnTObjectDeleteMap<gtuint, GnSequence*>::Entry& entity = iter.Item();
		entity.m_data->SetTargetObject(pRootNode);
		mpSequences.GetNextIter(iter);
	}
}

bool GnPlaneActor::LoadAllSequence(GnObjectStream& stream)
{
	GnTPrimitiveArray<GnActorTool::SequenceInfo*> sequinceInfos;
	mpsActorTool->GetSequenceInfos(sequinceInfos);
	if(  sequinceInfos.GetSize() < 1 )
		return false;
	
	GnSimpleString sequenceFileName;
	for( gtuint i = 0 ; i < sequinceInfos.GetSize() ; i++ )
	{
		bool loadFile = false;
		GnActorTool::SequenceInfo* sequenceInfo = sequinceInfos[i];
		if( sequenceInfo->GetFileName() != sequenceFileName )
		{
			sequenceFileName = sequenceInfo->GetFileName();
			loadFile = true;
		}
		if( AddSequence( sequenceInfo, stream, loadFile ) == false )
		{
			GnLog( GnText(" LoadAllSequence : Failed AddSequence - Name = %s, ID = %d"),
				(gchar*)sequenceInfo->GetSequenceName().GetHandle(), sequenceInfo->GetSequenceID() );
		}
	}
	return true;
}

bool GnPlaneActor::AddSequence(GnActorTool::SequenceInfo* pInfo, GnObjectStream& stream, bool bLoadFile)
{
	GnAssert( pInfo );
	gchar fileName[MAX_ACTOR_PATH] = {0, };
	if( bLoadFile )
	{
		if( mpsActorTool->GetGAFullFileName( pInfo->GetSequenceID(), fileName, MAX_ACTOR_PATH ) == false )
			return false;

		if( stream.Load( fileName ) == false )
			return false;
	}
	
	GnSequence* sequence = CreateSequenceFromFile( stream, pInfo->GetSequenceName() );
	if( sequence == NULL )
		return false;
	
	ChangeSequence( pInfo->GetSequenceID(), sequence );
	return true;
}

GnSequence* GnPlaneActor::CreateSequenceFromFile(GnObjectStream& stream, const GnSimpleString& strSequenceName)
{
	for( gtuint i = 0 ; i < stream.GetObjectCount() ; i++ )
	{
		GnSequence* sequence = GnDynamicCast( GnSequence, stream.GetObject( i ) );
		if( sequence && sequence->GetName() == strSequenceName )
			return sequence;
	}
	return NULL;
}

bool GnPlaneActor::SaveAllLoadedSequence(GnObjectStream& stream)
{
	GnTPrimitiveArray<GnActorTool::SequenceInfo*> sequinceInfos;
	mpsActorTool->GetSequenceInfos(sequinceInfos);
	if(  sequinceInfos.GetSize() < 1 )
		return false;

	bool bOneFile = false;
	GnSimpleString sequenceFileName;
	for( gtuint i = 0 ; i < sequinceInfos.GetSize() ; i++ )
	{
		GnActorTool::SequenceInfo* sequenceInfo = sequinceInfos[i];
		if( sequenceInfo->GetFileName() != sequenceFileName )
			sequenceFileName = sequenceInfo->GetFileName();
		else	if(  sequenceInfo->GetFileName() == sequenceFileName )
		{
			bOneFile = true;
			break;
		}
	}

	if( bOneFile )
	{
		LoadAllSequence(stream);
	}
	return true;
}

bool GnPlaneActor::SaveSequence(GnSequence* pSequence, GnSimpleString& strFileName,  GnObjectStream* pStream)
{
	bool bDelete = false;
	if( pStream == NULL )
	{
		bDelete = true;
		pStream = GnNew  GnObjectStream();
	}

	pStream->InsertRootObjects( pSequence );

	if( bDelete )
		GnDelete pStream;

	return true;
}

void GnPlaneActor::ChangeSequence(guint32 uiID, GnSequence* pSequences)
{
	GnAssert( pSequences );
	mpSequences.SetAt( uiID, pSequences, true );
	pSequences->SetTargetObject( (GnSMElement*)mpsRootNode );
}