#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GActorCtlrManager.h"
#include "GActionAttackCheck.h"
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
			RemoveAndDeleteActorCtlr( i );
			--i;
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

void GActorCtlrManager::ProcessAttack(GActorCtlrManager* pCheckCtlrManager)
{
	for ( gtuint i = 0; i < GetActorCtlrSize(); i++)
	{
		GActorController* actor = GetActorCtlr( i );
		GActionAttackCheck* attackCheck = (GActionAttackCheck*)actor->GetCurrentAction( GAction::ACTION_ATTACKCHECK );
		if( attackCheck )
		{
			if( attackCheck->IsEnableAttack() )
			{
				if( SendAttackToEnemy( attackCheck, pCheckCtlrManager ) > 0 )
					actor->RemoveCurrentAction( attackCheck->GetActionType() );
			}
			else if( attackCheck->IsReadyAttack() == false )
			{
				CollisionCheck( attackCheck, pCheckCtlrManager );
			}
		}
	}
}

void GActorCtlrManager::CollisionCheck(GActionAttackCheck* pAttackCheck, GActorCtlrManager* pCheckCtlrManager)
{
	for ( gtuint j = 0; j < pCheckCtlrManager->GetActorCtlrSize(); j++ )
	{
		if( pAttackCheck->CollisionCheck( pCheckCtlrManager->GetActorCtlr( j ) ) )
		{
			pAttackCheck->SetIsReadyAttack( true );
			break;
		}
	}	
}
gtuint GActorCtlrManager::SendAttackToEnemy(GActionAttackCheck* pAttackCheck, GActorCtlrManager* pCheckCtlrManager)
{
	gtuint numAttackCtrl = 0;
	GActorController* attacksCtrl[GActionAttackCheck::MAX_ATTCK_COUNT] = { NULL, };
	for ( gtuint j = 0; j < pCheckCtlrManager->GetActorCtlrSize(); j++ )
	{
		GActorController* checkCtrl = pCheckCtlrManager->GetActorCtlr( j );
		if( pAttackCheck->CollisionCheck( checkCtrl ) )
		{
			attacksCtrl[numAttackCtrl++] = checkCtrl;
			if( pAttackCheck->GetEnableAttackCount() <= numAttackCtrl )
				break;
		}
	}
	
	for( gtuint i = 0; i < numAttackCtrl; i++ )
	{
		attacksCtrl[i]->ReceiveAttack( pAttackCheck->GetController() );
	}
	return numAttackCtrl;
}