#include "StdAfx.h"
#include "GMobAttackLineGrid.h"
#include "GStageLevel.h"

GMobAttackLineGrid::GMobAttackLineGrid(void)
{
}


GMobAttackLineGrid::~GMobAttackLineGrid(void)
{
}

BOOL GMobAttackLineGrid::Create(const RECT& rect, CWnd* parent, UINT nID, DWORD dwStyle )
{
	if( !GGridCtrl::Create( rect, parent, nID, dwStyle ) )	
		return FALSE;
	SetFixedColumnCount( 0 );
	SetColumnWidth( 0, 50 );
	
	SetColumnCount( 3 );
	SetRowCount( 1 );
	SetItemText( 0, 0, GnText("줄 번호") );
	SetItemText( 0, 1, GnText("출현 시작(sec)") );
	SetItemText( 0, 2, GnText("출현 간격(sec)") );

	InsertRow();
	InsertRow();
	return TRUE;
}

void GMobAttackLineGrid::InsertRow()
{
	gint rowCount = GetRowCount();
	gtchar number[16] = {0,};
	GnTSprintf( number, sizeof( number ), GnText("%d"), rowCount - 1 );
	CGridCtrl::InsertRow( number );

	SetCellType( rowCount, 0, RUNTIME_CLASS(CGridCellNumeric) );
	SetCellType( rowCount, 1, RUNTIME_CLASS(CGridCellNumeric) );
	SetCellType( rowCount, 2, RUNTIME_CLASS(CGridCellNumeric) );
	SetItemText( rowCount, 0, number );
}

void GMobAttackLineGrid::SaveParse(GStageLevel* pStage)
{
	CGridCellBase* cell =  NULL;
	GtLongNumberString num;
	for( gint i = 1 ; i < GetRowCount() ; i++ )
	{
		GStageLevel::AttackLine line;

		cell = GetCell( i, COL_NUMLINE );
		num.SetNumber( (gtchar*)cell->GetText() );
		line.mNumLine = (guint32)num.GetNumber( 0 );

		cell = GetCell( i, COL_STARTAPPEARTIME );
		num.SetNumber( (gtchar*)cell->GetText() );
		line.mStartAppearTime = (float)num.GetNumber( 0 );

		cell = GetCell( i, COL_INTERVALAPPEARTIME );
		num.SetNumber( (gtchar*)cell->GetText() );
		line.mIntervalAppearTime = (float)num.GetNumber( 0 );

		pStage->AddAttackLine( line );
	}
}

void GMobAttackLineGrid::LoadParse(GStageLevel* pStage)
{
	CGridCellBase* cell =  NULL;
	GtLongNumberString num;
	for( gtuint i = 0 ; i < pStage->GetAttackLineCount() ; i++ )
	{
		//InsertRow();
		GStageLevel::AttackLine& line = pStage->GetAttackLine( i );

		num.SetNumber( (glong)line.mNumLine );
		SetItemText( i + 1, COL_NUMLINE, num.c_str() );

		num.SetNumber( (glong)line.mStartAppearTime );
		SetItemText( i + 1, COL_STARTAPPEARTIME, num.c_str() );

		num.SetNumber( (glong)line.mIntervalAppearTime );
		SetItemText( i + 1, COL_INTERVALAPPEARTIME, num.c_str() );
	}
}