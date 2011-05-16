#include "StdAfx.h"
#include "GtScreenMeshPropEntity.h"
#include "GtBoundedNumberPairProp.h"
#include <memory>

GtScreenMeshPropEntity::GtScreenMeshPropEntity(void)
{
	Init();
}


GtScreenMeshPropEntity::~GtScreenMeshPropEntity(void)
{
}

bool GtScreenMeshPropEntity::Init()
{
	GtPropertyGridProperty* pGroup = NULL;
	pGroup = new GtPropertyGridProperty(_T("메쉬 정보"));
	mpProperty = pGroup;

	GtPropertyGridProperty* pProp = NULL;
	pProp = new GtPropertyGridProperty(_T("파일 이름"), (_variant_t) _T(""),
		_T("캐릭터 이름을 지정합니다."));	
	pProp->AllowEdit( FALSE );
	pGroup->AddSubItem( pProp );

	std::auto_ptr<CMFCPropertyGridProperty> apSize(new GtBoundedNumberPairProp(_T("Mesh Scale Info")
		, 0, GINT_MAX, 0, GINT_MAX, 0, TRUE));
	apSize->AllowEdit( false );
	pProp = new GtBoundedNumberSubProp(_T("Height"), (COleVariant) 250l, 0, GINT_MAX, _T("Specifies the dialog's height"));
	pProp->EnableSpinControl( TRUE, 0, GINT_MAX );
	pProp->SetData( MSG_HEIGHT );
	apSize->AddSubItem( pProp );

	pProp = new GtBoundedNumberSubProp( _T("Width"), (COleVariant) 150l, 0, GINT_MAX, _T("Specifies the dialog's width"));
	pProp->EnableSpinControl( TRUE, 0, GINT_MAX );
	pProp->SetData( MSG_WIDTH );
	apSize->AddSubItem( pProp );

	pGroup->AddSubItem( apSize.release() );
	return true;
}

bool GtScreenMeshPropEntity::ParseToEntity(GtStreamObject* pObject)
{
	GtObject* gtObject = (GtObject*)pObject;
	GnVector2 scale = gtObject->GetScale();
	GtCString fileName = gtObject->GetFileName();
	GetFileNameProp()->SetValue( fileName );
	GetHeightProp()->SetValue( (COleVariant)(long)scale.y );
	GetWidthProp()->SetValue( (COleVariant)(long)scale.x );
	return true;
}

bool GtScreenMeshPropEntity::ParseToObject(GtObject* pObject)
{
	GtCString fileName = (CString)GetFileNameProp()->GetValue();
	pObject->SetFileName( fileName.GetAciiString() );

	int height = GetIntValue( GetHeightProp()->GetValue() );
	int width = GetIntValue( GetWidthProp()->GetValue() );
	pObject->ChanageScale( width, height );
	return true;
}