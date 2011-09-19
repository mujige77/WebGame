// GStageLevelDesignView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GameDesign.h"
#include "GStageLevelDesignView.h"
#include "GStageLevelDesignDefine.h"

IMPLEMENT_DYNCREATE(GStageLevelDesignView, GDesignFormView)

BEGIN_MESSAGE_MAP(GStageLevelDesignView, GDesignFormView)
	ON_BN_CLICKED(IDC_BT_ADDMOB, &GStageLevelDesignView::OnClickedAddMob)
	ON_BN_CLICKED(IDC_BT_DELETEMOB, &GStageLevelDesignView::OnClickedDeleteMob)
	ON_BN_CLICKED(IDC_BT_ADDMASSMOB, &GStageLevelDesignView::OnBnClickedAddMassMob)
	ON_BN_CLICKED(IDC_BT_DELETEMASSMOB, &GStageLevelDesignView::OnBnClickedBtDeleteMassMob)
END_MESSAGE_MAP()

GStageLevelDesignView::GStageLevelDesignView() : GDesignFormView(GStageLevelDesignView::IDD)	
	, mStageNumber(0), mBossMobIndex(0), mLoadedStageLevel( false ), mpGcMopAppear( NULL )
	, mpGcMobAttackLine( NULL )
	, mCastleHP(0)
{

}

GStageLevelDesignView::~GStageLevelDesignView()
{
	if( mpGcMopAppear )
		delete mpGcMopAppear;
	if( mpGcMobAttackLine )
		delete mpGcMobAttackLine;
	if( mpGcMassMopAppear )
		delete mpGcMassMopAppear;
}

void GStageLevelDesignView::DoDataExchange(CDataExchange* pDX)
{
	GDesignFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GP_MOBATTACKLINE, mGpMobAttackLine);
	DDX_Control(pDX, IDC_GP_MOBAPPEAR, mGpMopAppear);
	DDX_Control(pDX, IDC_ET_STAGENUMBER, mEtStageNumber);
	DDX_Control(pDX, IDC_ET_BOSSMOBINDEX, mEtBossMobIndex);
	DDX_Text(pDX, IDC_ET_STAGENUMBER, mStageNumber);
	DDX_Text(pDX, IDC_ET_BOSSMOBINDEX, mBossMobIndex);
	DDX_Control(pDX, IDC_ET_CASTLEHP, mEtCastleHP);
	DDX_Control(pDX, IDC_GP_MASSMOBAPPEAR, mGpMassMobAppear);
}

void GStageLevelDesignView::Save(GnStream* pStream)
{
	GStageLevel stageLevel;

	SaveStageLevel( &stageLevel );

	stageLevel.SaveStream( pStream );
}

void GStageLevelDesignView::Load(GnStream* pStream)
{
	mLoadedStageLevel = true;
	mLoadStageLevelValue.LoadStream( pStream );
}

BOOL GStageLevelDesignView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if( pMsg->message == WM_KEYDOWN && ( pMsg->wParam == 'C' || pMsg->wParam == 'X' || pMsg->wParam == 'V' ) )
	{
		if( IsCTRLpressed() )
			PreTranslateInput( pMsg );
	}
	return GDesignFormView::PreTranslateMessage(pMsg);
}

#ifdef _DEBUG
void GStageLevelDesignView::AssertValid() const
{
	GDesignFormView::AssertValid();
}

#ifndef _WIN32_WCE
void GStageLevelDesignView::Dump(CDumpContext& dc) const
{
	GDesignFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void GStageLevelDesignView::SaveStageLevel(GStageLevel* pStageLevel)
{
	guint32 number = 0;
	CString strNumber;
	GtLongNumberString convertNumber;

	mEtStageNumber.GetWindowText( strNumber );
	convertNumber.SetNumber( (gtchar*)strNumber.GetString() );
	number = convertNumber.GetNumber( 0 );
	pStageLevel->SetLevelIndex( number );

	mEtBossMobIndex.GetWindowText( strNumber );
	convertNumber.SetNumber( (gtchar*)strNumber.GetString() );
	number = convertNumber.GetNumber( 0 );
	pStageLevel->SetBossMobIndex( number );

	mEtCastleHP.GetWindowText( strNumber );
	convertNumber.SetNumber( (gtchar*)strNumber.GetString() );
	number = convertNumber.GetNumber( 0 );
	pStageLevel->SetCastleHP( number );

	mpGcMopAppear->SaveParse( pStageLevel );
	mpGcMobAttackLine->SaveParse( pStageLevel );
	mpGcMassMopAppear->SaveParse( pStageLevel );
}

void GStageLevelDesignView::LoadStageLevel(GStageLevel* pStageLevel)
{
	GtLongNumberString convertNumber;
	convertNumber.SetNumber( pStageLevel->GetLevelIndex() );	
	mEtStageNumber.SetWindowText( convertNumber.c_str() );	

	convertNumber.SetNumber( pStageLevel->GetBossMobIndex() );	
	mEtBossMobIndex.SetWindowText( convertNumber.c_str() );

	convertNumber.SetNumber( pStageLevel->GetCastleHP() );	
	mEtCastleHP.SetWindowText( convertNumber.c_str() );

	mpGcMopAppear->LoadParse( pStageLevel );
	mpGcMobAttackLine->LoadParse( pStageLevel );
	mpGcMassMopAppear->LoadParse( pStageLevel );
}

void GStageLevelDesignView::OnInitialUpdate()
{
	GDesignFormView::OnInitialUpdate();
	CRect rect;//(10,10,10,10);

	mpGcMobAttackLine = (GStageLevelGridCtrl*)CGridCtrl::FunctionRegGet( gcMobAttackLineGridCtrlName )();
	mpGcMobAttackLine->Create( rect, &mGpMobAttackLine, ID_GMobAttackLineGrid );

	mpGcMopAppear = (GStageLevelGridCtrl*)CGridCtrl::FunctionRegGet( gcMobAppearGridCtrlName )();
	mpGcMopAppear->Create( rect, &mGpMopAppear, ID_GMobAppearGrid );

	mpGcMassMopAppear = (GStageLevelGridCtrl*)CGridCtrl::FunctionRegGet( gcMassMobAppearGridCtrlName )();
	mpGcMassMopAppear->Create( rect, &mGpMassMobAppear, ID_GMassMobAppearGrid );

	
	if( mLoadedStageLevel )
		LoadStageLevel( &mLoadStageLevelValue );
}

void GStageLevelDesignView::OnClickedAddMob()
{
	mpGcMopAppear->InsertRow();
	mpGcMopAppear->Invalidate();	
}


void GStageLevelDesignView::OnClickedDeleteMob()
{
	int nRow = mpGcMopAppear->GetFocusCell().row;
	if( nRow != -1 )
	{
		mpGcMopAppear->DeleteRow( nRow );
		mpGcMopAppear->Invalidate();
	}
}

void GStageLevelDesignView::OnBnClickedAddMassMob()
{
	mpGcMassMopAppear->InsertRow();
	mpGcMassMopAppear->Invalidate();
}


void GStageLevelDesignView::OnBnClickedBtDeleteMassMob()
{
	int nRow = mpGcMassMopAppear->GetFocusCell().row;
	if( nRow != -1 )
	{
		mpGcMassMopAppear->DeleteRow( nRow );
		mpGcMassMopAppear->Invalidate();
	}
}
