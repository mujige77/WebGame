#include "GnGamePCH.h"
#include "GFireAttack.h"

GnImplementCreateAttack(GFireAttack, eIndexItemFire);

GFarAttack* GFireAttack::CreateAttack(guint32 uIndex)
{
	GFireAttack* attck = GnNew GFireAttack();
	attck->SetAttackCount( 10 );
	attck->CreateAttackMesh( 2 );
	attck->SetOriginalAttackRect( GnFRect(-90.0f, -5.0f, 50.0f, 5.0f ) );
	attck->SetStartAttackTime( 0.2f );
	attck->GetAttackDamageInfo()->SetAttackType( uIndex );
	GnTimeController::SetCycleType( GnTimeController::ONCE, attck->GetAttackMesh() );
	
	guint32 level = GUserAbility::GetAbilityLevel( eIndexSkillUp );
	attck->GetAttackDamageInfo()->SetDamage( 10 + level * 10  );
	return attck;
}

void GFireAttack::Update(float fTime)
{
	GFarAttack::Update( fTime );
	if( IsStopAnimation() )
	{
		SetIsDestory( true );
	}
}

void GFireAttack::SetPosition(GnVector2 cPos)
{
	GFarAttack::SetPosition( cPos );
	if( GetFilpX() )
		cPos.x += 50.0f;

	
	GnFRect originalRect = GetOriginalAttackRect();
	originalRect.MoveX( cPos.x );
	originalRect.MoveY( cPos.y );
	SetAttackRect( originalRect );
}