#pragma once
#include "GcTasksPane.h"
#include "GcTemplateDockable.h"
// GcTemplateTasks

class GcTemplateTasks : public GcTasksPane
{
	DECLARE_DYNAMIC(GcTemplateTasks)

protected:
	GcTemplateDockable mTemplateList;
	
public:
	GcTemplateTasks();
	virtual ~GcTemplateTasks();
	
	inline GcTemplateDockable& GetTemplateList() {
		return mTemplateList;
	}

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


