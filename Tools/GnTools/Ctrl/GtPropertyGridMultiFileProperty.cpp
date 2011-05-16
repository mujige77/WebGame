#include "StdAfx.h"
#include "GtPropertyGridMultiFileProperty.h"

#include "afxcontrolbarutil.h"
#include "afxpropertygridctrl.h"
#include "afxcolorbar.h"
#include "afxwinappex.h"
#include "afxshellmanager.h"
#include "afxmenuimages.h"
#include "afxvisualmanager.h"
#include "afxtoolbarcomboboxbutton.h"
#include "afxpopupmenu.h"
#include "afxdrawmanager.h"
#include "afxmaskededit.h"
#include "afxspinbuttonctrl.h"
#include "afxtagmanager.h"
#include "afxctrlcontainer.h"

#define visualManager CMFCVisualManager::GetInstance()
#define AFX_PROP_HAS_LIST 0x0001
#define AFX_PROP_HAS_BUTTON 0x0002
#define AFX_PROP_HAS_SPIN 0x0004

IMPLEMENT_DYNAMIC(GtPropertyGridMultiFileProperty, CMFCPropertyGridProperty)

GtPropertyGridMultiFileProperty::GtPropertyGridMultiFileProperty(const CString& strName, const CString& strFolderName,
	bool bGroup, DWORD_PTR dwData, LPCTSTR lpszDescr) : CMFCPropertyGridFileProperty(strName,
	COleVariant((LPCTSTR)strFolderName), dwData, lpszDescr)
{
	m_dwFlags = AFX_PROP_HAS_BUTTON;
	m_bIsFolder = TRUE;
	m_bGroup = bGroup;	
}

GtPropertyGridMultiFileProperty::GtPropertyGridMultiFileProperty(const CString& strName, BOOL bOpenFileDialog,
	const CString& strFileName, bool bGroup, LPCTSTR lpszDefExt, DWORD dwFileFlags, LPCTSTR lpszFilter,
	LPCTSTR lpszDescr, DWORD_PTR dwData) : CMFCPropertyGridFileProperty(strName, bOpenFileDialog, strFileName,
	lpszDefExt, dwFileFlags, lpszFilter, lpszDescr, dwData)
{
	m_dwFlags = AFX_PROP_HAS_BUTTON;
	m_bIsFolder  = FALSE;
	m_bGroup = bGroup;
}

GtPropertyGridMultiFileProperty::~GtPropertyGridMultiFileProperty()
{
}

BOOL GtPropertyGridMultiFileProperty::OnEdit(LPPOINT lptClick)
{
	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndList);

	if (!HasValueField())
	{
		return FALSE;
	}

	m_pWndInPlace = NULL;

	CRect rectEdit;
	CRect rectSpin;

	AdjustInPlaceEditRect(rectEdit, rectSpin);

	BOOL bDefaultFormat = FALSE;
	m_pWndInPlace = CreateInPlaceEdit(rectEdit, bDefaultFormat);

	if( m_pWndInPlace != NULL )
	{
		m_pWndInPlace->HideCaret();
		m_pWndInPlace->ShowWindow(SW_HIDE);
		m_bInPlaceEdit = TRUE;
		return TRUE;
	}
	return FALSE;
}

void GtPropertyGridMultiFileProperty::OnClickButton(CPoint /*point*/)
{
	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndList);
	ASSERT_VALID(m_pWndInPlace);
	ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));

	m_bButtonIsDown = TRUE;
	Redraw();

	CString strPath = m_varValue.bstrVal;
	BOOL bUpdate = FALSE;

	if (m_bIsFolder)
	{
	}
	else
	{
		GtOpenDialog dlg(m_bOpenFileDialog, m_strDefExt, strPath, m_dwFileOpenFlags, m_strFilter, m_pWndList);
		if (dlg.DoModal() == IDOK)
		{
			POSITION pos = dlg.GetStartPosition();
			while(pos)
			{
				strPath = dlg.GetNextPathName(pos);
				CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("이미지"));
				AddSubItem(pGroup);

				CMFCPropertyGridProperty* pProp = NULL;
				pProp = new CMFCPropertyGridProperty(_T("순서 번호"), (_variant_t) GetSubItemsCount(),
					_T("애니메이션 순서를 정합니다."));
				pProp->EnableSpinControl(TRUE, 0, 20);
				pGroup->AddSubItem(pProp);

				pProp = new CMFCPropertyGridFileProperty(_T("이미지 경로"), TRUE, strPath, _T(""),
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, m_strFilter, _T("현재 순서의 이미지를 정합니다"));
				pGroup->AddSubItem(pProp);
				pGroup->Expand(true);
				pGroup->Redraw();
			}
			Expand(true);
			m_pWndList->AdjustLayout();
			bUpdate = TRUE;
		}
	}

	if (bUpdate)
	{
		m_varValue = (LPCTSTR) strPath;
	}

	m_bButtonIsDown = FALSE;
	Redraw();

	if (m_pWndInPlace != NULL)
	{
		m_pWndInPlace->SetFocus();
	}
	else
	{
		m_pWndList->SetFocus();
	}
}

void GtPropertyGridMultiFileProperty::DrawButton(CDC* pDC)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	ASSERT_VALID(m_pWndList);
	AdjustButtonRect();

	CBrush cbrush;
	//cbrush.CreateSolidBrush(0xdddddd);
	cbrush.CreateSysColorBrush(COLOR_BTNSHADOW);
	pDC->FillRect(m_rectButton, &cbrush);

	CString str = _T("이미지 로드");
	pDC->DrawText(str, m_rectButton, DT_SINGLELINE | DT_CENTER | DT_VCENTER);


}

BOOL GtPropertyGridMultiFileProperty::OnSetCursor() const
{
	if (m_bInPlaceEdit)
	{
		return FALSE;
	}

	if (m_bIsValueList)
	{
		return TRUE;
	}

	switch (m_varValue.vt)
	{
	case VT_BSTR:
	case VT_R4:
	case VT_R8:
	case VT_UI1:
	case VT_I2:
	case VT_INT:
	case VT_UINT:
	case VT_I4:
	case VT_UI2:
	case VT_UI4:
		return TRUE;
	}

	return FALSE;
}

void GtPropertyGridMultiFileProperty::AdjustButtonRect()
{
	CMFCPropertyGridProperty::AdjustButtonRect();
	m_rectButton.left -= 100;
}

bool GtPropertyGridMultiFileProperty::ButtonHitTest(CPoint point)
{
	AdjustButtonRect();
	if( point.x > m_rectButton.left && m_rectButton.right > point.x )
		return true;

	return false;
}

CString GtPropertyGridMultiFileProperty::GetPath(int iIndex)
{
	CMFCPropertyGridProperty* parentProp = GetSubItem(iIndex);
	if( parentProp == NULL )
		return _T("");
	
	CMFCPropertyGridProperty* pathProp = parentProp->GetSubItem(1);
	if( pathProp == NULL )
		return _T("");

	return pathProp->GetValue();
}