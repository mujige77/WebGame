// GcSequenceModifyDockable.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcSequenceModifyDockable.h"
#include "GcSequenceTimeDlg.h"
#include "GcSequenceCollisionDlg.h"
#include "GcExtraDataDlg.h"

const gtchar* GcSequenceModifyDockable::msSequenceCollisionDlgName = _T("Collision");
const gtchar* GcSequenceModifyDockable::msSequenceTimeDlgName = _T("TimeKey");
const gtchar* GcSequenceModifyDockable::msActorExtraDlgName = _T("ActorExtra");
const gtchar* GcSequenceModifyDockable::ms2DObjectExtraDlgName = _T("2DObjectExtra");

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

	if ( !mTabCtrl.Create(CMFCTabCtrl::STYLE_FLAT, CRect (0, 0, 0, 0), this, 1
		, CMFCTabCtrl::LOCATION_TOP ) )
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}

	// Create toolbar:
	mTabCtrl.SetFlatFrame(FALSE, FALSE);
	mTabCtrl.AutoDestroyWindow(FALSE);


	AttachNeedMessage( GTMG_SELECTOBJECT );
	AttachNeedMessage( GTMG_SELECTSEQUENCE );
	AttachNeedMessage( GTMG_DESTORY );
	AttachNeedMessage( GTMG_TIMECHANGE );
	AttachNeedMessage( GTMG_SELECT2DOBJECT );
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

void GcSequenceModifyDockable::RemoveSequenceTab()
{
	for (int i = 0; i < mTabCtrl.GetTabsNum (); i++)
	{
		CWnd* pWnd = mTabCtrl.GetTabWnd (i);
		CString name;
		pWnd->GetWindowText( name );
		if( name == msSequenceCollisionDlgName || name == msSequenceTimeDlgName )
		{
			if( mTabCtrl.GetSafeHwnd() )
				mTabCtrl.RemoveTab( i-- );
			pWnd->DestroyWindow();
			delete pWnd;
		}
	}
}

void GcSequenceModifyDockable::RemoveSequence(const gtchar* pcName)
{
	for (int i = 0; i < mTabCtrl.GetTabsNum (); i++)
	{
		CWnd* pWnd = mTabCtrl.GetTabWnd (i);
		CString name;
		pWnd->GetWindowText( name );
		if( name == pcName )
		{
			if( mTabCtrl.GetSafeHwnd() )
				mTabCtrl.RemoveTab( i-- );
			pWnd->DestroyWindow();
			delete pWnd;
			return;
		}
	}
}

void GcSequenceModifyDockable::SetActiveTab(CString strActiveName)
{
	for (int i = 0; i < mTabCtrl.GetTabsNum(); i++)
	{
		CWnd* pWnd = mTabCtrl.GetTabWnd (i);
		CString name;
		pWnd->GetWindowText( name );
		if( name == strActiveName )
		{
			if( mTabCtrl.GetSafeHwnd() )
				mTabCtrl.SetActiveTab( i );
			break;
		}
	}
	CWnd* ActorExtraTab = NULL;
	CWnd* Object2DTab = NULL;
	GnTPrimitiveArray<CWnd*> othecrTabs(5, 5);
	for (int i = 0; i < mTabCtrl.GetTabsNum (); i++)
	{
		CWnd* pWnd = mTabCtrl.GetTabWnd(i);
		CString name;
		pWnd->GetWindowText( name );
		if( name == msActorExtraDlgName )
		{
			ActorExtraTab = pWnd;
			mTabCtrl.RemoveTab( i-- );
		}
		else if( name == ms2DObjectExtraDlgName )
		{
			Object2DTab = pWnd;
			mTabCtrl.RemoveTab( i-- );
		}
		else
		{
			othecrTabs.Add( pWnd );
			mTabCtrl.RemoveTab( i-- );
		}
	}
	if( ActorExtraTab )
		mTabCtrl.AddTab( ActorExtraTab, msActorExtraDlgName );
	if( Object2DTab )
		mTabCtrl.AddTab( Object2DTab, ms2DObjectExtraDlgName );

	for( gtuint i = 0; i < othecrTabs.GetSize(); i++ )
	{
		CString name;
		othecrTabs.GetAt( i )->GetWindowText( name );
		mTabCtrl.AddTab( othecrTabs.GetAt( i ), name );
	}
}

