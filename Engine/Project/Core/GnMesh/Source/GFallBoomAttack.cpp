#include "GnGamePCH.h"
#include "GFallBoomAttack.h"

GnImplementCreateAttack(GFallBoomAttack, eIndexItemBomb);

GFarAttack* GFallBoomAttack::CreateAttack(guint32 uIndex)
{
	GFallBoomAttack* attck = GnNew GFallBoomAttack();
	attck->SetAttackCount( 7 );
	attck->CreateAttackMesh( 22 );
	attck->SetOriginalAttackRect( GnFRect(0.0f, 0.0f, 140.0f, 10.0f ) );
	attck->SetStartAttackTime( 0.7f );
	attck->GetAttackDamageInfo()->SetAttackType( uIndex );
	GnTimeController::SetCycleType( GnTimeController::ONCE, attck->GetAttackMesh() );
	
	guint32 level = GUserAbility::GetAbilityLevel( eIndexSkillUp );
	attck->GetAttackDamageInfo()->SetDamage( 20 + level * 20  );
	return attck;
}

void GFallBoomAttack::Update(float fTime)
{
	GFarAttack::Update( fTime );
	if( IsStopAnimation() )
	{
		SetIsDestory( true );
	}
}

void GFallBoomAttack::SetPosition(GnVector2 cPos)
{
	if( GetFilpX() )
		cPos.x -= 190.0f;
	else
		cPos.x += 130.0f;
	
	GnFRect originalRect = GetOriginalAttackRect();
	originalRect.MoveX( cPos.x );
	originalRect.MoveY( cPos.y );
	SetAttackRect( originalRect );

	if( GetFilpX() )
		cPos.x += 60.0f;
	else
		cPos.x += 90.0f;

	cPos.y += 100;
	GetAttackMesh()->SetPosition( cPos );
}