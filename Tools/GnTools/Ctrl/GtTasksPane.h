#pragma once


// GtTasksPane

class GtTasksPane : public CMFCTasksPane
{
	DECLARE_DYNAMIC(GtTasksPane)

public:
	GtTasksPane();
	virtual ~GtTasksPane();

	void SetVisibleCaptionBar(bool bShow);
protected:
	DECLARE_MESSAGE_MAP()	

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


