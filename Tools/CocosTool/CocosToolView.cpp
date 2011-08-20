#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "CocosTool.h"
#endif

#include "CocosToolDoc.h"
#include "CocosToolView.h"

#include <CCStdC.h>
#include <CCApplication.h>

#include "MainFrm.h"
#include "GtGLView.h"
#include "GnLayerMain.h"
#include "ActorMacro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GnVector2 ActorBasePosition( 0, 0 );
const float CCocosToolView::msWidth = 480.0f;
const float CCocosToolView::msHeight = 320.0f;

// CCocosToolView

IMPLEMENT_DYNCREATE(CCocosToolView, CFormView)

BEGIN_MESSAGE_MAP(CCocosToolView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDC_RBBT_PLAY, &CCocosToolView::OnAniPlay)
	ON_COMMAND(IDC_RBBT_PAUSE, &CCocosToolView::OnAniPause)
	ON_WM_TIMER()
	ON_COMMAND(IDC_MODIFY_COLLISIONBOXS, &CCocosToolView::OnModifyCollisionboxs)
	ON_UPDATE_COMMAND_UI(IDC_MODIFY_COLLISIONBOXS, &CCocosToolView::OnUpdateModifyCollisionboxs)
	ON_COMMAND(IDC_ANICURRENTTIME, &CCocosToolView::OnAnicurrenttime)
	ON_COMMAND(IDC_ANITIMESLIDER, &CCocosToolView::OnAnitimeslider)
	ON_COMMAND(ID_BT_LOADBACKGROUND, &CCocosToolView::OnBtLoadbackground)
	ON_COMMAND(ID_SCALERANGE, &CCocosToolView::OnScaleRange)
	ON_COMMAND(ID_BT_FLIPX, &CCocosToolView::OnFlipx)
	ON_COMMAND(ID_ACTOR_CENTER, &CCocosToolView::OnActorCenter)
	ON_UPDATE_COMMAND_UI(ID_ACTOR_CENTER, &CCocosToolView::OnUpdateActorCenter)
END_MESSAGE_MAP()

// CCocosToolView 생성/소멸

CCocosToolView::CCocosToolView() :CFormView( CCocosToolView::IDD ), mpApp( NULL )
	, mpSpinCurrentTime(NULL), mpCollisionModify(NULL)
{
	mfCurrentTime = 0.0f;
	mBforeTime = 0.0f;
	mfStartTime = 0.0f;
	mfEndTime = 0.0f;
	mfTick = 0.0f;
	mfLastTick = 0.0f;

}

CCocosToolView::~CCocosToolView()
{
}

void CCocosToolView::DoDataExchange(CDataExchange* pDX)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOCATION_RENDER, mLoactionRender);
}

BOOL CCocosToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CCocosToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);	
	OnContextMenu(this, point);
}

void CCocosToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCocosToolView 진단

#ifdef _DEBUG
void CCocosToolView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCocosToolView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCocosToolDoc* CCocosToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCocosToolDoc)));
	return (CCocosToolDoc*)m_pDocument;
}
#endif //_DEBUG

void CCocosToolView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	if( mpApp == NULL )
	{
		AttachNeedMessage( GTMG_SELECTOBJECT );
		AttachNeedMessage( GTMG_SELECT2DOBJECT );
		AttachNeedMessage( GTMG_SELECTSEQUENCE );
		AttachNeedMessage( GTMG_REDRAW );
		AttachNeedMessage( GTMG_DESTORY );
		AttachNeedMessage( GTMG_CHAGESEQUENCEANITIME );

		mpApp = new GtCocos2DApp;
		// Initialize instance and cocos2d.
		GtGLView * pMainWnd = new GtGLView();
		pMainWnd->Create(mLoactionRender.GetSafeHwnd(), (int)msWidth, (int)msHeight);

		// initialize director
		CCDirector *pDirector = CCDirector::sharedDirector();
		pDirector->setOpenGLView(pMainWnd);
		if (! mpApp->initInstance() || ! mpApp->applicationDidFinishLaunching())
		{
			return;
		}
		GnSceneManager* man = GetSceneManager();
		GetSceneManager()->GetMainGameLayer()->setColor( ccc3(0,0,255) );
		GetSceneManager()->GetMainGameLayer()->setOpacity( 255 );
		GetSceneManager()->GetMainGameLayer()->setContentSize( CCSizeMake(msWidth, msHeight) );

		mpCollisionModify = GtCollisionModify::Create( msWidth, msHeight );		

		CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();
		mCategoryAnimation.Create( mainFrame->GetRibbonBar() );
		CCFileUtils::setIsPopupNotify(false );

		Loadbackground( GtToolSettings::GetBackgroundFilePath() );

		GetDrawObjectManager()->Reset();
	}	
	mModifyCollsionBoxsCheck = false;
	mActorCenterCheck = false;
}

