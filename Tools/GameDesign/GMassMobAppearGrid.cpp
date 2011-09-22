#include "StdAfx.h"
#include "GMassMobAppearGrid.h"
#include "GStageLevel.h"

GMassMobAppearGrid::GMassMobAppearGrid(void)
{
}


GMassMobAppearGrid::~GMassMobAppearGrid(void)
{
}

BOOL GMassMobAppearGrid::Create(const RECT& rect, CWnd* parent, UINT nID, DWORD dwStyle )
{
	if( !GGridCtrl::Create( rect, parent, nID, dwStyle ) )	
		return FALSE;

	SetFixedColumnCount( 0 );
	SetColumnCount( 4 );
	SetColumnWidth( 1, 40 );
	SetColumnWidth( 2, 70 );

	
	SetRowCount( 1 );
	SetItemText( 0, 0, GnText("몹 인덱스") );
	SetItemText( 0, 1, GnText("레벨") );
	SetItemText( 0, 2, GnText("출현 라인") );
	SetItemText( 0, 3, GnText("출현 개수") );

	return TRUE;
}

void GMassMobAppearGrid::SaveParse(GStageLevel* pStage)
{
	CGridCellBase* cell =  NULL;
	GtLongNumberString num;
	for( gint i = 1 ; i < GetRowCount() ; i++ )
	{
		GStageLevel::MassAppearMob mob;

		cell = GetCell( i, 0 );
		num.SetNumber( (gtchar*)cell->GetText() );
		mob.mIndex = (guint32)num.GetNumber( 0 );

		cell = GetCell( i, 1 );
		num.SetNumber( (gtchar*)cell->GetText() );
		mob.mLevel = (guint32)num.GetNumber( 0 );

		cell = GetCell( i, 2 );
		num.SetNumber( (gtchar*)cell->GetText() );
		mob.mNumLine = (guint32)num.GetNumber( 0 );

		cell = GetCell( i, 3 );
		num.SetNumber( (gtchar*)cell->GetText() );
		mob.mNumMobCount = (guint32)num.GetNumber( 0 );

		pStage->AddMassAppearMob( mob );
	}
}

void GMassMobAppearGrid::LoadParse(GStageLevel* pStage)
{
	CGridCellBase* cell =  NULL;
	GtLongNumberString num;
	for( gtuint i = 0 ; i < pStage->GetMassAppearMobCount() ; i++ )
	{
		InsertRow();
		GStageLevel::MassAppearMob& mob = pStage->GetMassAppearMob( i );

		num.SetNumber( (glong)mob.mIndex );
		SetItemText( i + 1, 0, num.c_str() );

		num.SetNumber( (glong)mob.mLevel );
		SetItemText( i + 1, 1, num.c_str() );

		num.SetNumber( (glong)mob.mNumLine );
		SetItemText( i + 1, 2, num.c_str() );

		num.SetNumber( (glong)mob.mNumMobCount );
		SetItemText( i + 1, 3, num.c_str() );
	}
}

void GMassMobAppearGrid::InsertRow()
{
	gint rowCount = GetRowCount();
	GStageLevelGridCtrl::InsertRow();

	SetCellType( rowCount, 0, RUNTIME_CLASS(CGridCellNumeric) );
	SetCellType( rowCount, 1, RUNTIME_CLASS(CGridCellNumeric) );
	SetCellType( rowCount, 2, RUNTIME_CLASS(CGridCellNumeric) );
	SetCellType( rowCount, 2, RUNTIME_CLASS(CGridCellNumeric) );
}