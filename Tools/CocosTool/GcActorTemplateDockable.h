#pragma once
#include "GcTemplateDockable.h"

class GcActorTemplateDockable : public GcTemplateDockable
{
public:
	GcActorTemplateDockable(void);
	~GcActorTemplateDockable(void);
	Gt2DActorPtr mpsCurrentObject;

protected:
	virtual void ReciveNotiyfiMessage(WPARAM wParam, LPARAM lParam);	
	Gt2DActor* GetActorObject(CString itemText );
	void SelectItem(int iIndex);
	virtual void DoNewTemplate();
	virtual void DoDelTemplate();
	virtual void DoOpenTemplate();
	virtual const gchar* GetFileName() {
		return "templatelist.lst";
	}
};