void CCocosToolView::PostNcDestroy()
{
	if( mpCollisionModify )
		delete mpCollisionModify;
	delete mpApp;
	CFormView::PostNcDestroy();
}

void CCocosToolView::ReceiveMediateMessage(gtuint messageIndex
	, GcMediateObjectMessage* pMessage)
{
	switch( messageIndex )
	{
	case GTMG_DESTORY:
		
		GetDrawObjectManager()->Reset();
		if( pMessage && *((bool*)(pMessage->mTempMessage)) )
			break;
		GetSceneManager()->GetMainGameLayer()->removeAllChildrenWithCleanup( true );
		if( mpCollisionModify )
			delete mpCollisionModify;
		mpCollisionModify = GtCollisionModify::Create( msWidth, msHeight );		
		Loadbackground( GtToolSettings::GetBackgroundFilePath() );		
		break;
	case GTMG_SELECTOBJECT:
		{
			GetDrawObjectManager()->SelectActor( pMessage->mpObject );
			AddCurrentActorToLayerDrawPprimitives();
		}
		break;
	case GTMG_SELECT2DOBJECT:
		{
			GetDrawObjectManager()->Select2DObject( pMessage->mpObject );
		}
		break;
	case GTMG_SELECTSEQUENCE:
		{
			GcSequenceMessage* sequenceMessage = (GcSequenceMessage*)pMessage;
			if( GetDrawObjectManager()->SelectSequence( sequenceMessage->mpSequenceInfo ) == false )
				break;
			
			ChageSequenceAniTime( GetDrawObjectManager()->GetSequence() );
			mBforeTime = 0.0f;
			mfCurrentTime = 0.0f;
			mCategoryAnimation.GetAniTimeSpin()->SetEditText( _T("0.000") );	
		}
		break;
	case GTMG_CHAGESEQUENCEANITIME:
		{
			if( GetDrawObjectManager()->GetSequence() )
				ChageSequenceAniTime( GetDrawObjectManager()->GetSequence() );
		}
		break;
	case GTMG_REDRAW:
		{
			Invalidate( FALSE );
		}		
		break;
	}
}

void CCocosToolView::OnDraw(CDC* /*pDC*/)
{
	CCocosToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	float deltaTime = GetCurrentTime() - mBforeTime;

	GetDrawObjectManager()->Update( deltaTime );

	CCDirector::sharedDirector()->setDeltaTime( deltaTime );
	CCDirector::sharedDirector()->mainLoop();
	mBforeTime = GetCurrentTime();
}
void CCocosToolView::OnAniPlay()
{
	mfTick = GnGetTicks();
	SetTimer(mTimerID, 0, NULL);
}

void CCocosToolView::OnAniPause()
{
	KillTimer(mTimerID);	
}

void CCocosToolView::OnTimer(UINT_PTR nIDEvent)
{
	CFormView::OnTimer(nIDEvent);
	if( GetCurrentTime() >= mfEndTime  )
	{
		mBforeTime = 0.0f;
		mfTick = GnGetTicks();
	}
	mfLastTick = GnGetTicks();

	SetCurrentTimeFromOnTimer();

	Invalidate(FALSE);

}

void CCocosToolView::OnAnicurrenttime()
{
	CString intTime = mCategoryAnimation.GetAniTimeSpin()->GetEditText();
	if( mStrCurrentTime == intTime )
		return;

	if( GetDrawObjectManager()->GetActor() == NULL 
		|| GetDrawObjectManager()->GetSequence() == NULL )
		return;

	float num = 0.0f;
	_stscanf_s( intTime.GetString(), _T("%f"), &num );
	num /= 100;
	if( mfEndTime > num )
	{
		SetCurrentTime( num );
	}	

	CString floatTime;
	floatTime.Format( _T("%.3f"), GetCurrentTime() );
	mCategoryAnimation.GetAniTimeSpin()->SetEditText( floatTime );
	mStrCurrentTime = floatTime;
	Invalidate(FALSE);
}

