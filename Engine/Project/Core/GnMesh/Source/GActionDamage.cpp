//
//  GActionDamage.cpp
//  Core
//
//  Created by Max Yoon on 11. 7. 13..
//  Copyright 2011년 __MyCompanyName__. All rights reserved.
//
#include "GnGamePCH.h"
#include "GActionDamage.h"
#include "GFileList.h"


GActionDamage::GActionDamage(GActorController* pController) : GAction( pController ), mpsMeshObject( NULL )
	, mEffectIndex( -1 ), mPushDelta( GnVector2( 1.0f, 0.0f ) ), mPushDownPosition( GnVector2( 30.0f, 0.0f ) )
	, mPushDamagePosition( GnVector2( 2.0f, 0.0f ) ), mDownTime( 2.0f ), mAttackDamage( 100, 0 )
	, mDontMoveTime( 0.0f ), mDontMoveAcumTime( 0.0f )
{
	SetIsPushDamage( true );
	SetIsDownDamage( false );
	SetIsEndMotion( true );
	SetIsEndPushPosition( true );
	SetIsEndEffectAnimation( true );
	SetIsDontMove( false );
	SetIsIce( false );
	SetIsEnableSetStartAction( true );
	mPushTimer.SetPercentTime( 0.01f );
}

GActionDamage::~GActionDamage()
{
	RemoveMeshParent();
}

GnVector2ExtraData* GActionDamage::CreateDamageEffect()
{
	GnVector2ExtraData* pos = NULL;
	if( mEffectIndex == 1 )
		pos = (GnVector2ExtraData*)
			GetController()->GetMesh()->GetExtraDataFromType( GExtraData::EXTRA_DAMAGE_POSITION );
	else
		pos = (GnVector2ExtraData*)
			GetController()->GetMesh()->GetExtraDataFromType( GExtraData::EXTRA_MISSILEDAMAGE_POSITION );
	
	if( pos )
	{	
		if( mpsMeshObject == NULL )
		{
			gstring fullName;
			if( GetFileList()->GetFullEffectName( mEffectIndex, fullName ) )
			{
				mpsMeshObject = Gn2DMeshObject::CreateFullPath( fullName.c_str(), true );
				if( mpsMeshObject == NULL )
				{
					return NULL;
				}
			}
			else
			{
				return NULL;
			}
		}
	}
	return pos;
}

void GActionDamage::SetAttackDamage(GAttackDamageInfo* pInfo)
{
	mAttackDamage = *pInfo;
	if( mEffectIndex != pInfo->GetDamageFileIndex() )
		mpsMeshObject = NULL;
	mEffectIndex = pInfo->GetDamageFileIndex();	
}

void GActionDamage::Update(float fTime)
{
	mDontMoveAcumTime += fTime;
	if( mpsMeshObject && IsEndEffectAnimation() == false )
	{
		bool bAllStop = true;
		mpsMeshObject->Update( fTime );
		GnTimeController* ctrl = mpsMeshObject->GetTimeControllers();
		GnAssert( ctrl );
		while ( ctrl )
		{
			if( ctrl->GetPlayFlags() != GnTimeController::STOP )
			{
				bAllStop = false;
				break;
			}
			ctrl = ctrl->GetNext();
		}
		if( bAllStop )
		{
			GetActorLayer()->RemoveChild( mpsMeshObject );
			SetIsEndEffectAnimation( true );
		}
	}
	
	if( IsDownDamage() )
	{
		Gn2DSequence* sequence = GetController()->GetActor()->GetCurrentSequence();
		if( sequence && sequence->IsStop() )
		{
			SetIsEndMotion( true );
		}
		if( IsEndPushPosition() == false && UpdatePush( fTime, mPushDownPosition ) )
			SetIsEndPushPosition( true );
	}
	else if( IsPushDamage() )
	{
		if( IsEndPushPosition() == false && UpdatePush( fTime, mPushDamagePosition ) )
			SetIsEndPushPosition( true );
	}
	
	if( IsEnableDamage() )
	{
		if( IsDownDamage() )
		{
			mDownAcumTime += fTime;
			if( mDownTime < mDownAcumTime && mDontMoveTime < mDontMoveAcumTime )
			{
				GetController()->SetStartAction();
				GetController()->RemoveCurrentAction( GAction::ACTION_DAMAGE );
			}
		}
		else if( mDontMoveTime < mDontMoveAcumTime )
		{
			if( IsEnableSetStartAction() )
				GetController()->SetStartAction();
			GetController()->RemoveCurrentAction( GAction::ACTION_DAMAGE );
		}		
	}
}

