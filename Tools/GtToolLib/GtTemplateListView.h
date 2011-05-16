#pragma once
#include "GtToolBarForm.h"

// GtTemplateListView

class GTTOOLLIB_ENTRY GtTemplateListView : public GtToolBarForm
{
	DECLARE_DYNAMIC(GtTemplateListView)

public:
	GtTemplateListView();
	virtual ~GtTemplateListView();
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


