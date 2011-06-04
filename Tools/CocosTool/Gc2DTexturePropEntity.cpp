#include "StdAfx.h"
#include "Gc2DTexturePropEntity.h"
#include "GcPropertyGridFileProperty.h"
#include "GcPropertyGridFloatSpinProperty.h"


Gc2DTexturePropEntity::Gc2DTexturePropEntity(void)
{
	Init();
}


Gc2DTexturePropEntity::~Gc2DTexturePropEntity(void)
{
}

bool Gc2DTexturePropEntity::Init()
{
	mUpdateEventSlot.Initialize( this, &Gc2DTexturePropEntity::UpdateEvent );
	GcPropertyGridProperty* pGroup = NULL;
	pGroup = new GcPropertyGridProperty(_T("텍스쳐 애니"));
	mpProperty = pGroup;

	GnAssert( mpProperty );
	GcPropertyGridProperty* proup = NULL;
	proup = new GcPropertyGridProperty(  _T("순서"), (_variant_t)0l, _T("애니메이션 순서를 정합니다.") );	
	proup->EnableSpinControl(TRUE, 0, INT_MAX);
	proup->AllowEdit( true );
	mpProperty->AddSubItem( proup );	

	proup = new GcPropertyGridFileProperty(_T("텍스쳐 정보"),
		TRUE, _T(""), true, _T("IMG"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		gsTextureFileFilter, _T("애니메이션 파일 경로를 표시 합니다.") );
	proup->SetData( MSG_TEXTUREPATH );
	proup->SubscribeToUpdateEvent( &mUpdateEventSlot );
	mpProperty->AddSubItem( proup );

	GcPropertyGridProperty* spinProp = NULL;
	spinProp = new GcPropertyGridProperty(_T("시작 시간"), (_variant_t) 0.0f,
		_T("애니메이션 인덱스를 정합니다."));
	spinProp->SetData( MSG_STARTTIME );
	spinProp->EnableFloatSpinControl(TRUE, 0, INT_MAX);
	spinProp->Show( false );
	mpProperty->AddSubItem(spinProp);

	spinProp = new GcPropertyGridProperty(_T("종료 시간"), (_variant_t) 0.0f,
		_T("애니메이션 인덱스를 정합니다."));
	spinProp->EnableFloatSpinControl(TRUE, 0, INT_MAX);
	spinProp->SetData( MSG_ENDTIME );
	spinProp->Show( false );
	mpProperty->AddSubItem(spinProp);

	mpProperty->Expand();
	return true;
}

void Gc2DTexturePropEntity::SetClearValues()
{
	for( int i = 0 ; i < mpProperty->GetSubItemsCount() ; i++ )
	{
		GcPropertyGridProperty* sub = (GcPropertyGridProperty*)mpProperty->GetSubItem( i );
		sub->SetDefaultValue();
	}
}

void Gc2DTexturePropEntity::SetIndex(int iIndex)
{
	GetTextureNumberProperty()->SetValue( (long)iIndex );
}

void Gc2DTexturePropEntity::SetTextureFilePath(CString strPath)
{
	GcPropertyGridFileProperty* fileProperty = (GcPropertyGridFileProperty*)GetTextureGridFileProperty();
	fileProperty->SetFilePathName( strPath );
}

void Gc2DTexturePropEntity::SetStartTime(float fTime)
{
	GetStartTimeProperty()->SetValue( fTime );
}

void Gc2DTexturePropEntity::SetEndTime(float fTime)
{
	GetEndTimeProperty()->SetValue( fTime );
}

int Gc2DTexturePropEntity::GetIndex()
{
	COleVariant val =  GetTextureNumberProperty()->GetValue();
	return val.intVal;
}

CString Gc2DTexturePropEntity::GetTextureFilePath()
{
	COleVariant val =  GetTextureGridFileProperty()->GetValue();
	return val;
}

CString Gc2DTexturePropEntity::GetTextureFileName()
{
	GcPropertyGridFileProperty* fileProperty = (GcPropertyGridFileProperty*)GetTextureGridFileProperty();		
	return fileProperty->GetFullFilePath();
}

float Gc2DTexturePropEntity::GetStartTime()
{
	COleVariant val =  GetStartTimeProperty()->GetValue();
	return val.fltVal;
}

float Gc2DTexturePropEntity::GetEndTime()
{
	COleVariant val =  GetEndTimeProperty()->GetValue();
	return val.fltVal;
}

bool Gc2DTexturePropEntity::ParseToEntity(EntityData* pEntityData)
{
	ThisEntity* thisEntity = (ThisEntity*)pEntityData;
	mpActor = (Gt2DActor*)(GtObject*)thisEntity->mpObject;
	SetIndex( thisEntity->mAniInfoIndex );
	SetTextureAniIndex( thisEntity->mTextureAniIndex );

	Gn2DTextureAni::TextureAniInfo* aniInfo = thisEntity->mpAniInfo;
	GtConvertString fileName = aniInfo->GetTextureName();
	SetTextureFilePath( fileName.c_str() );
	SetStartTime( aniInfo->GetStartTime() );
	SetEndTime( aniInfo->GetEndTime() );
	return true;
}

void Gc2DTexturePropEntity::UpdateEvent(GcPropertyGridProperty* pChangeProp)
{
	for( int i = 0 ; i < mpProperty->GetSubItemsCount() ; i++ )
	{
		CMFCPropertyGridProperty* prop = mpProperty->GetSubItem( i );
		if( prop == pChangeProp )
		{
			GnAssert( mpActor->GetType() == Gt2DActor::OBJECT_TYPE );
			Gt2DSequence* sequence = mpActor->GetModifySequence();
			if( sequence == NULL )
				return;

			switch( prop->GetData() )
			{
			case MSG_TEXTUREPATH:
				{
					GtConvertString str = GetTextureFileName().GetString();					
					sequence->ChangeTextureFile( GetTextureAniIndex(), GetIndex(), str.GetAciiString() );
					mpActor->GetActor()->StopAnimation();
					mpActor->GetActor()->SetTargetAnimation( sequence->GetSequence()->GetID() );
					SendMediateMessage( GTMG_REDRAW, NULL );
				}
				break;
			case MSG_STARTTIME:
			case MSG_ENDTIME:
				{
					//mpAniInfo->mStartTime = GetStartTime();
					//mpAniInfo->mEndTime = GetEndTime();
					//GnPlaneActor* gnActor = actor->ResetSequence();
				}
				break;
			}
		}
	}
}