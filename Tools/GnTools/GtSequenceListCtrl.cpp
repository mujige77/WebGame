// GtSequenceListCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GtSequenceListCtrl.h"

// GtSequenceListCtrl

IMPLEMENT_DYNAMIC(GtSequenceListCtrl, CMFCListCtrl)

GtSequenceListCtrl::GtSequenceListCtrl() : mSelectedItem(-1)
{

}

GtSequenceListCtrl::~GtSequenceListCtrl()
{
}


BEGIN_MESSAGE_MAP(GtSequenceListCtrl, CMFCListCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &GtSequenceListCtrl::OnLvnItemchanged)
END_MESSAGE_MAP()



// GtSequenceListCtrl 메시지 처리기입니다.




int GtSequenceListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	InsertColumn( 0, _T("아이디"), LVCFMT_LEFT, 50 );
	InsertColumn( 1,  _T("이름"), LVCFMT_LEFT, 150 );
	SendMessage( LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	EnableMarkSortedColumn();
	return 0;
}

void GtSequenceListCtrl::ResetData(GtActorObject* pObject)
{
	mSelectedItem = - 1;
	DeleteAllItems();
	mpsCurrentObject = pObject;
	mpsCurrentObject->SetCurrentSequenceInfo( NULL );
	for( guint i = 0 ; i < mpsCurrentObject->GetLoadedSequenceCount() ; i++ )
	{
		AddSequence( mpsCurrentObject->GetSequenceInfo( i ), false );
	}
}

void GtSequenceListCtrl::AddSequence(GtSequenceInfo* pSequence, bool bAddActor)
{
	int itemIndex = GetItemCount();
	GtCString  str;
	str.Format( _T("%d"), pSequence->GetSequenceID() );	
	InsertItem( itemIndex, str );	
	str = pSequence->GetName();
	SetItemText( itemIndex, 1, str.GetWideString() );	
	SetItemData( itemIndex , pSequence->GetSequenceID() );
	if( bAddActor )
		mpsCurrentObject->AddSequenceInfo( pSequence );
}

GtSequenceInfo* GtSequenceListCtrl::FindSequenceFromListItem(gtuint uiNum)
{
	CString str = GetItemText( uiNum, 0 );
	return FindSequenceFromID( str );
}

GtSequenceInfo* GtSequenceListCtrl::FindSequenceFromID(CString strNum)
{
	guint32 num;
	_stscanf_s( strNum, _T("%d"), &num );
	return FindSequenceFromID( num );
}

GtSequenceInfo* GtSequenceListCtrl::FindSequenceFromID(guint32 uiNum)
{
	for( gtuint i = 0 ; i < mpsCurrentObject->GetLoadedSequenceCount() ; i++ )
	{
		GtSequenceInfo* info = mpsCurrentObject->GetSequenceInfo( i );
		if( info->GetSequenceID() == uiNum )
			return info;
	}
	return NULL;
}


void GtSequenceListCtrl::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	if( GetActiveGnFrame() == NULL )
		return;
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	mSelectedItem = pNMLV->iItem;

	GtSequenceMessage sendData;
	if( mpsCurrentObject == NULL )
	{
		sendData.mpSender = this;
		sendData.mpSequenceInfo = NULL;
		SendMediateMessage( GTMG_SELECTSEQUENCE, &sendData );
		return;
	}

	GnPlaneActor* actor = mpsCurrentObject->GetActor();
	if( actor == NULL )
	{
		actor = mpsCurrentObject->CreateActorFromExistData();
	}

	GtSequenceInfo* info = FindSequenceFromListItem( pNMLV->iItem );
	if( info == NULL )
	{
		mpsCurrentObject->SetCurrentSequenceInfo( NULL );
		sendData.mpSender = this;
		sendData.mpSequenceInfo = NULL;
		SendMediateMessage( GTMG_SELECTSEQUENCE, &sendData );
		return;
	}
	
	if( actor->SetTargetAnimation( info->GetSequenceID() ) == false )
	{
		mpsCurrentObject->ResetSequence();
		actor->StopAnimation();
		actor->SetTargetAnimation( info->GetSequenceID() );
	}
	GnFrame* gnFrame = GetActiveGnFrame();
	if( gnFrame )
	{
		gnFrame->RemoveObject( mpsCurrentObject );
		gnFrame->AddObject( mpsCurrentObject );	
	}
	

	mpsCurrentObject->SetCurrentSequenceInfo( info );
	
	
	sendData.mpSender = this;
	sendData.mpSequenceInfo = info;
	SendMediateMessage( GTMG_SELECTSEQUENCE, &sendData );
}

void GtSequenceListCtrl::RemoveCurrentSequence()
{
	if( mSelectedItem == -1 )
		return;
	
	GtCString str = GetItemText( mSelectedItem, 1 );
	DeleteItem( mSelectedItem );
	mpsCurrentObject->RemvoeSequenceInfo( str.GetAciiString() );
}