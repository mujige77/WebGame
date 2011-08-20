#pragma once
#include "afxwin.h"
#include "GGridCtrl.h"
#include "GDesignFormView.h"
#include "GStageLevel.h"

class GStageLevelDesignView : public GDesignFormView
{
	DECLARE_DYNCREATE(GStageLevelDesignView)
protected:
	CStatic mGpMobAttackLine;
	CStatic mGpMopAppear;
	CEdit mEtStageNumber;
	CEdit mEtBossMobIndex;	
	GStageLevelGridCtrl* mpGcMopAppear;
	GStageLevelGridCtrl* mpGcMobAttackLine;
	bool mLoadedStageLevel;
	GStageLevel mLoadStageLevelValue;

public:
	static CRuntimeClass* CreateFormView() {
		return RUNTIME_CLASS(GStageLevelDesignView);
	}
	static const gchar* GetStaicName() {
		return "StageLevel";
	}
public:	
	virtual void Save(GnStream* pStream);
	virtual void Load(GnStream* pStream);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual const gchar* GetName() {
		return "StageLevel";
	}

protected:
	void SaveStageLevel(GStageLevel* pStageLevel);
	void LoadStageLevel(GStageLevel* pStageLevel);

protected:
	virtual void OnInitialUpdate();
	

protected:
	GStageLevelDesignView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~GStageLevelDesignView();

protected:
	afx_msg void OnClickedAddMob();
	afx_msg void OnClickedDeleteMob();	



public:
	enum { IDD = IDD_GSTAGELEVELDESIGNVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT mStageNumber;
	UINT mBossMobIndex;
};


