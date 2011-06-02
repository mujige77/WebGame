// GcSequenceModifyDockable.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcSequenceModifyDockable.h"
#include "GcSequenceTimeDlg.h"
#include "GcSequenceCollisionDlg.h"

// GcSequenceModifyDockable

GcSequenceModifyDockable::GcSequenceModifyDockable() : mCurrentAniTime(0.0f)
{

}

GcSequenceModifyDockable::~GcSequenceModifyDockable()
{
}


BEGIN_MESSAGE_MAP(GcSequenceModifyDockable, GcToolBarDockable)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// GcSequenceModifyDockable 메시지 처리기입니다.




int GcSequenceModifyDockable::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!mTabCtrl.Create (CMFCTabCtrl::STYLE_FLAT, CRect (0, 0, 0, 0), this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}

	// Create toolbar:
	mTabCtrl.SetFlatFrame (FALSE, FALSE);
	mTabCtrl.AutoDestroyWindow (FALSE);

	AttachNeedMessage( GTMG_SELECTOBJECT );
	AttachNeedMessage( GTMG_SELECTSEQUENCE );
	AttachNeedMessage( GTMG_DESTORY );
	AttachNeedMessage( GTMG_TIMECHANGE );
	return 0;
}

void GcSequenceModifyDockable::AddTab(CWnd* pAddWnd, CString strName)
{
	mTabCtrl.AddTab( pAddWnd, strName );
}

void GcSequenceModifyDockable::RemoveAllTab()
{
	for (int i = 0; i < mTabCtrl.GetTabsNum (); i++)
	{
		CWnd* pWnd = mTabCtrl.GetTabWnd (i);
		pWnd->DestroyWindow ();
		delete pWnd;
	}
	if( mTabCtrl.GetSafeHwnd() )
		mTabCtrl.RemoveAllTabs();
}

void GcSequenceModifyDockable::ReceiveMediateMessage(gtuint messageIndex
	, GcMediateObjectMessage* pMessage)
{
	switch( messageIndex )
	{
	case GTMG_TIMECHANGE:
		if( pMessage->mTempMessage )
			SetCurrentAniTime( *((float*)pMessage->mTempMessage) );
		break;
	case GTMG_SELECTOBJECT:
		{
			ChangeProperty( pMessage );
		}
		break;
	case GTMG_SELECTSEQUENCE:
		{
			ChangeSequence( pMessage );
		}
		break;
	}
}

void GcSequenceModifyDockable::ChangeProperty(GcMediateObjectMessage* pMessage)
{
	 mpsCurrentObject = pMessage->mpObject;
	 RemoveAllTab();
}

void GcSequenceModifyDockable::ChangeSequence(GcMediateObjectMessage* pMessage)
{
	int activeTab = -1;
	if( mTabCtrl.GetSafeHwnd() )
	{
		activeTab = mTabCtrl.GetActiveTab();
	}
	GcSequenceMessage* sequenceMessage = (GcSequenceMessage*)pMessage;
	if( sequenceMessage->mpSequenceInfo == NULL )
	{
		RemoveAllTab();
		return;
	}
	RemoveAllTab();

	Gt2DActor* actor = (Gt2DActor*)(GtObject*)sequenceMessage->mpObject;
	Gt2DSequence* gtSequence = NULL;
	if( actor->GetGtSequence( sequenceMessage->mpSequenceInfo->GetSequenceID(), gtSequence )
		== false )
		return;

	GcSequenceTimeDlg* timeDlg = new GcSequenceTimeDlg();
	timeDlg->Create( GcSequenceTimeDlg::IDD, &mTabCtrl );
	timeDlg->ResetData( gtSequence );
	timeDlg->SetCurrentAniTime( mCurrentAniTime );
	AddTab( timeDlg, _T("TimeKey") );

	GcSequenceCollisionDlg* collisionDlg = new GcSequenceCollisionDlg();
	collisionDlg->Create( GcSequenceCollisionDlg::IDD, &mTabCtrl );
	collisionDlg->ResetData( actor, gtSequence );
	AddTab( collisionDlg, _T("Collision") );

	if( activeTab != -1 )
		mTabCtrl.SetActiveTab( activeTab );
}

void GcSequenceModifyDockable::OnSize(UINT nType, int cx, int cy)
{
	GcToolBarDockable::OnSize(nType, cx, cy);

	CRect rectClient;
	GetClientRect (rectClient);
	mTabCtrl.SetWindowPos (NULL, rectClient.left, rectClient.top, 
		rectClient.Width (), rectClient.Height (),
		SWP_NOACTIVATE | SWP_NOZORDER);
}


void GcSequenceModifyDockable::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	GcToolBarDockable::PostNcDestroy();
}
