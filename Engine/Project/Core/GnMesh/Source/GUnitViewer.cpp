#include "GnGamePCH.h"
#include "GUnitViewer.h"
#include "GInterfaceLayer.h"
#include "GForcesController.h"
#include "GFileLIst.h"

GUnitViewer::~GUnitViewer()
{
	for( gtuint i = 0; i < mActors.GetSize(); i++ )
	{
		Unit* actorCtlr = mActors.GetAt( i );
		if( actorCtlr )
			GnDelete actorCtlr;
	}	
}

void GUnitViewer::SetVisibleActorCtlr(guint32 uiIndex, bool bVisible)
{
	for( gtuint i = 0 ; i < GetActorCtlrSize() ; i++ )
	{
		GUnitViewer::Unit* uint = GetUnit( i );
		if( uint->mIndex == uiIndex )
		{
			uint->mpActorController->GetMesh()->SetVisible( bVisible );
		}		
	}	
}

GUnitViewer* GUnitViewer::CreateUnitViewer(GnList<GUserHaveItem::Item>& cUnitItems)
{
	GetGameState()->SetGameScale( 0.7f );
	
	GUnitViewer* thisObject = GnNew GUnitViewer();	
	
	GnListIterator<GUserHaveItem::Item> iter = cUnitItems.GetIterator();
	gtint itemCount = 0;
	while( iter.Valid() )
	{
		guint32 unitIndex = iter.Item().mIndex;
		gchar idName[16] = { 0, };
		GetFileList()->GetForcesFileName( (gtuint)unitIndex, idName, sizeof( idName ) );
		GForcesController* controller = GForcesController::Create( idName, 1 );
		if( controller )
		{
			GnVector2 pos( 340.0f, 150.0f );
			if( itemCount == 0 )			
				pos.x -= 10.0f;
				
			controller->SetPosition( pos );
			controller->GetMesh()->SetVisible( false );
			thisObject->AddMeshToParentNode( controller->GetMesh() );
			controller->GetActor()->SetTargetAnimation( GAction::ANI_ATTACK );
			thisObject->AddActorCtlr( unitIndex, controller );
		}
		iter.Forth();
		++itemCount;
	}
	
	GetGameState()->SetGameScale( 1.0f );
	return thisObject;
}

void GUnitViewer::Update(float fDeltaTime)
{
	for( gtuint i = 0 ; i < GetActorCtlrSize() ; i++ )
	{
		GetActorCtlr( i )->GetActor()->Update( fDeltaTime );
	}
}