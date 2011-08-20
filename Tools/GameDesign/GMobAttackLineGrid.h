#pragma once
#include "GGridCtrl.h"

class GMobAttackLineGrid : public GStageLevelGridCtrl
{
	enum
	{
		COL_NUMLINE,
		COL_STARTAPPEARTIME,
		COL_INTERVALAPPEARTIME,
	};
public:
	static CGridCtrl* CreateCtrl()
	{
		return new GMobAttackLineGrid;
	}
public:
	virtual BOOL Create(const RECT& rect, CWnd* parent, UINT nID,
		DWORD dwStyle = WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE);
	void InsertRow();
	void SaveParse(GStageLevel* pStage);
	void LoadParse(GStageLevel* pStage);
public:
	GMobAttackLineGrid(void);
	virtual ~GMobAttackLineGrid(void);
};

