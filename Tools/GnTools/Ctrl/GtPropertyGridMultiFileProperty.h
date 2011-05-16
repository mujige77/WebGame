#pragma once
#include "GtOpenDialog.h"

class GtPropertyGridMultiFileProperty : public CMFCPropertyGridFileProperty
{
	DECLARE_DYNAMIC(GtPropertyGridMultiFileProperty)

public:

	GtPropertyGridMultiFileProperty(const CString& strName, const CString& strFolderName, bool bGroup = false,
		DWORD_PTR dwData = 0, LPCTSTR lpszDescr = NULL);
	GtPropertyGridMultiFileProperty(const CString& strName, BOOL bOpenFileDialog, const CString& strFileName,
		bool bGroup = false, LPCTSTR lpszDefExt = NULL,
		DWORD dwFlags = OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		LPCTSTR lpszFilter = NULL, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0);
	virtual ~GtPropertyGridMultiFileProperty();

	// Overrides
public:
	virtual void OnClickButton(CPoint point);

	// 버튼 클릭 안되는 것 때문에 상속 받았음
	virtual BOOL OnEdit(LPPOINT lptClick);
	// 에디트 박스 더블클릭하면 들어 오는 곳임 에디트 박스 들어가게되면 다시 만들어 야됨
	virtual BOOL OnDblClk(CPoint point){ return FALSE; }

	virtual BOOL OnSetCursor() const;	
	virtual void AdjustButtonRect();	

	// 파일 다이얼로그를 열기위한 버튼을 그린다
	virtual void DrawButton(CDC* pDC);
	// 파일 선택하기 버튼쪽에 마우스포인트가 있는지 확인
	// (루트 일때 더블 클릭하면 확장 또는 숨기기가 되는데 그것을 막기위해 만듬)
	bool ButtonHitTest(CPoint point);
	
	CString GetPath(int iIndex);

};

