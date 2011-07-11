#pragma once
#include "GcPropertyGridCtrl.h"
#include "GcEditorTextureListBox.h"
#include "Gc2DTexturePropEntity.h"
#include "GcEditorPropertyPage.h"
#include "afxwin.h"

class GcEditorTexture : public GcEditorPropertyPage
{
	DECLARE_DYNAMIC(GcEditorTexture)
	enum { IDD = IDD_SEQUENCE_PAGE2 };

protected:
	static const int msNumTexture = 1;
	static float mDefaultStartTime;
	static float mDefaultEndTime;

protected:
	GcPropertyGridCtrl mPropList;
	CStatic mPropLocation;
	CEdit mETDefaultStartTime;
	CEdit mETDefaultEndTime;

	GcEditorTextureListListBox mTextureListBox;
	GcEditorTextureListBox mTextureBox;

	Gc2DTexturePropEntity mpTextureAnimationPropEntity;
	GcPropertyEntityPtr mpEntity;


protected:
	// 새롭게 시작 해볼까~
	GnTPrimitiveArray<TextureListInfo*> mTextureLists;

public:
	static inline float GetDefaultStartTime();
	static inline void SetDefaultStartTime(float val);
	static inline float GetDefaultEndTime();
	static inline void SetDefaultEndTime(float val);

public:
	GcEditorTexture();
	virtual ~GcEditorTexture();	

public:
	void OnOK();
	bool CheckEnableButton();

public:
	inline GnTPrimitiveArray<TextureListInfo*>* GetTextureLists() {
		return &mTextureLists;
	}
protected:
	void SelectChangeListItem(int iItem);
	void SelectChangeTextureItem(int iItem);
	void GeFileName(CString strName);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);	

public:
	virtual BOOL OnInitDialog();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	LRESULT OnPropertyChanged(WPARAM wparam, LPARAM lparam);

public:
	afx_msg void OnChangeDefaultstarttime();
	afx_msg void OnChangeDefaultendtime();
	afx_msg void OnDeltaposDefaultstarttime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposDefaultendtime(NMHDR *pNMHDR, LRESULT *pResult);


};