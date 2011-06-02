#include "GnMeshPCH.h"
#include "Gn2DActor.h"

Gn2DActor* Gn2DActor::Create(const gchar* pcActorToolFileName, GnObjectStream& stream
	, bool bLoadSequenceFile)
{
	GnStream toolStream;
	if( toolStream.Load( pcActorToolFileName ) == false )
		return NULL;

	GnActorToolPtr pTool = GnNew GnActorTool();
	pTool->LoadStream( &toolStream );

	return Create( pTool, stream, bLoadSequenceFile );
}

Gn2DActor* Gn2DActor::Create(GnActorTool* pActorTool, GnObjectStream& stream, bool bLoadSequenceFile)
{
	//if( stream.Load(pActorTool->GetGMFilePath()) == false )
	//	return false;
	//Gn2DMeshObject* rootNode = (Gn2DMeshObject*)stream.GetObject(0);
	Gn2DMeshObject* rootNode = GnNew Gn2DMeshObject();
	Gn2DActor* pActor = GnNew Gn2DActor( pActorTool, rootNode );
	if( bLoadSequenceFile )
		pActor->LoadAllSequence( stream );

	return pActor;
}
Gn2DActor::Gn2DActor() : mpsActorTool(NULL), mpsRootNode(NULL), mpCurrentSequence(NULL)
{

}
Gn2DActor::Gn2DActor(GnActorTool* pActorTool, Gn2DMeshObject* pRootObject) : mpsActorTool(pActorTool)
	, mpsRootNode(pRootObject), mpCurrentSequence(NULL)
{
}

Gn2DActor::~Gn2DActor()
{
	mpSequences.RemoveAll( true );
	mpsActorTool->RemoveAllSequenceInfo();
}

void Gn2DActor::Update(float fDeltaTime)
{
	if( mCurrentID != mTargetID )
	{
		Gn2DSequence* sequence = NULL;
		if( GetSequence( mTargetID, sequence ) )
		{
			mCurrentID = mTargetID;
			if( mpCurrentSequence )
				mpCurrentSequence->Stop();

			mpCurrentSequence = sequence;			
			mpCurrentSequence->Start( fDeltaTime );			
		}
	}

	if( mpCurrentSequence == NULL )
		return;

	// 바뀌면서 된것
	mpCurrentSequence->Update( fDeltaTime );
}

bool Gn2DActor::SetTargetAnimation(guint32 uiID)
{
	if( mTargetID == uiID )
		return true;

	Gn2DSequence* sequence = NULL;
	if( GetSequence( uiID, sequence ) == false )
	{
		if( LoadSequence( uiID ) == false )
			return false;
	}

	mTargetID = uiID;
	return true;
}

void Gn2DActor::StopAnimation()
{
	mTargetID = NULL_ANI;
	mCurrentID = NULL_ANI;
	if( mpCurrentSequence )
		mpCurrentSequence->Stop();
	mpCurrentSequence = NULL;
}

void Gn2DActor::ChangeRootNode(GnObjectForm* pRootNode)
{
	GnAssert(pRootNode);

	GnTObjectDeleteMap<gtuint, Gn2DSequence*>::Iterator iter;
	mpSequences.GetFirstIter(iter);	
	while( iter.Valid() )
	{
		GnTObjectDeleteMap<gtuint, Gn2DSequence*>::Entry& entity = iter.Item();
		// 바뀌면서 된것
		entity.m_data->SetTargetObject(pRootNode);
		mpSequences.GetNextIter(iter);
	}
}

bool Gn2DActor::LoadAllSequence(GnObjectStream& stream)
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
				(gchar*)sequenceInfo->GetSequenceName(), sequenceInfo->GetSequenceID() );
		}
	}
	return true;
}

bool Gn2DActor::LoadSequence(guint32 uiID)
{
	GnActorTool::SequenceInfo* sequenceInfo;
	if( mpsActorTool->GetSequenceInfo( uiID, sequenceInfo ) == false )
		return false;

	GnObjectStream stream;
	return AddSequence( sequenceInfo, stream, true );
}

bool Gn2DActor::AddSequence(GnActorTool::SequenceInfo* pInfo, GnObjectStream& stream, bool bLoadFile)
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
	
	Gn2DSequence* sequence = CreateSequenceFromFile( stream, pInfo->GetSequenceID() );
	if( sequence == NULL )
		return false;
	
	ChangeSequence( pInfo->GetSequenceID(), sequence );
	return true;
}

Gn2DSequence* Gn2DActor::CreateSequenceFromFile(GnObjectStream& stream, guint32  uiID)
{
	for( gtuint i = 0 ; i < stream.GetObjectCount() ; i++ )
	{
		Gn2DSequence* sequence = GnDynamicCast( Gn2DSequence, stream.GetObject( i ) );
		if( sequence && sequence->GetID() == uiID )
			return sequence;
	}
	return NULL;
}

bool Gn2DActor::SaveAllLoadedSequence(GnObjectStream& stream)
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

bool Gn2DActor::SaveSequence(Gn2DSequence* pSequence, GnSimpleString& strFileName
	,  GnObjectStream* pStream)
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

void Gn2DActor::ChangeSequence(guint32 uiID, Gn2DSequence* pSequences)
{
	GnAssert( pSequences );
	mpSequences.SetAt( uiID, pSequences, true );
	pSequences->SetTargetObject( (Gn2DMeshObject*)mpsRootNode );
}