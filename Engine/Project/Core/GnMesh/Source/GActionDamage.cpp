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
	, mEffectIndex( -1 )
{
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
	if( mpsMeshObject )
	{
		mpsMeshObject->Update( fTime );
		bool bAllStop = true;
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
}