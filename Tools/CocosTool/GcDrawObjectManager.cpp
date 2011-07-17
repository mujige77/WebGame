#include "StdAfx.h"
#include "GcDrawObjectManager.h"
#include "ActorMacro.h"
#include "GLayer.h"

GcDrawObjectManager::GcDrawObjectManager(void) : mpDrawLayer( NULL )
{
}

GcDrawObjectManager::~GcDrawObjectManager(void)
{
}

void GcDrawObjectManager::Update(float fDeltaTime)
{
	if( mpsActor && mpsActor->GetActor() )
		mpsActor->GetActor()->Update( fDeltaTime );

	if( mps2DObject && mps2DObject->Get2DMeshObjecct() )
		mps2DObject->Get2DMeshObjecct()->Update( fDeltaTime );

	AttachEffectToActor();
}

void GcDrawObjectManager::SelectActor(GtObject* pObject)
{
	mpsActor = (Gt2DActor*)pObject;
	if( mpsActor == NULL )
		return;

	mpsActor->GetRootNode()->GetMesh()->setAnchorPoint( CCPointMake(0,0) );
	mpsActor->GetRootNode()->SetPosition( ActorBasePosition );
	GnLayer* state = GetSceneManager()->GetMainGameLayer();
	state->AddChild( mpsActor->GetRootNode(), 102 );

	if( mpsActorExtraDraw )
		mpDrawLayer->RemoveChild( mpsActorExtraDraw );		
	GnExtraDataPrimitivesLayer* extraDraw = GtObjectNew<GnExtraDataPrimitivesLayer>::Create();
	extraDraw->SetColor( GnColorA( 0.0f, 0.0f, 0.0f, 1.0f ) );
	extraDraw->SetThickness( 10.0f );
	extraDraw->SetMeshObject( mpsActor->GetRootNode() );
	mpDrawLayer->AddChild( extraDraw );
	mpsActorExtraDraw = extraDraw;
}

void GcDrawObjectManager::Select2DObject(GtObject* pObject)
{
	mps2DObject = (Gt2DObject*)pObject;
	if( mps2DObject == NULL )
		return;

	mps2DObject->Get2DMeshObjecct()->SetPosition( ActorBasePosition );
	GnLayer* state = GetSceneManager()->GetMainGameLayer();
	state->AddChild( mps2DObject->Get2DMeshObjecct(), 103 );

	if( mps2DObjectExtraDraw )
		mpDrawLayer->RemoveChild( mps2DObjectExtraDraw );
	GnExtraDataPrimitivesLayer* extraDraw = GtObjectNew<GnExtraDataPrimitivesLayer>::Create();	
	extraDraw->SetColor( GnColorA( 1.0f, 1.0f, 1.0f, 1.0f ) );
	extraDraw->SetThickness( 10.0f );
	extraDraw->SetMeshObject( mps2DObject->Get2DMeshObjecct() );
	mpDrawLayer->AddChild( extraDraw );
	mps2DObjectExtraDraw = extraDraw;
}

void GcDrawObjectManager::SetObjectPosition(GnVector2 cPosition)
{
	if( mpsActor && mpsActor->GetRootNode() )
		mpsActor->GetRootNode()->SetPosition( ActorBasePosition );

	if( mps2DObject && mps2DObject->Get2DMeshObjecct() )
		mps2DObject->Get2DMeshObjecct()->SetPosition( ActorBasePosition );

}

void GcDrawObjectManager::SetObjectCenter(bool bCenter)
{
	if( bCenter )
		ActorBasePosition = GnVector2( 200.0f, 100.0f );
	else
		ActorBasePosition = GnVector2( 0.0f, 0.0f );

	SetObjectPosition( ActorBasePosition );
}

void GcDrawObjectManager::Reset()
{
	mpsActor = NULL;
	mps2DObject = NULL;
	mpsSequence = NULL;

	GnLayer* state = GetSceneManager()->GetMainGameLayer();
	if( mpDrawLayer )
	{
		state->removeChild( mpDrawLayer, true );
		delete mpDrawLayer;
	}
	mpDrawLayer = new GnLayerDrawPrimitives();	
	state->addChild( mpDrawLayer, 106 );
}

bool GcDrawObjectManager::SelectSequence(GnActorTool::SequenceInfo* pSecuenceInfo)
{
	mpsSequence = NULL;
	if( mpsActor && pSecuenceInfo )
	{
		Gt2DSequence* sequence = NULL;
		mpsActor->GetGtSequence( pSecuenceInfo->GetSequenceID(), sequence );
		if( sequence == NULL || sequence->GetSequence() == NULL )
			return false;
		mpsSequence = sequence;
		sequence->GetSequence()->SetLoop( TRUE );
		return true;
	}
	return false;
}

void GcDrawObjectManager::AttachEffectToActor()
{
	if( mpsActor == NULL || mpsActor->GetRootNode() == NULL )
		return;
	if( mps2DObject == NULL )
		return;

	GnExtraData* effectData = NULL;
	Gn2DMeshObject* effectMesh = mps2DObject->Get2DMeshObjecct();
	for( gtuint i = 0; i < effectMesh->GetExtraDataSize(); i++ )
	{
		GnExtraData* data = effectMesh->GetExtraData( i );
		if( data->GetType() == GExtraData::EXTRA_EFFECT_POSITIONID )
		{
			effectData = data;
			break;
		}
	}
	if( effectData == NULL )
		return;

	GnVector2ExtraData* posData = NULL;
	Gn2DMeshObject* actorMesh = mpsActor->GetRootNode();
	for( gtuint i = 0; i < actorMesh->GetExtraDataSize(); i++ )
	{
		GnExtraData* data = actorMesh->GetExtraData( i );
		if( data->GetType() == GExtraData::EXTRA_EFFECT_POSITION )
		{
			posData = (GnVector2ExtraData*)data;
			break;
		}
	}
	if( posData == NULL )
		return;

	if( effectData->GetID() == posData->GetID() )
	{
		GnVector2 effectPos = posData->GetValueVector2() + actorMesh->GetPosition();
		effectMesh->SetPosition( effectPos );
	}	
}