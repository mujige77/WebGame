#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GActorCtlrManager.h"
#include "GActionAttack.h"
GActorCtlrManager::GActorCtlrManager(GLayer* pLayer) : mpActorLayer( pLayer )
{
}

GActorCtlrManager::~GActorCtlrManager()
{
}

void GActorCtlrManager::Update(float fDeltaTime)
{
	for( gtuint i = 0; i < mActors.GetSize(); i++ )
	{
		GActorController* actorCtlr = mActors.GetAt( i );
		if( actorCtlr->IsDestory() )
		{
			mActors.RemoveAtAndFill( i );
			--i;
			GnDelete actorCtlr;
		}
		else
		{
			actorCtlr->Update( fDeltaTime );
		}
	}
}

//void GActorCtlrManager::SetStartPostion(GActorController* pActorController
//	, gtuint uiDirection , gtuint uiAttackLine)
//{
//	static const gtint rendLinePosX = 10;
//	static gtint rendLine = rendLinePosX;
//	if( rendLine == rendLinePosX )
//		rendLine = 0;
//	else if( rendLine == 0 )
//		rendLine = -rendLinePosX;
//	else
//		rendLine = rendLinePosX;
//	
//	GnVector2 postion = GetGameEnvironment()->GetStartPosition( uiDirection, uiAttackLine );
//	postion.y += (float)rendLine;
//	pActorController->Start( postion );
//}

void GActorCtlrManager::CollisionCheck(GActorCtlrManager* pCheckCtlrManager)
{
	for ( gtuint i = 0; i < GetActorCtlrSize(); i++)
	{
		GActorController* actor = GetActorCtlr( i );
		GActionAttack* attack = (GActionAttack*)actor->GetActionComponent( GAction::ACTION_ATTACK );
		if( attack && attack->GetAttackActorCount() == 0 )
		{
			for ( gtuint j = 0; j < pCheckCtlrManager->GetActorCtlrSize(); j++ )
			{
				if( attack->CollisionCheck( pCheckCtlrManager->GetActorCtlr( j ) ) && attack->IsMoreAttack() )
					break;
			}
		}
	}
}