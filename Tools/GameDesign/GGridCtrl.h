#pragma once
#include "resource.h"

class GGridCtrl : public CGridCtrl
{
	DECLARE_MESSAGE_MAP()

public:
	static CGridCtrl* CreateCtrl()
	{
		return new GGridCtrl;
	}
public:
	virtual BOOL Create(const RECT& rect, CWnd* parent, UINT nID,
		DWORD dwStyle = WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE);
	virtual void InsertRow()
	{
		CGridCtrl::InsertRow( GnText("") );
	};
	virtual void Save(GnStream* pStream){};
	virtual void Load(GnStream* pStream){};
public:
	GGridCtrl(void);
	virtual ~GGridCtrl(void);
};

class GStageLevel;
class GStageLevelGridCtrl : public GGridCtrl
{
public:
	virtual void SaveParse(GStageLevel* pStage){};
	virtual void LoadParse(GStageLevel* pStage){};
};