void CCocosToolView::OnAnitimeslider()
{
	if( GetDrawObjectManager()->GetActor() == NULL
		|| GetDrawObjectManager()->GetSequence()== NULL )
		return;

	if( GetCurrentTime() >= mfEndTime  )
		return;

	Invalidate(FALSE);
}

void CCocosToolView::SetCurrentTime(float val)
{
	mfCurrentTime = val;

	GcMediateObjectMessage msg;
	msg.mTempMessage = &mfCurrentTime;
	SendMediateMessage( GTMG_TIMECHANGE, &msg );
}

void CCocosToolView::SetCurrentTimeFromOnTimer()
{
	SetCurrentTime( mfLastTick - mfTick );
	if( mpSpinCurrentTime )
	{
		mpSpinCurrentTime->SetPos( (int)(GetCurrentTime()*100) );
	}
	CString floatTime;
	floatTime.Format( _T("%.3f"), GetCurrentTime() );
	mCategoryAnimation.GetAniTimeSpin()->SetEditText( floatTime );
	mStrCurrentTime = floatTime;
}

void CCocosToolView::ChageSequenceAniTime(Gt2DSequence* sequence)
{
	mfStartTime = sequence->GetSequence()->GetStartTime();
	mfEndTime = sequence->GetSequence()->GetEndTime();

	CString time;
	time.Format( _T("%.3f"), mfStartTime );
	mCategoryAnimation.GetAniStartTime()->SetEditText( time );
	time.Format( _T("%.3f"), mfEndTime );
	mCategoryAnimation.GetAniEndTime()->SetEditText( time );
	Invalidate( FALSE );
	mCategoryAnimation.GetAniTimeSpin()->EnableSpinButtons( (int)mfStartTime
		, (int)(mfEndTime * 100) );


	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();
	CWnd* ps =  mainFrame->GetRibbonBar()->GetDlgItem(IDC_ANICURRENTTIME);
	mpSpinCurrentTime = (CMFCSpinButtonCtrl*)mainFrame->GetRibbonBar()->GetNextDlgGroupItem( ps );
	if( mpSpinCurrentTime )
		mpSpinCurrentTime->SetPos( 0 );
}

void CCocosToolView::OnUpdateModifyCollisionboxs(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( mModifyCollsionBoxsCheck );
}

void CCocosToolView::OnModifyCollisionboxs()
{
	mModifyCollsionBoxsCheck = !mModifyCollsionBoxsCheck;
	AddCurrentActorToLayerDrawPprimitives();
}

void CCocosToolView::OnActorCenter()
{
	mActorCenterCheck = !mActorCenterCheck;

	GetDrawObjectManager()->SetObjectCenter( mActorCenterCheck );

	if( mpCollisionModify  )
		mpCollisionModify->SetActorPosition( ActorBasePosition );

	Invalidate( FALSE );	
}

void CCocosToolView::OnUpdateActorCenter(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( mActorCenterCheck );
}

void CCocosToolView::AddCurrentActorToLayerDrawPprimitives()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.	
	if( mModifyCollsionBoxsCheck )
	{
		if( GetDrawObjectManager()->GetActor() && GetDrawObjectManager()->GetSequence() )
		{
			std::string strName = GtToolSettings::GetWorkPath();
			strName += gsActorPath;
			strName += GetDrawObjectManager()->GetActor()->GetObjectName();
			strName += "/";
			strName += GetDrawObjectManager()->GetActor()->GetGATFileName();
			mpCollisionModify->LoadBasicActor( strName.c_str() );
			mpCollisionModify->SetBasicSequenceID( 1 );
			mpCollisionModify->SetVisible( true, GetDrawObjectManager()->GetActor()->GetRootNode() );
		}		
	}
	else
	{
		mpCollisionModify->SetVisible( false );
	}
	Invalidate( FALSE );
}

