#include "StdAfx.h"
#include "GcPropertyGridProperty.h"
#include "GcFloatSpinButtonCtrl.h"
#define AFX_PROP_HAS_LIST 0x0001
#define AFX_PROP_HAS_BUTTON 0x0002
#define AFX_PROP_HAS_SPIN 0x0004

GcPropertyGridProperty::GcPropertyGridProperty(const CString& strGroupName, DWORD_PTR dwData,
	BOOL bIsValueList) : CMFCPropertyGridProperty(strGroupName, dwData, bIsValueList), mEnableGroupButton( false )
	, mGroupButtonWidth(100), mFloatSpin(false)
{

}

GcPropertyGridProperty::GcPropertyGridProperty(const CString& strName, const COleVariant& varValue,
	LPCTSTR lpszDescr, DWORD_PTR dwData, LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars) :
CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
	, mEnableGroupButton( false ), mGroupButtonWidth(100), mFloatSpin(false)
{
}

GcPropertyGridProperty::~GcPropertyGridProperty(void)
{
}

BOOL GcPropertyGridProperty::OnUpdateValue()
{
	if( CMFCPropertyGridProperty::OnUpdateValue() == false )
	{
		GnLogA("Failed GridProperty UpdateValue");
		return false;
	}
	mUpdateEvent.EmitSignal( this );
	return true;
}

BOOL GcPropertyGridProperty::OnEdit(LPPOINT lptClick)
{
	if( mEnableGroupButton == false )
		return CMFCPropertyGridProperty::OnEdit( lptClick );

	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndList);

	if (!HasValueField())
		return FALSE;

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

BOOL GcPropertyGridProperty::OnDblClk(CPoint point)
{
	if( mEnableGroupButton )
		return FALSE;

	return CMFCPropertyGridProperty::OnDblClk( point );
}

BOOL GcPropertyGridProperty::OnSetCursor() const
{
	if (m_bInPlaceEdit)
		return FALSE;

	if (m_bIsValueList)
	{
		if( mEnableGroupButton ) 
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_IBEAM));
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
		if( mEnableGroupButton ) 
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_IBEAM));
		return TRUE;
	}

	return FALSE;
}

void GcPropertyGridProperty::AdjustButtonRect()
{
	CMFCPropertyGridProperty::AdjustButtonRect();
	if( mEnableGroupButton ) 
	{
		CRect rectEdit = m_Rect;
		rectEdit.DeflateRect(0, 2);
		rectEdit.left = m_pWndList->GetListRect().left + m_pWndList->GetLeftColumnWidth() + m_Rect.Height() + AFX_TEXT_MARGIN + 1;
		m_rectButton.left = rectEdit.left;

	}
}

void GcPropertyGridProperty::DrawButton(CDC* pDC)
{
	if( mEnableGroupButton == false )
		return;

	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	ASSERT_VALID(m_pWndList);
	AdjustButtonRect();

	CBrush cbrush;
	cbrush.CreateSysColorBrush(COLOR_BTNSHADOW);
	pDC->FillRect(m_rectButton, &cbrush);
	pDC->DrawText( mButtonName, m_rectButton, DT_SINGLELINE | DT_CENTER | DT_VCENTER );
}

bool GcPropertyGridProperty::ButtonHitTest(CPoint point)
{
	if( mEnableGroupButton == false )
		return false;

	AdjustButtonRect();
	if( point.x > m_rectButton.left && m_rectButton.right > point.x )
		return true;

	return false;
}

void GcPropertyGridProperty::SetEnableGroupButton(bool val, LPCTSTR pcName)
{
	if( val == true )
	{
		m_dwFlags = AFX_PROP_HAS_BUTTON;
		m_bGroup = true;
	}
	else
	{
		m_dwFlags = 0;
		m_bGroup = false;
	}

	mEnableGroupButton = val;
	GnAssert( val && pcName );
	mButtonName = pcName;
}

void GcPropertyGridProperty::SetDefaultValue()
{
	switch (m_varValue.vt)
	{
	case VT_BSTR:
		m_varValue = _T("");
		break;
	case VT_UI1:
		m_varValue = (BYTE)0;
		break;
	case VT_I2:
		m_varValue = (short)0;
		break;
	case VT_INT:
	case VT_I4:
		m_varValue = (long)0;
		break;
	case VT_UI2:
		m_varValue.uiVal = (unsigned short)0;
		break;
	case VT_UINT:
	case VT_UI4:
		m_varValue.ulVal = (unsigned long)(0);
		break;
	case VT_R4:
		m_varValue = (float)0.0f;
		break;
	case VT_R8:
		m_varValue = (double)0.0;;
		break;
	case VT_BOOL:
		m_varValue = (VARIANT_BOOL)1;
		break;
	}

	Redraw();
}

void GcPropertyGridProperty::SubscribeToUpdateEvent(GnBaseSlot1<GcPropertyGridProperty*>* pSlot)
{
	mUpdateEvent.Subscribe( pSlot );
}

void GcPropertyGridProperty::EnableFloatSpinControl(bool bEnable, int iMin, int iMax)
{
	switch (m_varValue.vt)
	{
	case VT_R4:
	case VT_R8:
		break;
	default:
		GnAssert(FALSE);
		return;
	}

	m_nMinValue = iMin;
	m_nMaxValue = iMax;

	if (bEnable)
	{
		mFloatSpin = true;
		m_dwFlags |= AFX_PROP_HAS_SPIN;
	}
	else
	{
		m_dwFlags &= ~AFX_PROP_HAS_SPIN;
	}
}

CSpinButtonCtrl* GcPropertyGridProperty::CreateSpinControl(CRect rectSpin)
{
	if( mFloatSpin == false )
		return CMFCPropertyGridProperty::CreateSpinControl( rectSpin );

	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndList);

	CSpinButtonCtrl* pWndSpin = new GcFloatSpinButtonCtrl;

	if (!pWndSpin->Create(WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS | UDS_NOTHOUSANDS
		, rectSpin, m_pWndList, AFX_PROPLIST_ID_INPLACE))
	{
		return NULL;
	}

	pWndSpin->SetBuddy(m_pWndInPlace);

	if (m_nMinValue != 0 || m_nMaxValue != 0)
	{
		pWndSpin->SetRange32(m_nMinValue, m_nMaxValue);
	}

	return pWndSpin;
}