#include "StdAfx.h"
#include "Gt2DActor.h"

GnImplementRTTI(Gt2DActor, GtObject);
Gt2DActor::Gt2DActor(void)
{
}


Gt2DActor::~Gt2DActor(void)
{
}

bool Gt2DActor::SaveData(const gchar* pcBasePath)
{
	gchar sequenceBasePath[GN_MAX_PATH] = {0,};
	GnStrcpy( sequenceBasePath, GtToolSettings::GetWorkPath(), sizeof(sequenceBasePath) );
	GnStrcat( sequenceBasePath, GetObjectName(), sizeof(sequenceBasePath) );
	GnStrcat( sequenceBasePath, "/", sizeof(sequenceBasePath) );

	GtToolSettings::CreateDirectoryInWorkDirectory( GetObjectName() );

	// save *.gat file
	std::string toolPath = sequenceBasePath;
	toolPath += GetGATFileName();
	GnStream toolStream;
	if( toolStream.Save( toolPath.c_str() ) )
	{
		std::string gmFileName = GetObjectName();
		gmFileName += "/";
		gmFileName += GetGMFileName();
		GetActorTool()->SetGMFilePath( gmFileName.c_str() );
		GetActorTool()->SaveStream( &toolStream );
	}
	else
		GnLogA( "GtActorObject SaveStream %s", toolPath );
	toolStream.Close();	

	// save *.gm file
	GetRootNode()->SetName( GetObjectName() );
	std::string meshPath = sequenceBasePath;
	meshPath += GetGMFileName();
	GnObjectStream meshStream;	
	meshStream.InsertRootObjects( GetRootNode() );
	GnVerify( meshStream.Save( meshPath.c_str() ) );
	meshStream.Close();

	// save *.ga file
	GnTMap<guint32, Gt2DSequencePtr>::Iterator iter;
	mpGtSequences.GetFirstIter(iter);	
	while( iter.Valid() )
	{
		GnTObjectDeleteMap<guint32, Gt2DSequencePtr>::Entry& entity = iter.Item();		
		if( entity.m_data->IsModifed() )
		{
			entity.m_data->GetSequence()->GetAVData()->Move( GnVector2(0.0f, 0.0f)  );
			entity.m_data->GetSequence()->GetAVData()->FlipX( false, 0.0f );
			entity.m_data->SaveData( GetObjectName(), sequenceBasePath );
		}
		mpGtSequences.GetNextIter( iter );
	}

	return true;
}

bool Gt2DActor::LoadData()
{
	if( mGATFileName.Exists() )
	{
		gchar outPath[GN_MAX_PATH] = {0,};
		GtToolSettings::MakeSaveFilePath( mGATFileName, GetObjectName(), outPath, sizeof(outPath) );

		if( mpsActor == NULL )
		{
			GnObjectStream objStream;
			mpsActor = Gn2DActor::Create( outPath, objStream, false );
			//mpsActor = GnNew Gn2DActor();
		}

		if( mpsActor->GetActorTool() == NULL )
		{
			GnStream toolStream;
			if( toolStream.Load( outPath ) == false )
				return false;

			GtActorTool* pTool = GnNew GtActorTool();
			pTool->LoadStream( &toolStream );	
			mpsActor->SetActorTool( pTool );
		}
		
		if( mpsActor->GetRootNode() == NULL )
		{
			Gn2DMeshObject* rootNode = GnNew Gn2DMeshObject();
			mpsActor->SetRootNode( rootNode );
		}
		
	}
	else
		return false;

	return true;
}

void Gt2DActor::SetObjectName(const gchar* pcVal)
{
	GtObject::SetObjectName( pcVal );
	string fileName = pcVal;
	fileName +=  ".gat";
	SetGATFileName( fileName.c_str() );
	fileName = pcVal;
	fileName += ".gm";
	SetGMFileName( fileName.c_str() );
}

void Gt2DActor::RemoveSequenceWithTool(guint32 uiID)
{
	RemoveGtSequence( uiID );
	GtActorTool* actorTool = (GtActorTool*)GetActor()->GetActorTool();
	actorTool->RemoveSequenceInfo( uiID );
	actorTool->SetModifed( true );
}

bool Gt2DActor::CreateData()
{
	mpsActor = GnNew Gn2DActor();
	GtActorTool* actorTool = (GtActorTool*)GetActor()->GetActorTool();
	GnAssert( actorTool == NULL );
	actorTool = GnNew GtActorTool();
	GnAssert( mGATFileName.Exists() );
	std::string fileName = GetObjectName();
	fileName += GetGATFileName();
	actorTool->SetGATFilePath( fileName.c_str() );
	fileName = GetObjectName();
	fileName += GetGMFileName();
	actorTool->SetGMFilePath( fileName.c_str() );
	GetActor()->SetActorTool( actorTool );

	Gn2DMeshObject* rootNode = GnNew Gn2DMeshObject();
	GetActor()->SetRootNode( rootNode );
	return true;
}

void Gt2DActor::AddGtSequence(guint32 uiID, Gt2DSequence* sequence)
{
	mpGtSequences.Insert(uiID, sequence);
}

bool Gt2DActor::GetGtSequence(guint32 uiID, Gt2DSequence*& sequence)
{
	Gt2DSequencePtr psSequence;
	if( mpGtSequences.GetAt( uiID, psSequence ) == false)
		return false;

	sequence = psSequence;
	return true;
}

void Gt2DActor::RemoveGtSequence(guint32 uiID)
{		
	GetActor()->StopAnimation();
	GetActor()->RemoveSequence(uiID);
	mpGtSequences.Remove(uiID, true);
}

void Gt2DActor::ResetSequence(guint32 uiID)
{
	//RemoveSequence( uiID );
	//ChangeSequence( sequence->GetID(), sequence );
	//SetTargetAnimation( sequence->GetID() );
}