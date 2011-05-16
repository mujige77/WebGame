#pragma once
#include "GtMediateObject.h"


class GtToolBarForm : public CDockablePane, public GtMediateObject
{
	DECLARE_DYNAMIC(GtToolBarForm)
public:
	class ToolBar : public CMFCToolBar
	{
	public:
		virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
		{
			CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
		}

		virtual BOOL AllowShowOnList() const { return FALSE; }
	};

protected:
	ToolBar mToolBar;
	int mChildBeginTop;
	CWnd* mpMainWnd;

	// Construction
public:      // must derive your own class
	GtToolBarForm();
	virtual ~GtToolBarForm();
	void SetVisibleCaptionBar(bool bShow);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void ReciveNotiyfiMessage(WPARAM wParam, LPARAM lParam){};
	virtual void ReceiveMediateMessage(gtuint messageIndex, GtMediateObjectMessage* pSander){};

public:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);	
};


