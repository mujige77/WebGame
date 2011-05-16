#include "StdAfx.h"
#include "GtPropertyGridFloatSpinProperty.h"
#include "GtFloatSpinButtonCtrl.h"

#define AFX_PROP_HAS_LIST 0x0001
#define AFX_PROP_HAS_BUTTON 0x0002
#define AFX_PROP_HAS_SPIN 0x0004

GtPropertyGridFloatSpinProperty::GtPropertyGridFloatSpinProperty(const CString& strGroupName, DWORD_PTR dwData,
	BOOL bIsValueList) : GtPropertyGridProperty(strGroupName, dwData, bIsValueList),	mAccumulateDelta(0.0f)
{

}

GtPropertyGridFloatSpinProperty::GtPropertyGridFloatSpinProperty(const CString& strName, const COleVariant& varValue,
	LPCTSTR lpszDescr, DWORD_PTR dwData, LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars) :
	GtPropertyGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars),
	mFloatVlaue((float)dwData)
{

}
GtPropertyGridFloatSpinProperty::~GtPropertyGridFloatSpinProperty(void)
{
}

void GtPropertyGridFloatSpinProperty::EnableFloatSpinControl(bool bEnable, int iMin, int iMax)
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
		m_dwFlags |= AFX_PROP_HAS_SPIN;
	}
	else
	{
		m_dwFlags &= ~AFX_PROP_HAS_SPIN;
	}
}

CSpinButtonCtrl* GtPropertyGridFloatSpinProperty::CreateSpinControl(CRect rectSpin)
{
	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndList);

	CSpinButtonCtrl* pWndSpin = new GtFloatSpinButtonCtrl;

	if (!pWndSpin->Create(WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS | UDS_NOTHOUSANDS, rectSpin, m_pWndList, AFX_PROPLIST_ID_INPLACE))
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

BOOL GtPropertyGridFloatSpinProperty::OnUpdateValue()
{
	const float minDelta = 0.0009f;
	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndInPlace);
	ASSERT_VALID(m_pWndList);
	ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));

	CString strText;
	m_pWndInPlace->GetWindowText(strText);

	GtFloatSpinButtonCtrl*spin = (GtFloatSpinButtonCtrl*)m_pWndSpin;
	float delta = spin->GetDelta();
	if( delta > minDelta || delta < -minDelta)
	{
		mAccumulateDelta += delta;
		float val = 0.0f;
		_stscanf_s(strText, m_strFormatFloat, &val);
		val += delta;
		if( val <= 0.f )
			val = 0.0f;
		strText.Format(m_strFormatFloat, val);
		m_pWndInPlace->SetWindowText(strText);
	}

	if( TextToVar(strText) || delta > minDelta || delta < -minDelta)
	{
		m_pWndList->OnPropertyChanged(this);
	}
	spin->SetDelta(0.f);
	return TRUE;
}

BOOL GtPropertyGridFloatSpinProperty::OnEndEdit()
{
	float* val;
	switch (m_varValue.vt)
	{
	case VT_R4:
		val = &m_varValue.fltVal;
		break;
	case VT_R8:
		val = (float*)&m_varValue.dblVal;
	default:
		GnAssert(FALSE);
		return false;
	}
	if( *val <= 0.0f ) 
	{
		*val = 0.0f;
	}

	if( CMFCPropertyGridProperty::OnEndEdit() == false )
		return false;

	mAccumulateDelta = 0.0f;
	return true;
}