#pragma once
#include "GtPropertyGridCtrl.h"
#include "GtVSListBox.h"
#include "Gt2DTexturePropEntity.h"
#include "GtPropertyPage.h"
#include <GtSMTextureAniCtrl.h>
#include "afxwin.h"

class GtSequenceTextureEditPage : public GtPropertyPage
{
	class TextureListBox : public GtVSListBox
	{
	protected:
		bool mEnableAddItem;

	public:
		TextureListBox() : GtVSListBox(true),mEnableAddItem(true)
		{}
		virtual ~TextureListBox(){};

		void OnEndEditLabel(LPCTSTR lpszLabel);		

		virtual void OnBrowse();
		virtual void CreateNewItem();		
	};
	class AniListBox : public GtVSListBox
	{
	public:
		AniListBox() : GtVSListBox(true) {}
		virtual ~AniListBox(){};

	protected:
		virtual BOOL EditItem(int iIndex){ return FALSE; };
		virtual void CreateNewItem();		
		virtual BOOL RemoveItem(int iItem);
		CString GetMakeName(int count);
	};

	DECLARE_DYNAMIC(GtSequenceTextureEditPage)
	enum { IDD = IDD_SEQUENCE_PAGE2 };
	
	static const int msNumTexture = 1;
protected:
	static float mDefaultStartTime;
	static float mDefaultEndTime;

	GtPropertyGridCtrl mPropList;
	CStatic mPropLocation;
	AniListBox mAniListBox;
	TextureListBox mTextureListBox;

	CEdit mETDefaultStartTime;
	CEdit mETDefaultEndTime;
	
	Gt2DTexturePropEntity mpTextureAnimationPropEntity;
	GtPropertyEntityPtr mpEntity;

	GnTObjectArray<GtSMTextureAniCtrlPtr> mAniCtrls;
	GtSMTextureAniCtrl* mpCurrentAni;

public:
	GtSequenceTextureEditPage();
	virtual ~GtSequenceTextureEditPage();
	virtual void OnOK();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);	

public:
	virtual BOOL OnInitDialog();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	void SelectChangeAniItem( GTVSITEMACTIVATE* item );
	LRESULT OnPropertyChanged(WPARAM wparam, LPARAM lparam);	

protected:
	void GeFileName( CString &strName );
	void AddAniItem(GTVSITEMACTIVATE* item);	
	void RemoveAniItem(GTVSITEMACTIVATE* item);
	void AddTextureItem(GTVSITEMACTIVATE* item);	
	void RemoveTextureItem(GTVSITEMACTIVATE* item);
	void RenameTextureItem(int index);
	void RenameTextureItem(int uiIndex, CString strFilePath);

	void SelectChangeTextureItem(GtSMTextureAniCtrl::AniInfo* pAniInfo);

public:
	afx_msg void OnChangeDefaultstarttime();
	afx_msg void OnChangeDefaultendtime();
	afx_msg void OnDeltaposDefaultstarttime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposDefaultendtime(NMHDR *pNMHDR, LRESULT *pResult);
};