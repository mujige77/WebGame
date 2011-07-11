#pragma once
#include "GcToolBarDockable.h"
#include "GcTemplateListCtrl.h"
#include "GcTemplateDockable.h"
// 모델링이나, 캐릭터(엑터) 오브젝트의 이름을 불러오는 곳
class GnFrame;
class GcMeshTemplateDockable : public GcTemplateDockable
{
public:
	GcMeshTemplateDockable();
	virtual ~GcMeshTemplateDockable();

protected:
	Gt2DObjectPtr mpsCurrentObject;

protected:	
	virtual void ReciveNotiyfiMessage(WPARAM wParam, LPARAM lParam);	
	Gt2DObject* GetActorObject(CString itemText );
	void SelectItem(int iIndex);
	virtual void DoNewTemplate();
	virtual void DoDelTemplate();
	virtual void DoOpenTemplate();
	virtual const gchar* GetFileName() {
		return "meshlist.lst";
	}
};