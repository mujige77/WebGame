#pragma once


// GcTasksPane

class GcTasksPane : public CMFCTasksPane
{
	DECLARE_DYNAMIC(GcTasksPane)

public:
	GcTasksPane();
	virtual ~GcTasksPane();

	void SetVisibleCaptionBar(bool bShow);
protected:
	DECLARE_MESSAGE_MAP()	

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


