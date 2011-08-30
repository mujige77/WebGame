#include "GnGamePCH.h"
#include "GFireAttack.h"

GnImplementCreateAttack(GFireAttack, eIndexItemFire);

GFarAttack* GFireAttack::CreateAttack(guint32 uIndex)
{
	GFireAttack* attck = GnNew GFireAttack();
	attck->SetAttackCount( 10 );
	attck->CreateAttackMesh( 2 );
	attck->SetOriginalAttackRect( GnFRect(-90.0f, -10.0f, 50.0f, 10.0f ) );
	attck->SetStartAttackTime( 0.2f );
	GnTimeController::SetCycleType( GnTimeController::ONCE, attck->GetAttackMesh() );
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

//void GFireAttack::SetPosition(GnVector2 cPos)
//{
//	if( GetFilpX() )
//		cPos.x -= 150.0f;
//	else
//		cPos.x += 150.0f;
//	
//	GnFRect originalRect = GetOriginalAttackRect();
//	originalRect.MoveX( cPos.x );
//	originalRect.MoveY( cPos.y );
//	SetAttackRect( originalRect );
//	
//	cPos.x += 10.0f;
//	cPos.y += 60.0f;
//	GetAttackMesh()->SetPosition( cPos );
//}