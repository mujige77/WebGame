#pragma once
#include "GGridCtrl.h"

class GMobAppearGrid : public GStageLevelGridCtrl
{
public:
	static CGridCtrl* CreateCtrl()
	{
		return new GMobAppearGrid;
	}
public:
	virtual BOOL Create(const RECT& rect, CWnd* parent, UINT nID,
		DWORD dwStyle = WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE);
	void SaveParse(GStageLevel* pStage);
	void LoadParse(GStageLevel* pStage);
	void InsertRow();
public:
	GMobAppearGrid(void);
	virtual ~GMobAppearGrid(void);
};

