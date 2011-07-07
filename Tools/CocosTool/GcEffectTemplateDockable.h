#pragma once
#include "GcToolBarDockable.h"
#include "GcTemplateListCtrl.h"
#include "GcTemplateDockable.h"
// 모델링이나, 캐릭터(엑터) 오브젝트의 이름을 불러오는 곳
class GnFrame;
class GcEffectTemplateDockable : public GcTemplateDockable
{
public:
	GcEffectTemplateDockable();
	virtual ~GcEffectTemplateDockable();

protected:
	Gt2DActorPtr mpsCurrentObject;

protected:	
	virtual void ReciveNotiyfiMessage(WPARAM wParam, LPARAM lParam);	
	Gt2DActor* GetActorObject(CString itemText );
	void SelectItem(int iIndex);

public:
	afx_msg void OnSaveObjectstate();
};


