// GtSequenceMainEdiPage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtSequenceMainEdiPage.h"
#include "afxdialogex.h"


// GtSequenceMainEdiPage 대화 상자입니다.

IMPLEMENT_DYNAMIC(GtSequenceMainEdiPage, GtPropertyPage)

GtSequenceMainEdiPage::GtSequenceMainEdiPage() : GtPropertyPage(GtSequenceMainEdiPage::IDD)
{

}

GtSequenceMainEdiPage::~GtSequenceMainEdiPage()
{
}

void GtSequenceMainEdiPage::DoDataExchange(CDataExchange* pDX)
{
	GtPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ET_EDITOR_SEQUENCENAME, mEtSequenceName);
	DDX_Control(pDX, IDC_ET_EDITOR_SEQUENCEFILENAME, mEtSequenctFileName);
	DDX_Control(pDX, IDC_ET_EDITOR_SEQUENCEINDEX, mEtID);
}


BEGIN_MESSAGE_MAP(GtSequenceMainEdiPage, GtPropertyPage)
	ON_EN_CHANGE(IDC_ET_EDITOR_SEQUENCENAME, &GtSequenceMainEdiPage::OnEnChangeSequencename)
	ON_EN_CHANGE(IDC_ET_EDITOR_SEQUENCEFILENAME, &GtSequenceMainEdiPage::OnChangeSequencefilename)
	ON_EN_CHANGE(IDC_ET_EDITOR_SEQUENCEINDEX, &GtSequenceMainEdiPage::OnChangeSequenceindex)
END_MESSAGE_MAP()


BOOL GtSequenceMainEdiPage::OnInitDialog()
{
	GtPropertyPage::OnInitDialog();
	return TRUE;
}

void GtSequenceMainEdiPage::OnEnChangeSequencename()
{
	GtCString strName;
	mEtSequenceName.GetWindowText( strName );
	mpSequence->SetName( strName.GetAciiString() );
	CheckEnableOKButton();
}

void GtSequenceMainEdiPage::OnChangeSequencefilename()
{
	SetFileName();

}

void GtSequenceMainEdiPage::OnChangeSequenceindex()
{
	guint32 sequenceID = 1;
	CString strName;
	mEtID.GetWindowText( strName );
	_stscanf_s( strName, _T("%d"), &sequenceID );
	mpSequence->SetSequenceID( sequenceID );
	CheckEnableOKButton();
}

bool GtSequenceMainEdiPage::CheckEnableButton()
{
	if( GtPropertyPage::CheckEnableButton() == false )
		return false;

	GnSimpleString& aniName = mpSequence->GetName();
	if( aniName.Exists() == NULL )
		return false;	

	if( mpSequence->GetSequenceID() == GUINT32_MAX )
		return false;

	for( gtuint i = 0 ; i < mpActorObject->GetLoadedSequenceCount() ; i++ )
	{
		GtSequenceInfo* sequence = mpActorObject->GetSequenceInfo( i );
		if( sequence->GetSequenceID() == mpSequence->GetSequenceID() )
			return false;
	}
	return true;
}

void GtSequenceMainEdiPage::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SetFileName();
	GtPropertyPage::OnOK();
}

void GtSequenceMainEdiPage::SetFileName()
{
	GtCString strName;
	mEtSequenctFileName.GetWindowText( strName );
	if( strName.IsEmpty() )
	{
		mEtSequenceName.GetWindowText( strName );
	}
	int pos = strName.Find( _T(".") );
	if( pos == -1 )
	{
		strName += _T(".ga");
	}
	mpSequence->SetFileName( strName.GetAciiString() );
}
