#include "StdAfx.h"
#include "GcTextureAnimationPropEntity.h"
#include "GcPropertyGridFloatSpinProperty.h"
#include "GcPropertyGridProperty.h"
#include "Gc2DTexturePropEntity.h"

GcTextureAnimationPropEntity::GcTextureAnimationPropEntity(void)
{
	Init();
}


GcTextureAnimationPropEntity::~GcTextureAnimationPropEntity(void)
{
}

bool GcTextureAnimationPropEntity::Init()
{
	mUpdateEventSlot.Initialize( this, &GcTextureAnimationPropEntity::UpdateEvent );

	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("텍스쳐 애니메이션 정보"));
	mpProperty = pGroup;

	GcPropertyGridProperty* pProp = NULL;
	pProp = new GcPropertyGridProperty(_T("에니 인덱스"), 0L,
		_T("애니메이션 인덱스를 정합니다."));
	pProp->SetData( MSG_ANIINDEX );
	pProp->AllowEdit( false );
	pGroup->AddSubItem(pProp);

	//pProp = new GcPropertyGridProperty(_T("파일 이름"), _T(""),
	//	_T("애니메이션 인덱스를 정합니다."));
	//pProp->SetData( MSG_FILENAME );
	//pGroup->AddSubItem(pProp);
	//
	GcPropertyGridProperty* spinProp = NULL;
	spinProp = new GcPropertyGridProperty(_T("시작 타임"), (_variant_t) 0.0f,
		_T("애니메이션 인덱스를 정합니다."));
	spinProp->SetData( MSG_STARTTIME );
	spinProp->EnableFloatSpinControl(TRUE, 0, INT_MAX);
	spinProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	pGroup->AddSubItem(spinProp);
	
	spinProp = new GcPropertyGridProperty(_T("종료 타임"), (_variant_t) 1.0f,
		_T("애니메이션 인덱스를 정합니다."));
	spinProp->SetData( MSG_ENDTIME );
	spinProp->EnableFloatSpinControl(TRUE, 0, INT_MAX);
	spinProp->SubscribeToUpdateEvent( &mUpdateEventSlot );
	pGroup->AddSubItem(spinProp);

	return true;
}

float GcTextureAnimationPropEntity::GetStartTime()
{
	CMFCPropertyGridProperty* aniTime = GetStartTimeProperty();
	return aniTime->GetValue().fltVal;
}

float GcTextureAnimationPropEntity::GetEndTime()
{
	CMFCPropertyGridProperty* aniTime = GetEndTimeProperty();
	return aniTime->GetValue().fltVal;
}

bool GcTextureAnimationPropEntity::ParseToEntity(EntityData* pObject)
{	
	EntityDataTextureAni* thisEntityData = (EntityDataTextureAni*)pObject;
	mpActor = (Gt2DActor*)(GtObject*)thisEntityData->mpObject;
	mpAni = thisEntityData->mpAni;
	for( gtuint i = 0 ; i < mpAni->GetAniInfoCount() ; i++ )
	{
		Gc2DTexturePropEntity* textureProp = GtObjectNew<Gc2DTexturePropEntity>::Create();
		AddChild( textureProp );
		Gn2DTextureAni::TextureAniInfo* aniInfo = (Gn2DTextureAni::TextureAniInfo*)mpAni->GetAniInfo( i );
		
		textureProp->SetIndex( i );
		GtConvertString fileName = aniInfo->GetTextureName();
		textureProp->SetTextureFilePath( fileName.c_str() );
		textureProp->SetStartTime( aniInfo->GetStartTime() );
		textureProp->SetEndTime( aniInfo->GetEndTime() );
		textureProp->SetTextureAniIndex( thisEntityData->mIndex );
		textureProp->GetProperty()->Expand( false );
		if( i == 0 )
		{
			GetAniIndexProperty()->SetValue( thisEntityData->mIndex );
			GetStartTimeProperty()->SetValue( aniInfo->GetStartTime() );
			GetEndTimeProperty()->SetValue( aniInfo->GetEndTime() );
		}
	}	
	return true;
}