void CCocosToolView::OnBtLoadbackground()
{
	CFileDialog dlg(true, _T("IMG"), NULL
		, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR
		, gsTextureFileFilter, this );

	if( IDOK == dlg.DoModal() )
	{
		GtConvertString filePath = dlg.GetPathName().GetString();
		Loadbackground( filePath.GetAciiString() );
		GtToolSettings::SetBackgroundFilePath( filePath.GetAciiString() );
		Invalidate(FALSE);
	}
}

void CCocosToolView::Loadbackground(const gchar* pcFilePath)
{
	if( GnStrlen(pcFilePath) )
	{
		GnLayerMain* main = (GnLayerMain*)GetSceneManager()->GetMainGameLayer();
		GnVerify( main->CreateBackgroundFromFile( pcFilePath ) );	
	}
}

LRESULT CCocosToolView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{  
	switch (message) 
	{ 
	case WM_CHAR:
		{
			GnLayerMain* main = (GnLayerMain*)GetSceneManager()->GetMainGameLayer();
			if( main->GetBackground() )
			{
				switch( wParam )
				{
				case 'd':
					{
						CCPoint point = main->GetBackground()->getPosition();
						point.x -= 20;
						main->GetBackground()->setPosition( point );
						Invalidate( FALSE );
					}
					break;
				case 'a':
					{
						CCPoint point = main->GetBackground()->getPosition();
						point.x += 20;
						main->GetBackground()->setPosition( point );
						Invalidate( FALSE );
					}					
					break;
				}
			}
		}
		break;
	}

	return CFormView::WindowProc(message, wParam, lParam);
}

void CCocosToolView::OnScaleRange()
{
	
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();
	CWnd* ps =  mainFrame->GetRibbonBar()->GetDlgItem( ID_SCALERANGE );
	if( ps )
	{
		CMFCSpinButtonCtrl* spin = 
			(CMFCSpinButtonCtrl*)mainFrame->GetRibbonBar()->GetNextDlgGroupItem( ps );
		if( spin )
		{
			if( GtToolSettings::GetScalePercent() == 100 )
			{
				int btRet = MessageBox( 
					_T("스케일을 조정 하면 데이터를 저장 할 수 없습니다. 미리 저장 하시겠습니까?") 
					,_T("Warring"), MB_YESNOCANCEL );
				if( btRet == IDOK )
					GetObjectFactory()->SaveObjects(true);
				else if( btRet == IDCANCEL )
				{
					spin->SetPos( GtToolSettings::GetScalePercent() );
					return;
				}
			}
			GetObjectFactory()->RemvoeAllObject();
			SendMediateMessage( GTMG_DESTORY, NULL );
			GtToolSettings::SetScalsePercent( spin->GetPos() );
			GetGameState()->SetGameScale( GtToolSettings::GetScale() );
		}
		//if( GetDrawObjectManager()->GetActor() )
		//	GetDrawObjectManager()->GetActor()->GetRootNode()->SetScale( 1.0f );
		Invalidate( false );
	}
}

void CCocosToolView::OnFlipx()
{
	if( GetDrawObjectManager()->GetActor() )
	{
		Gn2DMeshObject* mesh = GetDrawObjectManager()->GetActor()->GetRootNode();
		if( mesh )
		{
			mesh->SetFlipX( !mesh->GetMesh()->isFlipX() );
// 			for( gtuint i = 0; i < mesh->GetExtraDataSize(); i++ )
// 			{
// 				GnVector2ExtraData* vectorData = GnDynamicCast(GnVector2ExtraData, mesh->GetExtraData( i ));
// 				if( vectorData )
// 				{
// 					if( mesh->GetAVData() )
// 					{
// 						if( mesh->GetFlipX() )
// 						{
// 							Gn2DAVData::CollisionRect& baseRect = mesh->GetAVData()->GetCollisionRect( 0 );
// 							float center = baseRect.mRect.GetWidth();							
// 							vectorData->SetValueX( center - vectorData->GetValueVector2().x );
// 						}
// 						else
// 						{
// 							Gn2DAVData::CollisionRect& baseRect = mesh->GetAVData()->GetCollisionRect( 0 );
// 							float center = baseRect.mRect.GetWidth();// - vectorData->GetValueVector2().x;
// 							vectorData->SetValueX( center -  vectorData->GetValueVector2().x);
// 						}
// 					}
// 				}
// 			}			
			Invalidate( false );
		}
	}
}