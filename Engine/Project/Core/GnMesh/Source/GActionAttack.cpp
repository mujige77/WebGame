#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GActionAttack.h"
#include "GActorController.h"

GActionAttack::GActionAttack(GActorController* pController) : GAction( pController )
{
	Reset();
}

void GActionAttack::Reset()
{
	SetIsWaitEndAttackAni( false );	
}