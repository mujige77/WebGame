#include "StdAfx.h"
#include "GMobAppearGrid.h"
#include "GStageLevel.h"

GMobAppearGrid::GMobAppearGrid(void)
{
}


GMobAppearGrid::~GMobAppearGrid(void)
{
}

BOOL GMobAppearGrid::Create(const RECT& rect, CWnd* parent, UINT nID, DWORD dwStyle )
{
	if( !GGridCtrl::Create( rect, parent, nID, dwStyle ) )	
		return FALSE;

	SetFixedColumnCount( 0 );
	//SetColumnWidth( 0, 60 );

	SetColumnCount( 3 );
	SetRowCount( 1 );
	SetItemText( 0, 0, GnText("¸÷ ÀÎµ¦½º") );
	SetItemText( 0, 1,  GnText("·¹º§") );
	SetItemText( 0, 2,GnText("ÃâÇö °£°Ý(%)") );
	
	return TRUE;
}

void GMobAppearGrid::SaveParse(GStageLevel* pStage)
{
	CGridCellBase* cell =  NULL;
	GtLongNumberString num;
	for( gint i = 1 ; i < GetRowCount() ; i++ )
	{
		GStageLevel::AppearMob mob;

		cell = GetCell( i, 0 );
		num.SetNumber( (gtchar*)cell->GetText() );
		mob.mIndex = (guint32)num.GetNumber( 0 );
		
		cell = GetCell( i, 1 );
		num.SetNumber( (gtchar*)cell->GetText() );
		mob.mLevel = (guint32)num.GetNumber( 0 );
		
		cell = GetCell( i, 2 );
		num.SetNumber( (gtchar*)cell->GetText() );
		mob.mIntervalAppearPercent = num.GetNumber( 0 );

		pStage->AddAppearMob( mob );
	}
}

void GMobAppearGrid::LoadParse(GStageLevel* pStage)
{
	CGridCellBase* cell =  NULL;
	GtLongNumberString num;
	for( gtuint i = 0 ; i < pStage->GetAppearMobCount() ; i++ )
	{
		InsertRow();
		GStageLevel::AppearMob& mob = pStage->GetAppearMob( i );

		num.SetNumber( (glong)mob.mIndex );
		SetItemText( i + 1, 0, num.c_str() );
		
		num.SetNumber( (glong)mob.mLevel );
		SetItemText( i + 1, 1, num.c_str() );

		num.SetNumber( mob.mIntervalAppearPercent );
		SetItemText( i + 1, 2, num.c_str() );
	}
}

void GMobAppearGrid::InsertRow()
{
	gint rowCount = GetRowCount();
	GStageLevelGridCtrl::InsertRow();

	SetCellType( rowCount, 0, RUNTIME_CLASS(CGridCellNumeric) );
	SetCellType( rowCount, 1, RUNTIME_CLASS(CGridCellNumeric) );
	SetCellType( rowCount, 2, RUNTIME_CLASS(CGridCellNumeric) );
}