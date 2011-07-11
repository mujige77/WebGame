#pragma once
#include "GcTasksPane.h"
#include "GcActorTemplateDockable.h"
#include "GcMeshTemplateDockable.h"
// GcTemplateTasks

class GcTemplateTasks : public GcTasksPane
{
	DECLARE_DYNAMIC(GcTemplateTasks)

protected:
	GcActorTemplateDockable mTemplateList;
	GcMeshTemplateDockable  mObjectTemplateList;	

public:
	GcTemplateTasks();
	virtual ~GcTemplateTasks();
	
	inline GcActorTemplateDockable& GetTemplateList() {
		return mTemplateList;
	}
	inline GcMeshTemplateDockable& GetObjectTemplateList() {
		return mObjectTemplateList;
	}

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


