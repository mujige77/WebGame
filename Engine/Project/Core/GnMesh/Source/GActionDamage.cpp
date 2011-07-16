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


GActionDamage::GActionDamage(GActorController* pController) : GAction( pController ), mpMeshObject( NULL )
	, mEffectIndex( -1 )
{
}

GActionDamage::~GActionDamage()
{
	RemoveMeshParent();
	if( mpMeshObject )
		GnDelete mpMeshObject;
}

void GActionDamage::Update(float fTime)
{
	if( mpMeshObject )
	{
		mpMeshObject->Update( fTime );
		bool bAllStop = true;
		GnTimeController* ctrl = mpMeshObject->GetTimeControllers();
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
			GetActorLayer()->RemoveChild( mpMeshObject );
			GetController()->RemoveCurrentAction( GAction::ACTION_DAMAGE );
		}
	}
}

void GActionDamage::AttachActionToController()
{
	GnVector2ExtraData* pos = (GnVector2ExtraData*)
	GetController()->GetMesh()->GetExtraDataFromType( GExtraData::EXTRA_DAMAGE_POSITION );
	if( pos )
	{	
		if( mpMeshObject == NULL )
		{
			gstring fullName;
			if( GetFileList()->GetFullEffectName( pos->GetID(), fullName ) )
			{
				mpMeshObject = Gn2DMeshObject::CreateFullPath( fullName.c_str(), true );
				if( mpMeshObject == NULL )
				{
					SetEffectIndexDamage();
					return;
				}
			}
			else
			{
				SetEffectIndexDamage();
				return;
			}
		}
		
		GnVector2 effectPos;
		if( GetController()->GetMesh()->GetFlipX() )
		{
			effectPos = pos->GetValueVector2() - GetController()->GetMesh()->GetFlipCenter();
			effectPos += GetController()->GetMesh()->GetPosition();
		}
		else
		{
			effectPos = GetController()->GetMesh()->GetPosition() + pos->GetValueVector2();
		}
		
		RemoveMeshParent();
		mpMeshObject->SetPosition( effectPos );
		GetActorLayer()->AddChild( mpMeshObject, GetController()->GetMesh()->GetZOrder() + 1 );
	}
	else
	{
		SetEffectIndexDamage();
		return;
	}
	
	
	GnTimeController* ctrl = mpMeshObject->GetTimeControllers();
	GnAssert( ctrl );
	while ( ctrl )
	{
		ctrl->SetCycleType( GnTimeController::ONCE );
		ctrl->Start();
		ctrl = ctrl->GetNext();
	}	
}

void GActionDamage::SetEffectIndexDamage()
{
	
}