void GcSequenceModifyDockable::ReceiveMediateMessage(gtuint messageIndex
	, GcMediateObjectMessage* pMessage)
{
	switch( messageIndex )
	{
	case GTMG_DESTORY:
		mps2DObject = NULL;
		mpsActorObject = NULL;
		RemoveAllTab();
		break;
	case GTMG_TIMECHANGE:
		if( pMessage->mTempMessage )
			SetCurrentAniTime( *((float*)pMessage->mTempMessage) );
		break;
	case GTMG_SELECTOBJECT:
	case GTMG_SELECT2DOBJECT:
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
	CString activeName;
	if( mTabCtrl.GetSafeHwnd() )
	{
		CWnd* wnd = mTabCtrl.GetActiveWnd();
		if( wnd )
			wnd->GetWindowText( activeName );
	}

	CWnd* focus = GetFocus();

	GtObject* changeObject = pMessage->mpObject;
	if( changeObject )
	{
		const gtchar* dlgName = NULL;
		Gn2DMeshObject* meshObject = NULL;
		Gt2DActor* actor = GnDynamicCast(Gt2DActor,  changeObject );
		if( actor == NULL )
		{
			dlgName = ms2DObjectExtraDlgName;
			mps2DObject = changeObject;
			Gt2DObject* Object2D = GnDynamicCast(Gt2DObject,  mps2DObject );
			if( Object2D )
				meshObject = Object2D->Get2DMeshObjecct();
		}
		else
		{
			RemoveSequenceTab();
			dlgName = msActorExtraDlgName;
			mpsActorObject = changeObject;
			meshObject = actor->GetRootNode();
		}
			
		if( meshObject )
		{
			RemoveSequence( dlgName );
			GcExtraDataDlg* timeDlg = new GcExtraDataDlg();
			timeDlg->Create( GcExtraDataDlg::IDD, &mTabCtrl );		
			timeDlg->ResetData( changeObject, meshObject );
			timeDlg->SetWindowText( dlgName );
			AddTab( timeDlg, dlgName );
			SetActiveTab( activeName );
		}		
	}

	::SetFocus( focus->GetSafeHwnd() );
}

void GcSequenceModifyDockable::ChangeSequence(GcMediateObjectMessage* pMessage)
{
	CWnd* focus = GetFocus();
	int activeTab = -1;
	if( mTabCtrl.GetSafeHwnd() )
	{
		activeTab = mTabCtrl.GetActiveTab();
	}
	GcSequenceMessage* sequenceMessage = (GcSequenceMessage*)pMessage;
	if( sequenceMessage->mpSequenceInfo == NULL )
	{
		RemoveSequenceTab();
		return;
	}
	RemoveSequenceTab();

	Gt2DActor* actor = (Gt2DActor*)(GtObject*)sequenceMessage->mpObject;
	Gt2DSequence* gtSequence = NULL;
	if( actor->GetGtSequence( sequenceMessage->mpSequenceInfo->GetSequenceID(), gtSequence )
		== false )
		return;

	GcSequenceTimeDlg* timeDlg = new GcSequenceTimeDlg();
	timeDlg->Create( GcSequenceTimeDlg::IDD, &mTabCtrl );
	timeDlg->ResetData( gtSequence );
	timeDlg->SetCurrentAniTime( mCurrentAniTime );
	timeDlg->SetWindowText( msSequenceTimeDlgName );
	AddTab( timeDlg, msSequenceTimeDlgName );

	GcSequenceCollisionDlg* collisionDlg = new GcSequenceCollisionDlg();
	collisionDlg->Create( GcSequenceCollisionDlg::IDD, &mTabCtrl );
	collisionDlg->ResetData( actor, gtSequence );
	collisionDlg->SetWindowText( msSequenceCollisionDlgName );
	AddTab( collisionDlg, msSequenceCollisionDlgName );

	if( activeTab != -1 )
		mTabCtrl.SetActiveTab( activeTab );

	::SetFocus( focus->GetSafeHwnd() );
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
