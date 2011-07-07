#pragma once
#include "GcTasksPane.h"
#include "GcActorTemplateDockable.h"
#include "GcEffectTemplateDockable.h"
// GcTemplateTasks

class GcTemplateTasks : public GcTasksPane
{
	DECLARE_DYNAMIC(GcTemplateTasks)

protected:
	GcActorTemplateDockable mTemplateList;
	GcEffectTemplateDockable  mEffectTemplateList;	
public:
	GcTemplateTasks();
	virtual ~GcTemplateTasks();
	
	inline GcActorTemplateDockable& GetTemplateList() {
		return mTemplateList;
	}

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


