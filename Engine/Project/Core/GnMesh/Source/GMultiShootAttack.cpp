#include "GnGamePCH.h"
#include "GMultiShootAttack.h"
#include "GGameDefine.h"

void GMultiShootAttack::RegisterCreateFunction()
{
	static bool bRegistered = false;
	if(bRegistered)
		return;
	
	GFarAttack::RegCreateFunction( eIndexItemMissile, GMultiShootAttack::CreateAttack );
	bRegistered = true;
}

GFarAttack* GMultiShootAttack::CreateAttack(guint32 uiIndex)
{
	GMultiShootAttack* attck = GnNew GMultiShootAttack();
	attck->CreateAttackMesh( 23 );
	attck->InitShooting( 3.0f, 0.0f );
	attck->SetAttackCount( 3 );
	attck->SetOriginalAttackRect( GnFRect(20.0f, -5.0f, 25.0f, 3.0f ) );
	
	if( uiIndex == eIndexItemMissile )
	{
		guint32 level = GUserAbility::GetAbilityLevel( eIndexSkillUp );
		attck->GetAttackDamageInfo()->SetDamage( 10 + level * 5  );
		attck->GetAttackDamageInfo()->SetDamageFileIndex( 25 );
	}
	return attck;
}