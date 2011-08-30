#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GActorCtlrManager.h"
#include "GActionAttackCheck.h"
#include "GInfoBasic.h"
#include "GAttackDamageInfo.h"

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
	for( gtuint i = 0; i < GetActorCtlrSize() ; i++ )
	{
		GActorController* actorCtlr = GetActorCtlr( i );
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
	
	for( gtuint i = 0; i < GetFarAttackSize() ; i++ )
	{
		GFarAttack* attack = GetFarAttack( i );
		if( attack->IsDestory() )
		{
			RemoveFarAttack( i );
			--i;
		}
		else
		{
			attack->Update( fDeltaTime );
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
	
	for( gtuint i = 0; i < GetFarAttackSize() ; i++ )
	{
		GFarAttack* attack = GetFarAttack( i );
		if( attack->IsEnableAttack() && attack->IsReadyAttack() )
		{
			for ( gtuint j = 0; j < pCheckCtlrManager->GetActorCtlrSize(); j++ )
			{
				GActorController* checkCtrl = pCheckCtlrManager->GetActorCtlr( j );			
				if( FarAttackCollisionCheck( attack, checkCtrl ) )
				{
					checkCtrl->ReceiveAttack( attack->GetAttackDamageInfo() );
					attack->SendedAttackTo();
					if( attack->EnableNextAttack() == false )
						break;
				}
			}
			attack->EndedAttackTo();
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

	// attack enemy
	gtuint enableAttackCount = pAttackCheck->GetEnableAttackCount();
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
		GInfoBasic* fromActorBasic = (GInfoBasic*)pAttackCheck->GetController()->GetInfoComponent( GInfo::INFO_BASIC );
		GAttackDamageInfo damage( fromActorBasic->GetStrength() );
		attacksCtrl[i]->ReceiveAttack( &damage );
	}
	totalNumAttackCtrl += numAttackCtrl;
	
	
	// attack castle if ramains	attack count
	if( totalNumAttackCtrl < enableAttackCount )
	{
		GCastle* castle = pCheckCtlrManager->GetCastle();
		if( castle && CastleCollisionCheck( pAttackCheck, castle ) )
		{
			GInfoBasic* fromActorBasic = 
			(GInfoBasic*)pAttackCheck->GetController()->GetInfoComponent( GInfo::INFO_BASIC );
			castle->ReceveAttack( (gint32)fromActorBasic->GetStrength() );
			++totalNumAttackCtrl;
		}	
	}
	return totalNumAttackCtrl;
}

bool GActorCtlrManager::CollisionCheck(GActionAttackCheck* pAttackCheck, GActorController* pCheckCtrl)
{
	GActionAttackCheck* checkAttack = EnableAttackToCtrl( pCheckCtrl );
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

bool GActorCtlrManager::FarAttackCollisionCheck(GFarAttack* pFarAttack, GActorController* pCheckCtrl)
{
	GActionAttackCheck* checkAttack = EnableAttackToCtrl( pCheckCtrl );
	if( checkAttack == NULL )
		return false;
	
	Gn2DAVData* avData = pCheckCtrl->GetMesh()->GetAVData();
	if( avData == NULL )
		return false;
	
	Gn2DAVData::CollisionRect& rect	= avData->GetCollisionRect( 0 );
	GnFRect& attackRect = pFarAttack->GetAttackRect();
	if( ( attackRect.ContainsRectHeight( rect.mRect ) || rect.mRect.ContainsRectHeight( attackRect ) )
	   && ( rect.mRect.ContainsRectWidth( attackRect ) || attackRect.ContainsRectWidth( rect.mRect ) ) )
		return true;
	
	return false;
}

GActionAttackCheck* GActorCtlrManager::EnableAttackToCtrl(GActorController* pCtrl)
{
	if( pCtrl->GetCurrentAction( GAction::ACTION_DIE ) )
		return NULL;
	
	GActionAttackCheck* checkAttack = 
		(GActionAttackCheck*)pCtrl->GetActionComponent( GAction::ACTION_ATTACKCHECK );
	
	return checkAttack;
}
