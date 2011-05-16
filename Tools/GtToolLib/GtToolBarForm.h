#pragma once


// GtToolBarForm

class GtToolBarForm : public CDockablePane
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

	// Construction
public:      // must derive your own class
	GtToolBarForm();
	~GtToolBarForm();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


