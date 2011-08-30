#include "GnGamePCH.h"
#include "GFallBoomAttack.h"

GnImplementCreateAttack(GFallBoomAttack, eIndexItemBomb);

GFarAttack* GFallBoomAttack::CreateAttack(guint32 uIndex)
{
	GFallBoomAttack* attck = GnNew GFallBoomAttack();
	attck->SetAttackCount( 10 );
	attck->CreateAttackMesh( 22 );
	attck->SetOriginalAttackRect( GnFRect(0.0f, 0.0f, 150.0f, 20.0f ) );
	attck->SetStartAttackTime( 0.7f );
	GnTimeController::SetCycleType( GnTimeController::ONCE, attck->GetAttackMesh() );
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
		cPos.x -= 130.0f;
	else
		cPos.x += 130.0f;
	
	GnFRect originalRect = GetOriginalAttackRect();
	originalRect.MoveX( cPos.x );
	originalRect.MoveY( cPos.y );
	SetAttackRect( originalRect );

	cPos.x += 90;
	cPos.y += 100;
	GetAttackMesh()->SetPosition( cPos );
}