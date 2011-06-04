#pragma once
#include "GcToolBarDockable.h"
#include "GcTemplateListCtrl.h"
#include "Gt2DActor.h"
// �𵨸��̳�, ĳ����(����) ������Ʈ�� �̸��� �ҷ����� ��
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
	Gt2DActorPtr mpsCurrentObject;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtDeltemplate();
	afx_msg void OnBtNewtemplate();
	afx_msg void OnBtOpentemplate();
	
	// ���� ����� ���մ� ������Ʈ ����Ʈ�� ���� �ε� �Ѵ�.
	void SaveTemplateList(const gchar* filePath);
	void LoadTemplateList(const gchar* filePath);

protected:	
	virtual void ReciveNotiyfiMessage(WPARAM wParam, LPARAM lParam);	
	Gt2DActor* GetActorObject(CString itemText );
	void AddItem(CString itemName, gint8 iActortype, bool bSelected = false);
	void SelectItem(int iIndex);
public:
	afx_msg void OnSaveObjectstate();
};

