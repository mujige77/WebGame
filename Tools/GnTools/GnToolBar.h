#pragma once


// GnToolBar

class GnToolBar : public CMFCToolBar
{
	DECLARE_DYNAMIC(GnToolBar)

	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }

public:
	GnToolBar();
	virtual ~GnToolBar();

protected:
	DECLARE_MESSAGE_MAP()


};


