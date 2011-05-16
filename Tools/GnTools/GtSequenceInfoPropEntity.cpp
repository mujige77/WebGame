#include "StdAfx.h"
#include "GnTools.h"
#include "GtSequenceInfoPropEntity.h"
#include "GtProperties.h"
#include "GtWindowCreater.h"


GtSequenceInfoPropEntity::MainPropertyGridProperty::MainPropertyGridProperty(const CString& strName, const COleVariant& varValue)
	: GtPropertyGridProperty(strName, varValue)
{
}

void GtSequenceInfoPropEntity::MainPropertyGridProperty::OnClickButton(CPoint /*point*/)
{
	GtProperties& prop = GetWindowCreater()->GetAniProperties();
	if( prop.IsVisible() == false )
		prop.ShowPane(true, false, true);
}

GtSequenceInfoPropEntity::GtSequenceInfoPropEntity(void)
{
	Init();
}


GtSequenceInfoPropEntity::~GtSequenceInfoPropEntity(void)
{
}

bool GtSequenceInfoPropEntity::Init()
{
	MainPropertyGridProperty* pGroup = new MainPropertyGridProperty( _T("시퀀스 정보"), _T( "value")  );
	pGroup->SetEnableGroupButton( true, _T( "시퀀스 수정") );
	mpProperty = pGroup;

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty( _T("시퀀스 아이디"), _T(""), _T("캐릭터 애니메이션") );
	//for( int i = 0 ; i < 20 ; i++ )
	//{
	//	pProp->AddOption(_T("None"), false);
	//	pProp->AddOption(_T("Thin"), false);
	//	pProp->AddOption(_T("Resizable"), false);
	//	pProp->AddOption(_T("Dialog Frame"), false);
	//}
	pProp->SetData( MSG_SEQUENCEID );
	pProp->AllowEdit(FALSE);
	pGroup->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("파일 이름"), (_variant_t) _T(""),
		_T("애니메이션 파일 이름") );
	pProp->AllowEdit( FALSE );
	pProp->SetData( MSG_FILENAME );
	pGroup->AddSubItem(pProp);
	return true;
}

CString GtSequenceInfoPropEntity::GetFileName()
{
	COleVariant rVariant = GetSequenceFileNameProp()->GetValue();
	VARIANT v = rVariant.Detach();
	GnAssert(v.vt == VT_BSTR);
	CString str = OLE2T(v.bstrVal);
	return str;
}

void GtSequenceInfoPropEntity::SetNames(LPCTSTR ptcSequenceName, LPCTSTR ptcFileName)
{
	GetSequenceNameProp()->AddOption( ptcSequenceName, false );
	GetSequenceFileNameProp()->AddOption( ptcFileName, false );
}

CString GtSequenceInfoPropEntity::GetCurrenctSequenceName()
{
	COleVariant rVariant = GetSequenceNameProp()->GetValue();
	VARIANT v = rVariant.Detach();
	GnAssert(v.vt == VT_BSTR);
	CString str = OLE2T(v.bstrVal);
	return str;
}

bool GtSequenceInfoPropEntity::ParseToEntity(GtStreamObject* pObject)
{
	GtActorObject* actorObject = (GtActorObject*)pObject;
	GnAssert( actorObject->GetType() == GtActorObject::GTPLANEACTORTYPE );
	
	guint optionCount = actorObject->GetLoadedSequenceCount();

	if( optionCount <= 0 )
		return true;

	CMFCPropertyGridProperty* sequenceFiles = GetSequenceFileNameProp();
	CMFCPropertyGridProperty* sequenceNames = GetSequenceNameProp();	
	
	for( guint i = 0; i < optionCount ; i++ )
	{
		GtCString names = actorObject->GetSequenceFileName( i );
		sequenceFiles->AddOption( names.GetWideString() );
		names = actorObject->GetSequenceName( i );
		sequenceNames->AddOption( names.GetWideString() );
	}
	return true;
}

bool GtSequenceInfoPropEntity::ParseToObject(GtObject* pObject)
{
	//GtActorObject* actor = GnDynamicCast( GtActorObject, pObject );
	//GnAssert( actor );
	//GnAssert( GetSequenceNameProp() );
	//
	//CMFCPropertyGridProperty* sequenceFiles = GetSequenceFileNameProp();
	//CMFCPropertyGridProperty* sequenceNames = GetSequenceNameProp();	
	//int optionCount = sequenceNames->GetOptionCount();

	//actor->RemoveAllNames();
	//actor->SetSequenceCount( optionCount  );

	//for( int i = 0 ; i < optionCount ; i++ )
	//{
	//	GtCString name =  sequenceNames->GetOption( i );
	//	GtCString filename = sequenceFiles->GetOption( i );
	//	actor->AddNewSequence(name.GetAciiString(), filename.GetAciiString());
	//}
	return true;
}