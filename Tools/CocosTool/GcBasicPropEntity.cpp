#include "StdAfx.h"
#include "GcBasicPropEntity.h"


GcBasicPropEntity::GcBasicPropEntity(void)
{
	Init();
}


GcBasicPropEntity::~GcBasicPropEntity(void)
{
}

bool GcBasicPropEntity::Init()
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

CString GcBasicPropEntity::GetObjectName()
{
	return mpProperty->GetSubItem( BASIC_OBJECTNAME )->GetValue();
}

CString GcBasicPropEntity::GetObjectFileName()
{
	return mpProperty->GetSubItem( BASIC_FILENAME )->GetValue();
}

gtint GcBasicPropEntity::GetObjectIndex()
{
	const COleVariant& var = mpProperty->GetSubItem( BASIC_INDEX )->GetValue();
	return GetIntValue( var );
}

bool GcBasicPropEntity::ParseToEntity(GtObject* pObject)
{
	//GtObject* gtObject = (GtObject*)pObject;
	//GnAssert( gtObject && gtObject->GetObjectName() );
	//GtConvertString name = gtObject->GetObjectName();
	//CMFCPropertyGridProperty* gridPrperty = mpProperty->GetSubItem( BASIC_OBJECTNAME );
	//gridPrperty->SetValue( name.c_str() );
	//
	//SetObjectFileName( gtObject );
	//SetObjectType( gtObject );

	//gridPrperty = GetIndexProp();
	//gridPrperty->SetValue(  (_variant_t) gtObject->GetIndex() );
	return true;
}

bool GcBasicPropEntity::ParseToObject(GtObject* pObject)
{
	//GtConvertString name = GetObjectName();
	//pObject->SetObjectName( name.GetAciiString() );

	//name = GetObjectFileName();	
	//switch( pObject->GetType() )
	//{
	//case GtObject::OBJECT_TYPE:
	//	{
	//		pObject->SetFileName( name.GetAciiString() );
	//	}
	//	break;
	//case Gt2DActor::OBJECT_TYPE:
	//	{
	//		Gt2DActor* actorObject = (Gt2DActor*)pObject;
	//		actorObject ->SetGATFileName( name.GetAciiString() );
	//	}		
	//	break;
	//}

	//pObject->SetIndex( (gint32)GetObjectIndex() );
	return true;
}

void GcBasicPropEntity::SetObjectType(GtObject* pObject)
{
	CMFCPropertyGridProperty* prop = GetTypeProp();
	switch( pObject->GetType() )
	{
	case Gt2DObject::OBJECT_TYPE:
		{
			prop->SetValue( _T( "2D 모델" ) );			
		}
		break;
	case Gt2DActor::OBJECT_TYPE:
		{
			prop->SetValue( _T( "2D 캐릭터" ) );
		}		
		break;
	}
}

void GcBasicPropEntity::SetObjectFileName(GtObject* pObject)
{
	GtConvertString name;
	CMFCPropertyGridProperty* prop = GetFileNameProp();
	switch( pObject->GetType() )
	{
	case Gt2DObject::OBJECT_TYPE:
		{
			name = pObject->GetObjectName() == NULL ? "" : pObject->GetObjectName();	
			if( name.find( _T(".gm") ) == GtConvertString::npos )
				name += _T(".gm");
		}
		break;
	case Gt2DActor::OBJECT_TYPE:
		{
			Gt2DActor* actorObject = (Gt2DActor*)pObject;
			name = actorObject ->GetGATFileName() == NULL ? "" : actorObject ->GetGATFileName();
			if( name.find( _T(".gat") ) == GtConvertString::npos )
				name += _T(".gat");
		}		
		break;
	}
	prop->SetValue( name.c_str() );
}