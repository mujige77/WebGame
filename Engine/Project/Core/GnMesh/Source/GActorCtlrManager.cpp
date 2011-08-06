#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GActorCtlrManager.h"
#include "GActionAttackCheck.h"
#include "GInfoBasic.h"

GActorCtlrManager::GActorCtlrManager(GLayer* pLayer, GCastle* pCastle) : mpActorLayer( pLayer )
	, mpCastle( pCastle )
{
}

GActorCtlrManager::~GActorCtlrManager()
{
	for( gtuint i = 0; i < mActors.GetSize(); i++ )
	{
		GActorController* actorCtlr = mActors.GetAt( i );
		GetActorLayer()->RemoveChild( actorCtlr->GetMesh() );
#ifdef GNDEBUG
		if( actorCtlr->GetDebugLayer() )
			GetActorLayer()->removeChild( actorCtlr->GetDebugLayer(), true );
#endif
		GnDelete actorCtlr;
	}
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
	if( pCheckCtlrManager->GetCastle() && CastleCollisionCheck( pAttackCheck, pCheckCtlrManager->GetCastle() ) )
		pAttackCheck->SetIsReadyAttack( true );

	for ( gtuint j = 0; j < pCheckCtlrManager->GetActorCtlrSize(); j++ )
	{
		GActorController* checkCtrl = pCheckCtlrManager->GetActorCtlr( j );
		if( CollisionCheck( pAttackCheck, checkCtrl ) )
		{
			pAttackCheck->SetIsReadyAttack( true );
			break;
		}
	}	
}
gtuint GActorCtlrManager::SendAttackToEnemy(GActionAttackCheck* pAttackCheck, GActorCtlrManager* pCheckCtlrManager)
{
	gtuint totalNumAttackCtrl = 0;
	GCastle* castle = pCheckCtlrManager->GetCastle();
	if( castle && CastleCollisionCheck( pAttackCheck, castle ) )
	{
		GInfoBasic* fromActorBasic = 
			(GInfoBasic*)pAttackCheck->GetController()->GetInfoComponent( GInfo::INFO_BASIC );
		castle->ReceveAttack( (gint32)fromActorBasic->GetStrength() );
		++totalNumAttackCtrl;
	}
		
	gtuint enableAttackCount = pAttackCheck->GetEnableAttackCount() - totalNumAttackCtrl;
	if( enableAttackCount )
	{
		gtuint numAttackCtrl = 0;
		GActorController* attacksCtrl[GActionAttackCheck::MAX_ATTCK_COUNT] = { NULL, };
		for ( gtuint j = 0; j < pCheckCtlrManager->GetActorCtlrSize(); j++ )
		{
			GActorController* checkCtrl = pCheckCtlrManager->GetActorCtlr( j );
			if( CollisionCheck( pAttackCheck, checkCtrl ) )
			{
				attacksCtrl[numAttackCtrl++] = checkCtrl;
				if( enableAttackCount <= numAttackCtrl )
					break;
			}
		}
		
		for( gtuint i = 0; i < numAttackCtrl; i++ )
		{
			attacksCtrl[i]->ReceiveAttack( pAttackCheck->GetController() );
		}
		totalNumAttackCtrl += numAttackCtrl;
	}
	return totalNumAttackCtrl;
}

bool GActorCtlrManager::CollisionCheck(GActionAttackCheck* pAttackCheck, GActorController* pCheckCtrl)
{
	if( pCheckCtrl->GetCurrentAction( GAction::ACTION_DIE ) )
		return false;
	GActionAttackCheck* checkAttack = 
	(GActionAttackCheck*)pCheckCtrl->GetActionComponent( GAction::ACTION_ATTACKCHECK );
	
	if( checkAttack == NULL )
		return false;
	Gn2DAVData* avData = pCheckCtrl->GetMesh()->GetAVData();
	if( avData == NULL )
		return false;
	Gn2DAVData::CollisionRect& rect	= avData->GetCollisionRect( 0 );
	if( pAttackCheck->CollisionCheck( checkAttack->GetAttackLine(), rect.mRect ) )
		return true;
	
	return false;
}

bool GActorCtlrManager::CastleCollisionCheck(GActionAttackCheck* pAttackCheck, GCastle* pCheckCastel)
{
	if( pAttackCheck->CollisionCheck( 0, pCheckCastel->GetBottomBodyRect() ) )
		return true;
	if( pAttackCheck->CollisionCheck( 1, pCheckCastel->GetTopBodyRect() ) )
		return true;
	
	return false;
}