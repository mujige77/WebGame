#include "GnGamePCH.h"
#include "GBoltAttack.h"

GnImplementCreateAttack(GBoltAttack, eIndexItemBolt);

GFarAttack* GBoltAttack::CreateAttack(guint32 uIndex)
{
	GBoltAttack* attck = GnNew GBoltAttack();
	attck->SetAttackCount( 3 );
	attck->CreateAttackMesh( 21 );
	attck->SetOriginalAttackRect( GnFRect(0.0f, 0.0f, 100.0f, 10.0f ) );
	attck->SetStartAttackTime( 0.2f );
	attck->GetAttackDamageInfo()->SetAttackType( uIndex );
	GnTimeController::SetCycleType( GnTimeController::ONCE, attck->GetAttackMesh() );
	
	guint32 level = GUserAbility::GetAbilityLevel( eIndexSkillUp );
	attck->GetAttackDamageInfo()->SetDamage( 20 + level * 15  );
	return attck;
}

void GBoltAttack::Update(float fTime)
{
	GFarAttack::Update( fTime );
	if( IsStopAnimation() )
	{
		SetIsDestory( true );
	}
}

void GBoltAttack::SetPosition(GnVector2 cPos)
{
	if( GetFilpX() )
		cPos.x -= 165.0f;
	else
		cPos.x += 150.0f;
	
	GnFRect originalRect = GetOriginalAttackRect();
	originalRect.MoveX( cPos.x );
	originalRect.MoveY( cPos.y );
	SetAttackRect( originalRect );
	
	if( GetFilpX() )
		cPos.x += 60.0f;
	else
		cPos.x += 10.0f;
	cPos.y += 60.0f;
	GetAttackMesh()->SetPosition( cPos );
}