bool GcTextureAnimationPropEntity::ParseToObject(EntityData* pObject)
{
//	GnAssert( pObject->IsActor() );	
//	GtConvertString name = GetAniName();
//	GtConvertString fileName = GetFileName();	
//	Gt2DActor* actor = (Gt2DActor*)pObject;	
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
//		GcPropertyEntity* entity = mChildren.GetAt( i );
//		Gc2DTexturePropEntity* child = (Gc2DTexturePropEntity*)entity;
//	}
//
////	actor->SetModifyingSequence( info );
	return true;
}

void GcTextureAnimationPropEntity::ApplyObjectData(CMFCPropertyGridProperty* pChangeProp
	, EntityData* pCurrentObject)
{
	//for( int i = 0 ; i < mpProperty->GetSubItemsCount() ; i++ )
	//{
	//	CMFCPropertyGridProperty* prop = mpProperty->GetSubItem( i );
	//	if( prop == pChangeProp )
	//	{
	//		Gt2DActor* actor = (Gt2DActor*)pCurrentObject;
	//		GnAssert( actor->GetType() == Gt2DActor::OBJECT_TYPE );

	//		for( gtuint j = 0 ; j < mChildren.GetSize() ; j++ )
	//		{
	//			Gc2DTexturePropEntity*  textureEntity = (Gc2DTexturePropEntity*)((GcPropertyEntity*)mChildren.GetAt( j ));
	//			textureEntity->SetStartTime( GetStartTime() );
	//			textureEntity->SetEndTime( GetEndTime() );
	//		}
	//		Gn2DActor* gnActor = actor->GetActor();
	//		if( gnActor )
	//		{
	//			gnActor->StopAnimation();
	//			gnActor->SetTargetAnimation(actor->GetCurrentSequenceInfo()->GetSequenceID());
	//		}
	//		return;
	//	}
	//}

	//for( gtuint i = 0 ; i < mChildren.GetSize() ; i++ )
	//{
	//	mChildren.GetAt( i )->ApplyObjectData( pChangeProp, pCurrentObject );
	//}
}

void GcTextureAnimationPropEntity::UpdateEvent(GcPropertyGridProperty* pChangedGridProperty)
{
	if( mpAni == NULL || mpActor == NULL || mpActor->GetModifySequence() == NULL )
		return;

	switch( pChangedGridProperty->GetData() )
	{
	case MSG_STARTTIME:
		{

		}
		break;
	case MSG_ENDTIME:
		{
			GnAssert( mpActor->GetType() == Gt2DActor::OBJECT_TYPE);

			for( gtuint i = 0 ; i < mChildren.GetSize() ; i++ )
			{
				Gc2DTexturePropEntity*  textureEntity 
					= (Gc2DTexturePropEntity*)((GcPropertyEntity*)mChildren.GetAt( i ));
				textureEntity->SetStartTime( GetStartTime() );
				textureEntity->SetEndTime( GetEndTime() );
			}

			float sequenceEndTime = 0.0f;
			for( gtuint i = 0 ; i < mpAni->GetAniInfoCount() ; i++ )
			{
				Gn2DTextureAni::TextureAniInfo* aniInfo = (Gn2DTextureAni::TextureAniInfo*)mpAni->GetAniInfo( i );
				aniInfo->SetEndTime( GetEndTime() );
				sequenceEndTime += GetEndTime();
			}
			mpAni->SetAniSpeed( GetEndTime() );
			mpActor->GetModifySequence()->GetSequence()->SetEndTime( sequenceEndTime );
			SendMediateMessage( GTMG_CHAGESEQUENCEANITIME, NULL );

		}
		break;
	default:
		return;
	}
	mpActor->GetModifySequence()->SetModifed( true );
}