#include "GnToolLibPCH.h"
#include "GtActorObject.h"

GnImplementRTTI(GtActorObject, GtObject);

#define BASEPOSTION 100

GtActorObject::GtActorObject() : mpCurrentSequence(NULL), mMeshRect(0, 0, 70, 70)
{
}

GtActorObject::~GtActorObject()
{

}

bool GtActorObject::AddSequenceInfo(GtSequenceInfo* pInfo)
{
	for( gtuint i = 0 ; i < mSequences.GetSize() ; i++ ) 
	{
		if( mSequences[i]->GetName() == pInfo->GetName() || mSequences[i]->GetSequenceID() == pInfo->GetSequenceID() 
			|| mSequences[i]->GetFileName() == pInfo->GetFileName() )
			return false;
	}

	mSequences.Add( pInfo );
	return true;
}

void GtActorObject::RemvoeSequenceInfo(const gchar* pcSequenceName)
{
	for( gtuint i = 0 ; i < mSequences.GetSize() ; i++ ) 
	{
		if( mSequences[i]->GetName() == pcSequenceName )
		{
			mSequences.RemoveAtAndFillAll( i );
			break;
		}
	}
	return;
}

GtSequenceInfo* GtActorObject::GetSequenceInfo(const gchar* pcSequenceName)
{
	for( gtuint i = 0 ; i < mSequences.GetSize() ; i++ ) 
	{
		if( mSequences[i]->GetName() == pcSequenceName )
			return mSequences[i];
	}
	return NULL;
}

bool GtActorObject::LoadStream()
{	
	gchar outPath[GN_MAX_PATH] = {0,};
	GtToolSettings::MakeSaveFilePath( mGATFileName, mObjectName, outPath, sizeof(outPath) );

	GnStream toolStream;
	if( toolStream.Load( outPath ) == false )
		return false;

	mSequences.RemoveAll();

	GnActorTool* pTool = GnNew GnActorTool();
	pTool->LoadStream( &toolStream );
	toolStream.Close();

	mpsActor = GnNew GnPlaneActor();
	mpsActor->SetActorTool( pTool );

	GnTPrimitiveArray<GnActorTool::SequenceInfo*>infos;
	pTool->GetSequenceInfos( infos );

	gchar sequenceBasePath[GN_MAX_PATH] = {0,};
	GnStrcpy( sequenceBasePath, GtToolSettings::GetWorkPath(), sizeof(sequenceBasePath) );
	GnStrcat( sequenceBasePath, mObjectName, sizeof(sequenceBasePath) );
	GnStrcat( sequenceBasePath, "\\", sizeof(sequenceBasePath) );
	for( gtuint i = 0 ; i < infos.GetSize() ; i++ )
	{
		GnActorTool::SequenceInfo* info = infos.GetAt( i );
		GtSequenceInfo* gtInfo = GnNew GtSequenceInfo();
		gtInfo->SetSequenceID( info->GetSequenceID() );
		gtInfo->SetName( info->GetSequenceName() );
		gtInfo->SetFileName( info->GetFileName() );
		gtInfo->LoadStream( mObjectName, sequenceBasePath );
		mSequences.Add( gtInfo );
	}

	GtToolSettings::MakeSaveFilePath( mFileName, mObjectName, outPath, sizeof(outPath) );
	GnObjectStream objectStream;
	if( objectStream.Load( outPath ) )
	{
		mpsRootNode = (GnObjectForm*)objectStream.GetObject( 0 );
		GnAssert( mpsRootNode );
		GnSMElement* meshElement = (GnSMElement*)mpsRootNode->GetObjectByName( "Actor" );
		GnAssert( meshElement );
		mMeshRect = meshElement->GetDisplayRect();
		MakeRenderDisplayRect();		
		objectStream.Close();
	}

	mpsActor = NULL;
	return true;
}

bool GtActorObject::SaveStream()
{
	GnActorTool* pTool = CreateActorTool();

	gchar outPath[GN_MAX_PATH] = {0,};
	gchar outPath2[GN_MAX_PATH] = {0,};
	GtToolSettings::MakeSaveFilePath( mGATFileName, mObjectName, outPath, sizeof(outPath) );
	GnStream toolStream;
	if( toolStream.Save( outPath ) )
	{		
		GnPath::GetFullPathA( outPath, outPath2, GN_MAX_PATH );
		GnLogA( "GtActorObject SaveStream %s", outPath2 );
		pTool->SaveStream( &toolStream );
	}
	toolStream.Close();	

	gchar sequenceBasePath[GN_MAX_PATH] = {0,};
	GnStrcpy( sequenceBasePath, GtToolSettings::GetWorkPath(), sizeof(sequenceBasePath) );
	GnStrcat( sequenceBasePath, mObjectName, sizeof(sequenceBasePath) );
	GnStrcat( sequenceBasePath, "\\", sizeof(sequenceBasePath) );

	for( gtuint i = 0 ; i < mSequences.GetSize() ; i++ )
	{
		GtSequenceInfo* gtInfo = mSequences.GetAt( i );
		gtInfo->SaveStream( mObjectName, sequenceBasePath );
	}

	if( mpsRootNode )
	{
		MakeObjectDisplayRect();
		GtToolSettings::MakeSaveFilePath( mFileName, mObjectName, outPath, sizeof(outPath) );
		GnObjectStream objectStream;
		objectStream.InsertRootObjects( mpsRootNode );
		if( objectStream.Save( outPath ) )
		{
			GnLogA( "mpsRootNode SaveStream %s", outPath );
			objectStream.Close();
		}
		MakeRenderDisplayRect();
	}

	GnDelete pTool;
	return true;
}

