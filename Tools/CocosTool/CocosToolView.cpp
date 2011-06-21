// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// http://msdn.microsoft.com/officeui를 참조하십시오.
//
// Copyright (C) Microsoft Corporation
// 모든 권리 보유.

// CocosToolView.cpp : CCocosToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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
END_MESSAGE_MAP()

// CCocosToolView 생성/소멸

CCocosToolView::CCocosToolView() :CFormView( CCocosToolView::IDD ), mpApp( NULL )
	, mpSpinCurrentTime(NULL), mpCollisionModify(NULL)
{
	// TODO: 여기에 생성 코드를 추가합니다.

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


// CCocosToolView 메시지 처리기


void CCocosToolView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	if( mpApp == NULL )
	{
		AttachNeedMessage( GTMG_SELECTOBJECT );
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
		CCDirector::sharedDirector()->SetUseTools( true );
		CCFileUtils::setIsPopupNotify(false );

		Loadbackground( GtToolSettings::GetBackgroundFilePath() );
	}	
	mModifyCollsionBoxsCheck = false;
}

void CCocosToolView::PostNcDestroy()
{
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
		mpsActor = NULL;
		mpsSequence = NULL;
		break;
	case GTMG_SELECTOBJECT:
		{
			mpsActor = (Gt2DActor*)((GcObjectMessage*)pMessage)->mpObject;
			AddCurrentActorToLayerDrawPprimitives();
		}
		break;
	case GTMG_SELECTSEQUENCE:
		{
			mpsSequence = NULL;
			GcSequenceMessage* sequenceMessage = (GcSequenceMessage*)pMessage;
			if( mpsActor && sequenceMessage->mpSequenceInfo )
			{
				Gt2DSequence* sequence;
				mpsActor->GetGtSequence( sequenceMessage->mpSequenceInfo->GetSequenceID(), sequence );
				if( sequence == NULL || sequence->GetSequence() == NULL )
					return;
				mpsSequence = sequence;
				sequence->GetSequence()->SetLoop( TRUE );

				ChageSequenceAniTime(sequence);
			}
			mBforeTime = 0.0f;
			mfCurrentTime = 0.0f;
			mCategoryAnimation.GetAniTimeSpin()->SetEditText( _T("0.000") );	
		}
		break;
		case GTMG_CHAGESEQUENCEANITIME:
			{
				if( mpsSequence )
					ChageSequenceAniTime( mpsSequence );
			}
	case GTMG_REDRAW:
		Invalidate( FALSE );
		break;
	}
}

void CCocosToolView::OnDraw(CDC* /*pDC*/)
{
	CCocosToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if( mpsActor )
		mpsActor->GetActor()->Update( GetCurrentTime() - mBforeTime );

	CCDirector::sharedDirector()->SetDeltaTime( GetCurrentTime() - mBforeTime );
	CCDirector::sharedDirector()->mainLoop();
	mBforeTime = GetCurrentTime();
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
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

	if( mpsActor == NULL || mpsSequence == NULL )
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
	if( mpsActor == NULL || mpsSequence == NULL )
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


void CCocosToolView::AddCurrentActorToLayerDrawPprimitives()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.	
	if( mModifyCollsionBoxsCheck )
	{
		if( mpsActor && mpsSequence )
		{
			std:string strName = GtToolSettings::GetWorkPath();
			strName += mpsActor->GetObjectName();
			strName += "/";
			strName += mpsActor->GetGATFileName();
			mpCollisionModify->LoadBasicActor( strName.c_str() );
			mpCollisionModify->SetBasicSequenceID( 1 );
			mpCollisionModify->SetVisible( true, mpsActor->GetActor()->GetRootNode() );
		}		
	}
	else
	{
		mpCollisionModify->SetVisible( false );
	}
	Invalidate( FALSE );	
	//if( mModifyCollsionBoxsCheck )
	//{
	//	if( mpsActor )
	//	{
	//		GnLayerDrawPrimitives* node = 
	//			(GnLayerDrawPrimitives*)GetSceneManager()->GetMainGameLayer()->getChildByTag( 1 );

	//		if( mpsDrawSequenceRect )
	//			node->RemoveChild( mpsDrawSequenceRect );

	//		GnDraw2DObjectRect* drawObject = GtObjectNew<GnDraw2DObjectRect>::Create();
	//		drawObject->SetThickness( 3.0f );
	//		drawObject->SetColor( GnColorA(1.0f, 1.0f, 0.0f, 1.0f) );
	//		drawObject->SetObject( mpsActor->GetRootNode() );
	//		node->AddChild( drawObject );
	//		mpsDrawSequenceRect = drawObject;
	//	}
	//}
	//else if( mpsDrawSequenceRect )
	//{
	//	GnLayerDrawPrimitives* node = 
	//		(GnLayerDrawPrimitives*)GetSceneManager()->GetMainGameLayer()->getChildByTag( 1 );
	//	node->RemoveChild( mpsDrawSequenceRect );
	//}	

	//Invalidate( FALSE );
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
			if( spin->GetPos() == 0 )
			{
				mpCollisionModify->SetScale( 0.36f );
				GetGameState()->SetGameScale( 0.36f );
			}
			else
			{
				mpCollisionModify->SetScale( (float)spin->GetPos() );
				GetGameState()->SetGameScale( (float)spin->GetPos() );
			}
		}
		if( mpsActor )
		{
			mpsActor->GetActor()->GetRootNode()->SetScale( 1.0f );
		}
		Invalidate( false );
	}
}


void CCocosToolView::OnFlipx()
{
	if( mpsActor )
	{
		Gn2DMeshObject* mesh = mpsActor->GetRootNode();
		if( mesh )
		{
			static int i= 1;
			mesh->SetFlipX( !mesh->GetMesh()->isFlipX() );
			//if( mesh->GetMesh()->isFlipX() )
			//{
			//	mesh->SetPosition( mesh->GetPosition() - mesh->GetAVData()->GetAnchorPoint() );
			//}
			//else
			//	mesh->SetPosition( mesh->GetPosition() + mesh->GetAVData()->GetAnchorPoint() );
			Invalidate( false );
		}
	}
}