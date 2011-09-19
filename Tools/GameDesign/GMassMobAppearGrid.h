#pragma once
#include "GGridCtrl.h"

class GMassMobAppearGrid : public GStageLevelGridCtrl
{
public:
	static CGridCtrl* CreateCtrl()
	{
		return new GMassMobAppearGrid;
	}
public:
	virtual BOOL Create(const RECT& rect, CWnd* parent, UINT nID,
		DWORD dwStyle = WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE);
	void SaveParse(GStageLevel* pStage);
	void LoadParse(GStageLevel* pStage);
	void InsertRow();
public:
	GMassMobAppearGrid(void);
	virtual ~GMassMobAppearGrid(void);
};

