#include "StdAfx.h"
#include "GtTextureAnimationPropEntity.h"
#include "GtPropertyGridFloatSpinProperty.h"
#include "GtPropertyGridProperty.h"
#include "Gt2DTexturePropEntity.h"
#include "GtSMTextureAniCtrl.h"
GtTextureAnimationPropEntity::GtTextureAnimationPropEntity(void) : mpCurrentAniCtrl(NULL)
{
	Init();
}


GtTextureAnimationPropEntity::~GtTextureAnimationPropEntity(void)
{
}

bool GtTextureAnimationPropEntity::Init()
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("텍스쳐 애니메이션 정보"));
	mpProperty = pGroup;

	GtPropertyGridProperty* pProp = NULL;
	pProp = new GtPropertyGridProperty(_T("타겟 이름"), _T(""),
		_T("애니메이션 인덱스를 정합니다."));
	pProp->SetData( MSG_TARGETNAME );
	pProp->AllowEdit( false );
	pGroup->AddSubItem(pProp);

	//pProp = new GtPropertyGridProperty(_T("파일 이름"), _T(""),
	//	_T("애니메이션 인덱스를 정합니다."));
	//pProp->SetData( MSG_FILENAME );
	//pGroup->AddSubItem(pProp);
	//
	GtPropertyGridFloatSpinProperty* spinProp = NULL;
	spinProp = new GtPropertyGridFloatSpinProperty(_T("시작 타임"), (_variant_t) 0.0f,
		_T("애니메이션 인덱스를 정합니다."));
	spinProp->SetData( MSG_STARTTIME );
	spinProp->EnableFloatSpinControl(TRUE, 0, INT_MAX);
	pGroup->AddSubItem(spinProp);
	
	spinProp = new GtPropertyGridFloatSpinProperty(_T("종료 타임"), (_variant_t) 1.0f,
		_T("애니메이션 인덱스를 정합니다."));
	spinProp->SetData( MSG_ENDTIME );
	spinProp->EnableFloatSpinControl(TRUE, 0, INT_MAX);
	pGroup->AddSubItem(spinProp);

	return true;
}

CString GtTextureAnimationPropEntity::GetTargetName()
{
	CMFCPropertyGridProperty* prop = GetTargetNameProperty();
	return prop->GetValue();
}
//CString GtTextureAnimationPropEntity::GetFileName()
//{
//	CMFCPropertyGridProperty* prop = GetFileNameProperty();
//	return prop->GetValue();
//}
//
float GtTextureAnimationPropEntity::GetStartTime()
{
	CMFCPropertyGridProperty* aniTime = GetStartTimeProperty();
	return aniTime->GetValue().fltVal;
}

float GtTextureAnimationPropEntity::GetEndTime()
{
	CMFCPropertyGridProperty* aniTime = GetEndTimeProperty();
	return aniTime->GetValue().fltVal;
}

bool GtTextureAnimationPropEntity::ParseToEntity(GtStreamObject* pObject)
{
	mpCurrentAniCtrl =  (GtSMTextureAniCtrl*)pObject;

	for( gtuint i = 0 ; i < mpCurrentAniCtrl->GetAniInfoCount() ; i++ )
	{
		Gt2DTexturePropEntity* textureProp = GnObjectNew<Gt2DTexturePropEntity>::Create();
		AddChild( textureProp );
		GtSMTextureAniCtrl::AniInfo* aniInfo = mpCurrentAniCtrl->GetAniInfo( i );
		textureProp->ParseToEntity( aniInfo );
		if( i == 0 )
		{
			GetStartTimeProperty()->SetValue( aniInfo->mStartTime );
			GetEndTimeProperty()->SetValue( aniInfo->mEndTime );
		}
	}

	GtCString name = mpCurrentAniCtrl->GetTargetName();
	GetTargetNameProperty()->SetValue( name.GetWideString() );
	return true;
}

bool GtTextureAnimationPropEntity::ParseToObject(GtObject* pObject)
{
//	GnAssert( pObject->IsActor() );	
//	GtCString name = GetAniName();
//	GtCString fileName = GetFileName();	
//	GtActorObject* actor = (GtActorObject*)pObject;	
//	GtSequenceInfo* info = actor->GetSequenceInfo( name.GetAciiString() );
////	if( info == NULL )
////		info = actor->AddNewSequence( name.GetAciiString(), fileName.GetAciiString() );
//	GnSequence* sequence = info->GetSequence();
//	GnAssert( sequence );	
//	
//	int textureCount = mChildren.GetSize();
//	GnSMTextureAniCtrl* ani = GnObjectNew<GnSMTextureAniCtrl>::Create( textureCount );
//	for( int i = 0 ; i < textureCount ; i++ )
//	{
//		GtPropertyEntity* entity = mChildren.GetAt( i );
//		Gt2DTexturePropEntity* child = (Gt2DTexturePropEntity*)entity;
//	}
//
////	actor->SetModifyingSequence( info );

	return true;
}

void GtTextureAnimationPropEntity::ApplyObjectData(CMFCPropertyGridProperty* pChangeProp, GtObject* pCurrentObject)
{
	if( mpCurrentAniCtrl == NULL )
		return;

	for( int i = 0 ; i < mpProperty->GetSubItemsCount() ; i++ )
	{
		CMFCPropertyGridProperty* prop = mpProperty->GetSubItem( i );
		if( prop == pChangeProp )
		{
			GtActorObject* actor = (GtActorObject*)pCurrentObject;
			GnAssert( actor->GetType() == GtActorObject::GTPLANEACTORTYPE );

			for( gtuint j = 0 ; j < mChildren.GetSize() ; j++ )
			{
				Gt2DTexturePropEntity*  textureEntity = (Gt2DTexturePropEntity*)((GtPropertyEntity*)mChildren.GetAt( j ));
				textureEntity->SetStartTime( GetStartTime() );
				textureEntity->SetEndTime( GetEndTime() );
			}
			GnPlaneActor* gnActor = actor->ResetSequence();
			if( gnActor )
			{
				gnActor->StopAnimation();
				gnActor->SetTargetAnimation(actor->GetCurrentSequenceInfo()->GetSequenceID());
			}
			return;
		}
	}

	for( gtuint i = 0 ; i < mChildren.GetSize() ; i++ )
	{
		mChildren.GetAt( i )->ApplyObjectData( pChangeProp, pCurrentObject );
	}
}