#include "GnMeshPCH.h"
#include "GnGamePCH.h"
#include "GActionAttack.h"
#include "GActorController.h"
#include "GShootAttack.h"
#include "GMultiShootAttack.h"


GActionAttack::GActionAttack(GActorController* pController) : GAction( pController )
{
	Reset();
}

void GActionAttack::Reset()
{
	SetIsWaitEndAttackAni( false );
}

void GActionAttack::Init(guint32 uiAttackType, guint32 uiAttackCount, guint32 uiAttackDamage)
{
	mAttackType = (eAttackType)uiAttackType;
	mAttackCount = uiAttackCount;
	mAttackDamage = uiAttackDamage;
}

GFarAttack* GActionAttack::CreateFarAttack()
{
	GFarAttack* farAttack = NULL;
	switch( mAttackType )
	{
		case eTypeMissile:
		{
			GMultiShootAttack* attck = GnNew GMultiShootAttack();
			attck->InitShooting( 3.0f, 0.0f );
			
			farAttack = attck;
		}
		break;
		case eTypeIceMagic:
		{
			GMultiShootAttack* attck = GnNew GMultiShootAttack();
			attck->InitShooting( 2.0f, 0.0f );
			attck->GetAttackDamageInfo()->SetDontMoveTime( 5.0f );
			farAttack = attck;			
		}
		break;
		case eTypeMultiMissile:
		{
			GMultiShootAttack* attck = GnNew GMultiShootAttack();
			attck->InitShooting( 2.0f, 0.0f );
			farAttack = attck;
		}
		break;
		case eTypeParabolaBoom:
		{
			GMultiShootAttack* attck = GnNew GMultiShootAttack();
			attck->InitShooting( 2.0f, 0.0f );
			farAttack = attck;
		}
		break;
		default:
		return NULL; 
	}
	farAttack->CreateAttackMesh( GetFarAttackFileIndex() );
	farAttack->SetFilpX( GetController()->GetMesh()->GetFlipX() );
	farAttack->SetAttackCount( mAttackCount );
	farAttack->GetAttackDamageInfo()->SetDamage( mAttackDamage );
	farAttack->GetAttackDamageInfo()->SetAttackType( mAttackType );
	farAttack->SetOriginalAttackRect( GetFarAttackRect( farAttack->GetAttackMesh() ) );
	
	GnVector2ExtraData* pos = (GnVector2ExtraData*)
		GetController()->GetMesh()->GetExtraDataFromType( GExtraData::EXTRA_FARATTACK_POSITION );	
	GnVector2 effectPos = GetController()->GetMesh()->GetPosition();
	if( pos )
	{
		effectPos += pos->GetValueVector2();
	}
	farAttack->SetPosition( effectPos );
	return farAttack;
}

GnFRect GActionAttack::GetFarAttackRect(Gn2DMeshObject* pAttackMesh)
{
	GnVector2ExtraData* pos = (GnVector2ExtraData*)
		GetController()->GetMesh()->GetExtraDataFromType( GExtraData::EXTRA_FARATTACK_POSITION );
	
	if( pos )
	{
		switch( pos->GetID() )
		{
			case 13:
				return GnFRect( 20.0f, -5.0f, 25.0f, 3.0f );
			case 14:
				return GnFRect( 20.0f, -5.0f, 25.0f, 3.0f );
			default:
				break;
		}
	}
	return GnFRect( 0.0f, 0.0f, pAttackMesh->GetSize().x, pAttackMesh->GetSize().y );
}

guint32 GActionAttack::GetFarAttackFileIndex()
{
	GnVector2ExtraData* pos = (GnVector2ExtraData*)
	GetController()->GetMesh()->GetExtraDataFromType( GExtraData::EXTRA_FARATTACK_POSITION );
	
	if( pos )
		return pos->GetID();
	
	return 12;
}