GnActorTool* GtActorObject::CreateActorTool()
{
	GnActorTool* pTool = GnNew GnActorTool();
	pTool->SetName( mObjectName );
	pTool->SetGATFilePath( mGATFileName );
	pTool->SetGMFilePath( mFileName );

	for( gtuint i = 0 ; i < mSequences.GetSize() ; i++ )
	{
		GtSequenceInfo* gtInfo = mSequences.GetAt( i );
		GnActorTool::SequenceInfo* gnInfo = GnNew GnActorTool::SequenceInfo();
		gnInfo->SetFileName( gtInfo->GetFileName() );
		gnInfo->SetSequenceID( gtInfo->GetSequenceID() );
		gnInfo->SetSequenceName( gtInfo->GetName() );
		pTool->AddSequenceInfo( gnInfo->GetSequenceID(), gnInfo );
	}

	return pTool;
}

GnPlaneActor* GtActorObject::CreateActorFromExistData()
{
	mpsActor = GnNew GnPlaneActor();
	GnActorTool* tool = CreateActorTool();	
	mpsActor->SetActorTool( tool );

	if( mpsRootNode == NULL )
	{
		mMeshRect = GnIRect(0, 0, 70, 70);
		GnScreenMesh* mesh = GnScreenMesh::CreateScreenMesh(4, false, false, true);
		mesh->SetTexture( 0, GnFRect( 0, 0, 1, 1 ) );
		mesh->SetName( mObjectName );

		GnSMElement* meshElement = GnNew GnSMElement();
		meshElement->SetName( "Actor" );
		meshElement->SetMesh( mesh, MakeRenderDisplayRect( mMeshRect ) );

		GnSMGroup* meshGroup = GnNew GnSMGroup();
		meshGroup->SetName( "ActorGroup" );
		meshGroup->AttachChild( meshElement );
		mpsRootNode = meshGroup;
	}
	else
	{
		GnSMElement* meshElement = (GnSMElement*)mpsRootNode->GetObjectByName( "Actor" );
		meshElement->SetDisplayRect( MakeRenderDisplayRect( mMeshRect ) );
		meshElement->UpdateRect( true );
	}

	mpsActor->SetRootNode( (GnSMElement*)((GnObjectForm*)mpsRootNode) );
	CreateSequenceFromExistData();
	return mpsActor;
}

GnPlaneActor* GtActorObject::ResetSequence()
{
	if( mpsActor == NULL )
	{
		CreateActorFromExistData();
		return mpsActor;
	}
	GnAssert( mpsActor );
	CreateSequenceFromExistData();
	return mpsActor;
}

void GtActorObject::CreateSequenceFromExistData()
{
	for( gtuint i = 0 ; i < mSequences.GetSize() ; i++ )
	{
		GtSequenceInfo* gtInfo = mSequences.GetAt( i );		
		GnSequence* gnSequence = gtInfo->CreateSequence();
		mpsActor->ChangeSequence( gtInfo->GetSequenceID(), gnSequence );
	}
}

void GtActorObject::Update(float fTime)
{
	if( mpsActor )
		mpsActor->Update( fTime );
}

GnVector2 GtActorObject::GetScale()
{
	return GnVector2( (float)mMeshRect.GetWidth(), (float)mMeshRect.GetHeight() );
}

void GtActorObject::ChanageScale(gint32 iX, gint32 iY)
{
	if( mpsActor == NULL )
	{
		CreateActorFromExistData();
		return;
	}
	
	mMeshRect.right = iX;
	mMeshRect.bottom = iY;
	MakeRenderDisplayRect();
}

bool GtActorObject::EnableLoadGnObject()
{
	if( GtObject::EnableLoadGnObject() == false )
		return false;

	if( mpsActor )
		return false;

	return true;
}

GnIRect GtActorObject::MakeRenderDisplayRect(GnIRect objectRect)
{
	objectRect.left += BASEPOSTION;
	objectRect.top += BASEPOSTION;
	objectRect.right += BASEPOSTION;
	objectRect.bottom += BASEPOSTION;
	return objectRect;
}