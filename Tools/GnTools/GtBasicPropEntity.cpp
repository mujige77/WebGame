#include "StdAfx.h"
#include "GtBasicPropEntity.h"


GtBasicPropEntity::GtBasicPropEntity(void)
{
	Init();
}


GtBasicPropEntity::~GtBasicPropEntity(void)
{
}

bool GtBasicPropEntity::Init()
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("기본 정보"));
	mpProperty = pGroup;
	
	CMFCPropertyGridProperty* pProp = NULL;
	pProp = new CMFCPropertyGridProperty(_T("오브젝트 이름"), (_variant_t) _T(""),
		_T("캐릭터 이름을 지정합니다."));	
	pProp->SetData( MSG_OBJECTNAME );

	pGroup->AddSubItem(pProp);
	
	pProp = new CMFCPropertyGridProperty(_T("오브젝트 종류"), (_variant_t) _T("2D 캐릭터"),
		_T("캐릭터 이름을 지정합니다."));
	pProp->AllowEdit( FALSE );
	pProp->SetData( MSG_OBJECTTYPE );

	pGroup->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("파일 이름"), (_variant_t) _T(""),
		_T("파일 이름을 지정합니다."));	
	pProp->SetData( MSG_FILENAME );

	pGroup->AddSubItem(pProp);

	//static const TCHAR szFilter[] = _T("Image (*.GAT, *.GAA, *.GM) | *.GAT;*.GAA;*.GM | All Files(*.*)|*.*||");
	//pProp = new CMFCPropertyGridFileProperty(_T("파일 경로"), TRUE, _T(""), _T(""),
	//	OFN_HIDEREADONLY | OFN_READONLY, szFilter, _T("현재 선택된 모델의 파일 이름 입니다."));
	//pGroup->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("인덱스 번호"), (_variant_t) 0,
		_T("캐릭터 인덱스를 지정합니다."), 0 );
	pProp->SetData( MSG_OBJECTINDEX );
	pProp->EnableSpinControl( TRUE, 0, 500000 );

	pGroup->AddSubItem(pProp);

	return true;
}

CString GtBasicPropEntity::GetObjectName()
{
	return mpProperty->GetSubItem( BASIC_OBJECTNAME )->GetValue();
}

CString GtBasicPropEntity::GetObjectFileName()
{
	return mpProperty->GetSubItem( BASIC_FILENAME )->GetValue();
}

gtint GtBasicPropEntity::GetObjectIndex()
{
	const COleVariant& var = mpProperty->GetSubItem( BASIC_INDEX )->GetValue();
	return GetIntValue( var );
}

bool GtBasicPropEntity::ParseToEntity(GtStreamObject* pObject)
{
	GtObject* gtObject = (GtObject*)pObject;
	GnAssert( gtObject && gtObject->GetObjectName() );
	GtCString name = gtObject->GetObjectName();
	CMFCPropertyGridProperty* gridPrperty = mpProperty->GetSubItem( BASIC_OBJECTNAME );
	gridPrperty->SetValue( name.GetString() );
	
	SetObjectFileName( gtObject );
	SetObjectType( gtObject );

	gridPrperty = GetIndexProp();
	gridPrperty->SetValue(  (_variant_t) gtObject->GetIndex() );
	return true;
}

bool GtBasicPropEntity::ParseToObject(GtObject* pObject)
{
	GtCString name = GetObjectName();
	pObject->SetObjectName( name.GetAciiString() );

	name = GetObjectFileName();	
	switch( pObject->GetType() )
	{
	case GtObject::GTOBJECTTYPE:
		{
			pObject->SetFileName( name.GetAciiString() );
		}
		break;
	case GtActorObject::GTPLANEACTORTYPE:
		{
			GtActorObject* actorObject = (GtActorObject*)pObject;
			actorObject ->SetGATFileName( name.GetAciiString() );
		}		
		break;
	}

	pObject->SetIndex( (gint32)GetObjectIndex() );
	return true;
}

void GtBasicPropEntity::SetObjectType(GtObject* pObject)
{
	CMFCPropertyGridProperty* prop = GetTypeProp();
	switch( pObject->GetType() )
	{
	case GtObject::GTOBJECTTYPE:
		{
			prop->SetValue( _T( "2D 모델" ) );			
		}
		break;
	case GtActorObject::GTPLANEACTORTYPE:
		{
			prop->SetValue( _T( "2D 캐릭터" ) );
		}		
		break;
	}
}

void GtBasicPropEntity::SetObjectFileName(GtObject* pObject)
{
	GtCString name;
	CMFCPropertyGridProperty* prop = GetFileNameProp();
	switch( pObject->GetType() )
	{
	case GtObject::GTOBJECTTYPE:
		{
			name = pObject->GetFileName() == NULL ? "" : pObject->GetFileName();	
			if( name.Find( _T(".gm") ) == -1 )
				name += _T(".gm");
		}
		break;
	case GtActorObject::GTPLANEACTORTYPE:
		{
			GtActorObject* actorObject = (GtActorObject*)pObject;
			name = actorObject ->GetGATFileName() == NULL ? "" : actorObject ->GetGATFileName();
			if( name.Find( _T(".gat") ) == -1 )
				name += _T(".gat");
		}		
		break;
	}
	prop->SetValue( name.GetString() );
}