void GActionDamage::AttachActionToController()
{
	GnVector2ExtraData* posExtraData = CreateDamageEffect();
	if( posExtraData )
	{
		GnVector2 effectPos = GetController()->GetMesh()->GetPosition() + posExtraData->GetValueVector2();
		
		RemoveMeshParent();
		mpsMeshObject->SetPosition( effectPos );
		if( mpsMeshObject->GetMesh()->getParent() == NULL )
			GetActorLayer()->AddChild( mpsMeshObject, GetController()->GetMesh()->GetZOrder() + 1 );
		
		SetIsEndEffectAnimation( false );
	}
	else
		return;
	
	GnTimeController* ctrl = mpsMeshObject->GetTimeControllers();
	GnAssert( ctrl );
	while ( ctrl )
	{
		ctrl->SetCycleType( GnTimeController::ONCE );
		ctrl->Start();
		ctrl = ctrl->GetNext();
	}
	
	if( IsDownDamage() )
	{
		Gn2DSequence* sequence = NULL;
		GetController()->GetActor()->GetSequence( GAction::ANI_DIE, sequence );
		GnAssert( sequence );
		if( sequence )
			sequence->SetLoop( false );
		GetController()->GetActor()->SetTargetAnimation( GAction::ANI_DIE );
		SetIsEndMotion( false );
		GetController()->RemoveAllCurrentAction();
	}	
	if( IsPushDamage() )
	{
		GetController()->RemoveAllCurrentAction();
	}
	SetIsEndPushPosition( false );
	if( IsIce() )
	{
		GetController()->GetActor()->GetRootNode()->SetColor( GnColor( 0.4f, 0.6f, 1.0f ) );
	}
	
	mPushAcum = GnVector2( 0.0f, 0.0f );
}

void GActionDamage::DetachActionToController()
{
	if( mpsMeshObject && mpsMeshObject->GetMesh()->getParent() )
		GetActorLayer()->RemoveChild( mpsMeshObject );
	
	if( IsIce() )
	{
		GetController()->GetActor()->GetRootNode()->SetColor( GnColor( 1.0f, 1.0f, 1.0f ) );
	}
	mDownAcumTime = 0.0f;
	SetIsDownDamage( false );
	SetIsEndEffectAnimation( true );
	SetIsEndMotion( true );
	SetIsEndPushPosition( true );
	SetIsDontMove( false );
	SetIsIce( false );
};

bool GActionDamage::UpdatePush(float fTime, GnVector2& cPosition)
{
	if( mPushTimer.Update( fTime ) )
	{
		GnVector2 movePos = mPushDelta * mPushTimer.GetAmplify();
		GnVector2 acum = movePos + mPushAcum;
		GnVector2 endPos( cPosition.x - fabs( acum.x ), cPosition.y - fabs( acum.y ) );
		if( endPos.x < 0.00000001f )
		{
			if( mPushDelta.x > 0 )
				movePos.x = cPosition.x - mPushAcum.x;
			else
				movePos.x = -( cPosition.x - mPushAcum.x );
		}
		if( endPos.y < 0.00000001f )
		{
			if( mPushDelta.y > 0 )
				movePos.y = cPosition.y - mPushAcum.y;
			else
				movePos.y = -( cPosition.y - mPushAcum.y );
		}
		
		mPushAcum = acum;
		GetController()->SetMoveDeltaPosition( movePos );
		mPushTimer.Reset();
		
		if( endPos.x < 0.00000001f && endPos.y < 0.00000001f )
			return true;
	}
	return false;
}

bool GActionDamage::IsEnableDamage()
{
	return ( IsEndEffectAnimation() && IsEndMotion() && IsEndPushPosition() );
}