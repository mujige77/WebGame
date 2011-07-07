#pragma once
#include "GcToolBarDockable.h"
#include "GcTemplateListCtrl.h"
#include "Gt2DActor.h"
// 모델링이나, 캐릭터(엑터) 오브젝트의 이름을 불러오는 곳
class GnFrame;
class GcTemplateDockable : public GcToolBarDockable
{
	DECLARE_DYNAMIC(GcTemplateDockable)

public:
	GcTemplateDockable();
	virtual ~GcTemplateDockable();

	struct TemplateListData
	{
		TemplateListData(){}
		TemplateListData( const gtchar* pcName, gint8 uiObjectType )
		{
			mObjectName = pcName;
			mObjectType = uiObjectType;
		}
		CString mObjectName;
		gint8 mObjectType;
	};	
	
protected:
	DECLARE_MESSAGE_MAP()
	int mLastSelectItem;
	GcTemplateListCtrl mListCtrl;
	CArray<TemplateListData> mTemplateList;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtDeltemplate();
	afx_msg void OnBtNewtemplate();
	afx_msg void OnBtOpentemplate();
	
	// 현재 만들어 져잇는 오브젝트 리스트를 저장 로드 한다.
	void SaveTemplateList(const gchar* filePath);
	void LoadTemplateList(const gchar* filePath);

protected:	
	virtual void AddItem(CString itemName, gint8 iActortype, bool bSelected = false);
	virtual void DoNewTemplate(){}
	virtual void DoDelTemplate(){}
	virtual void DoOpenTemplate(){}

};


