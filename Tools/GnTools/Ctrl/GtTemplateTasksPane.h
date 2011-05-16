#pragma once
#include "GtTasksPane.h"
#include "GtTemplateListForm.h"
// GtTemplateTasksPane

class GtTemplateTasksPane : public GtTasksPane
{
	DECLARE_DYNAMIC(GtTemplateTasksPane)

protected:
	GtTemplateListForm mTemplateList;
	
public:
	GtTemplateTasksPane();
	virtual ~GtTemplateTasksPane();
	
	inline GtTemplateListForm& GetTemplateList() {
		return mTemplateList;
	}

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


