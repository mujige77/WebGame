#pragma once
#include "GcPropertyGridCtrl.h"
#include "GcVSListBox.h"
#include "Gc2DTexturePropEntity.h"
#include "GcEditorPropertyPage.h"
#include "afxwin.h"

class GcEditorSequenceTexture : public GcEditorPropertyPage
{
	class TextureListBox : public GcVSListBox
	{
	protected:
		bool mEnableAddItem;

	public:
		TextureListBox() : GcVSListBox(true),mEnableAddItem(true)
		{}
		virtual ~TextureListBox(){};

		void OnEndEditLabel(LPCTSTR lpszLabel);		

		virtual void OnBrowse();
		virtual void CreateNewItem();		
	};
	class AniListBox : public GcVSListBox
	{
	public:
		AniListBox() : GcVSListBox(true)
		{ SetEnableEdit( false ); }
		virtual ~AniListBox(){};

	protected:		
		virtual void CreateNewItem();		
		virtual BOOL RemoveItem(int iItem);
		CString GetMakeName(int count);
	};

	DECLARE_DYNAMIC(GcEditorSequenceTexture)
	enum { IDD = IDD_SEQUENCE_PAGE2 };
	
	static const int msNumTexture = 1;
protected:
	static float mDefaultStartTime;
	static float mDefaultEndTime;

	GcPropertyGridCtrl mPropList;
	CStatic mPropLocation;
	AniListBox mAniListBox;
	TextureListBox mTextureListBox;

	CEdit mETDefaultStartTime;
	CEdit mETDefaultEndTime;
	
	Gc2DTexturePropEntity mpTextureAnimationPropEntity;
	GcPropertyEntityPtr mpEntity;
	Gn2DTextureAniPtr mpsCurrentAni;
	GnTObjectArray<Gn2DTextureAniPtr> mAniCtrls;	

public:
	GcEditorSequenceTexture();
	virtual ~GcEditorSequenceTexture();
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
	void GeFileName(CString strName);
	void AddAniItem(GTVSITEMACTIVATE* item);	
	void RemoveAniItem(GTVSITEMACTIVATE* item);
	void AddTextureItem(GTVSITEMACTIVATE* item);	
	void RemoveTextureItem(GTVSITEMACTIVATE* item);
	void RenameTextureItem(int index);
	void RenameTextureItem(int uiIndex, CString strFilePath);

	void SelectChangeTextureItem(int uiIndex);

public:
	afx_msg void OnChangeDefaultstarttime();
	afx_msg void OnChangeDefaultendtime();
	afx_msg void OnDeltaposDefaultstarttime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposDefaultendtime(NMHDR *pNMHDR, LRESULT *pResult);
};