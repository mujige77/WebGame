// GcSequenceListCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcSequenceListCtrl.h"

// GcSequenceListCtrl

IMPLEMENT_DYNAMIC(GcSequenceListCtrl, CMFCListCtrl)

GcSequenceListCtrl::GcSequenceListCtrl() : mSelectedItem(-1)
{

}

GcSequenceListCtrl::~GcSequenceListCtrl()
{
}


BEGIN_MESSAGE_MAP(GcSequenceListCtrl, CMFCListCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &GcSequenceListCtrl::OnLvnItemchanged)
END_MESSAGE_MAP()



// GcSequenceListCtrl 메시지 처리기입니다.




int GcSequenceListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	InsertColumn( 0, _T("아이디"), LVCFMT_LEFT, 50 );
	InsertColumn( 1,  _T("이름"), LVCFMT_LEFT, 150 );
	SendMessage( LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	EnableMarkSortedColumn();
	return 0;
}

void GcSequenceListCtrl::ResetData(Gt2DActor* pObject)
{
	mSelectedItem = - 1;
	mpsCurrentActor = pObject;
	if( GetSafeHwnd() )
		DeleteAllItems();
	if( mpsCurrentActor )
	{
		GnActorTool* actorTool = pObject->GetActorTool();
		if( actorTool )
		{
			GnTPrimitiveArray<GtActorTool::SequenceInfo*> sequenceInfos;
			actorTool->GetSequenceInfos( sequenceInfos );
			for( gtuint i = 0 ; i < sequenceInfos.GetSize() ; i++ )
			{
				GtActorTool::SequenceInfo* info = sequenceInfos.GetAt( i );
				AddSequence( info->GetSequenceID(), info->GetSequenceName(), info->GetFileName(), false );
			}
		}
	}
}

void GcSequenceListCtrl::AddSequence(guint32 uiID, const gchar* pcName, const gchar* pcFileName
	, bool bAddActor)
{
	int itemIndex = GetItemCount();
	GtConvertString  str;
	str.Format( _T("%d"), uiID );	
	InsertItem( itemIndex, str.c_str() );	
	str = pcName;
	SetItemText( itemIndex, 1, str.c_str() );
	if( bAddActor )
	{
		GnActorTool* actorTool  = mpsCurrentActor->GetActorTool();
		if( actorTool )
			actorTool->AddSequenceInfo( uiID, pcName, pcFileName );
	}
}

GtActorTool::SequenceInfo* GcSequenceListCtrl::FindSequenceFromListItem(gtuint uiNum)
{
	CString str = GetItemText( uiNum, 0 );
	return FindSequenceFromID( str );
}

GtActorTool::SequenceInfo* GcSequenceListCtrl::FindSequenceFromID(CString strNum)
{
	guint32 num;
	_stscanf_s( strNum, _T("%d"), &num );
	return FindSequenceFromID( num );
}

GtActorTool::SequenceInfo* GcSequenceListCtrl::FindSequenceFromID(guint32 uiNum)
{
	GnActorTool* actorTool = mpsCurrentActor->GetActorTool();
	if( actorTool )
	{
		GtActorTool::SequenceInfo* info = NULL;
		if( actorTool->GetSequenceInfo( uiNum, info ) )
			return info;
	}

	return NULL;
}


void GcSequenceListCtrl::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	mSelectedItem = pNMLV->iItem;
	if( mSelectedItem == -1 )
		return;

	GcSequenceMessage sendData;
	sendData.mpSender = this;
	sendData.mpSequenceInfo= NULL;
	sendData.mpObject = mpsCurrentActor;
	if( mpsCurrentActor == NULL )
	{
		SendMediateMessage( GTMG_SELECTSEQUENCE, &sendData );
		return;
	}

	Gn2DActor* actor = mpsCurrentActor->GetActor();
	if( actor == NULL )
	{
		GnVerify( mpsCurrentActor->LoadData() );
	}

	GtActorTool::SequenceInfo* info = FindSequenceFromListItem( pNMLV->iItem );
	if( info == NULL )
	{
		SendMediateMessage( GTMG_SELECTSEQUENCE, &sendData );
		return;
	}
	
	if( actor->SetTargetAnimation( info->GetSequenceID() ) == false )
	{
		actor->StopAnimation();
		actor->SetTargetAnimation( info->GetSequenceID() );
	}
	
	sendData.mpSequenceInfo = info;
	SendMediateMessage( GTMG_SELECTSEQUENCE, &sendData );
}

void GcSequenceListCtrl::RemoveCurrentSequence()
{
	if( mSelectedItem == -1 )
		return;
	
	if( mpsCurrentActor )
	{
		CString strNum = GetItemText( mSelectedItem, 0 );	
		guint32 num;
		_stscanf_s( strNum, _T("%d"), &num );
		mpsCurrentActor->RemoveSequenceWithTool( num );
	}
	DeleteItem( mSelectedItem );

	if( GetItemCount() == 0 )
	{
		GcSequenceMessage sendData;
		sendData.mpSender = this;
		sendData.mpSequenceInfo = NULL;
		SendMediateMessage( GTMG_SELECTSEQUENCE, &sendData );
	}	
}