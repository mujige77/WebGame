#include "StdAfx.h"
#include "Gt2DTexturePropEntity.h"
#include "GtPropertyGridMultiFileProperty.h"
#include "GtPropertyGridFileProperty.h"
#include "GtPropertyGridFloatSpinProperty.h"
#include "GtTextureDefine.h"
#include <GnSMTextureAniCtrl.h>

Gt2DTexturePropEntity::Gt2DTexturePropEntity(void) : mpAniInfo(NULL)
{
	Init();
}


Gt2DTexturePropEntity::~Gt2DTexturePropEntity(void)
{
}

bool Gt2DTexturePropEntity::Init()
{
	GtPropertyGridProperty* pGroup = NULL;
	pGroup = new GtPropertyGridProperty(_T("텍스쳐 애니"));
	mpProperty = pGroup;

	GnAssert( mpProperty );
	GtPropertyGridProperty* proup = NULL;
	//proup = new GtPropertyGridProperty(  _T("순서"), (_variant_t)0l, _T("애니메이션 순서를 정합니다.") );	
	//proup->EnableSpinControl(TRUE, 0, INT_MAX);
	//proup->AllowEdit( true );
	//mpProperty->AddSubItem( proup );	

	proup = new GtPropertyGridFileProperty(_T("텍스쳐 정보"),
		TRUE, _T(""), true, _T("IMG"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		gsTextureFileFilter, _T("애니메이션 파일 경로를 표시 합니다.") );
	proup->SetData( MSG_TEXTUREPATH );
	mpProperty->AddSubItem( proup );

	GtPropertyGridFloatSpinProperty* spinProp = NULL;
	spinProp = new GtPropertyGridFloatSpinProperty(_T("시작 시간"), (_variant_t) 0.0f,
		_T("애니메이션 인덱스를 정합니다."));
	spinProp->SetData( MSG_STARTTIME );
	spinProp->EnableFloatSpinControl(TRUE, 0, INT_MAX);
	mpProperty->AddSubItem(spinProp);

	spinProp = new GtPropertyGridFloatSpinProperty(_T("종료 시간"), (_variant_t) 0.0f,
		_T("애니메이션 인덱스를 정합니다."));
	spinProp->EnableFloatSpinControl(TRUE, 0, INT_MAX);
	spinProp->SetData( MSG_ENDTIME );
	mpProperty->AddSubItem(spinProp);

	mpProperty->Expand();
	return true;
}

void Gt2DTexturePropEntity::SetClearValues()
{
	for( int i = 0 ; i < mpProperty->GetSubItemsCount() ; i++ )
	{
		GtPropertyGridProperty* sub = (GtPropertyGridProperty*)mpProperty->GetSubItem( i );
		sub->SetDefaultValue();
	}
}

bool Gt2DTexturePropEntity::ParseToEntity(GtStreamObject* pObject)
{
	mpAniInfo =  (GtSMTextureAniCtrl::AniInfo*)pObject;
	//SetIndex( mpAniInfo->mIndex );
	SetStartTime( mpAniInfo->mStartTime );
	SetEndTime( mpAniInfo->mEndTime  );
	GtCString str = mpAniInfo->mTextureFilePath;
	SetTextureFilePath( str.GetWideString() );
	return true;
}

bool Gt2DTexturePropEntity::ParseToObject(GtObject* pObject)
{
	GtActorObject* actor = (GtActorObject*)pObject;
	if( actor == NULL )
		return false;

	
	return true;
}

//void Gt2DTexturePropEntity::SetIndex(int iIndex)
//{
//	GetTextureNumberProperty()->SetValue( (long)iIndex );
//}

void Gt2DTexturePropEntity::SetTextureFilePath(CString strPath)
{
	if( mpAniInfo )
	{
		GtCString str = strPath;
		mpAniInfo->mTextureFilePath = str.GetAciiString();
	}
	GtPropertyGridFileProperty* fileProperty = (GtPropertyGridFileProperty*)GetTextureGridFileProperty();
	fileProperty->SetFilePathName( strPath );
}

void Gt2DTexturePropEntity::SetStartTime(float fTime)
{
	if( mpAniInfo )
		mpAniInfo->mStartTime = fTime;
	GetStartTimeProperty()->SetValue( fTime );
}

void Gt2DTexturePropEntity::SetEndTime(float fTime)
{
	if( mpAniInfo )
		mpAniInfo->mEndTime = fTime;
	GetEndTimeProperty()->SetValue( fTime );
}

//int Gt2DTexturePropEntity::GetIndex()
//{
//	COleVariant val =  GetTextureGridFileProperty()->GetValue();
//	return val.intVal;
//}

CString Gt2DTexturePropEntity::GetTextureFilePath()
{
	COleVariant val =  GetTextureGridFileProperty()->GetValue();
	return val;
}

CString Gt2DTexturePropEntity::GetTextureFileName()
{
	GtPropertyGridFileProperty* fileProperty = (GtPropertyGridFileProperty*)GetTextureGridFileProperty();		
	return fileProperty->GetFullFilePath();
}

float Gt2DTexturePropEntity::GetStartTime()
{
	COleVariant val =  GetStartTimeProperty()->GetValue();
	return val.fltVal;
}

float Gt2DTexturePropEntity::GetEndTime()
{
	COleVariant val =  GetEndTimeProperty()->GetValue();
	return val.fltVal;
}

void Gt2DTexturePropEntity::ApplyObjectData(CMFCPropertyGridProperty* pChangeProp, GtObject* pCurrentObject)
{
	for( int i = 0 ; i < mpProperty->GetSubItemsCount() ; i++ )
	{
		CMFCPropertyGridProperty* prop = mpProperty->GetSubItem( i );
		if( prop == pChangeProp )
		{
			GtActorObject* actor = (GtActorObject*)pCurrentObject;
			GnAssert( actor->GetType() == GtActorObject::GTPLANEACTORTYPE );

			if( mpAniInfo == NULL )
				return;
			
			switch( prop->GetData() )
			{
			case MSG_TEXTUREPATH:
				{
					GtCString str = GetTextureFileName();
					mpAniInfo->mTextureFilePath = str.GetAciiString();
					GnPlaneActor* gnActor = actor->ResetSequence();
					if( gnActor )
					{
						gnActor->StopAnimation();
						gnActor->SetTargetAnimation(actor->GetCurrentSequenceInfo()->GetSequenceID());
					}
				}
				break;
			case MSG_STARTTIME:
			case MSG_ENDTIME:
				{
					mpAniInfo->mStartTime = GetStartTime();
					mpAniInfo->mEndTime = GetEndTime();
					GnPlaneActor* gnActor = actor->ResetSequence();
					if( gnActor )
					{
						gnActor->StopAnimation();
						gnActor->SetTargetAnimation(actor->GetCurrentSequenceInfo()->GetSequenceID());
					}
				}
				break;
			}
		}
	}
}