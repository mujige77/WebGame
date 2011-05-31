#include "StdAfx.h"
#include "GcPropertyGridNumberPair.h"


GcPropertyGridNumberPair::GcPropertyGridNumberPair(const CString& strGroupName, int nMinValue1, int nMaxValue1
	, int nMinValue2, int nMaxValue2, DWORD_PTR dwData, BOOL bIsValueList)  : GcPropertyGridProperty(strGroupName
	, dwData, bIsValueList)
{
	m_nMinValue1 = nMinValue1;
	m_nMaxValue1 = nMaxValue1;
	m_nMinValue2 = nMinValue2;
	m_nMaxValue2 = nMaxValue2;
}


GcPropertyGridNumberPair::~GcPropertyGridNumberPair(void)
{
}

BOOL GcPropertyGridNumberPair::OnUpdateValue()
{
	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndInPlace);
	ASSERT_VALID(m_pWndList);
	ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));

	CString strText;
	m_pWndInPlace->GetWindowText(strText);

	BOOL bIsChanged = FormatProperty() != strText;

	if (bIsChanged)
	{
		CString strDelimeter(_T(","));

		for (int i = 0; !strText.IsEmpty() && i < GetSubItemsCount(); i++)
		{
			CString strItem = strText.SpanExcluding(strDelimeter);
			if (strItem.GetLength() + 1 > strText.GetLength())
			{
				strText.Empty();
			}
			else
			{
				strText = strText.Mid(strItem.GetLength() + 1);
			}
			strItem.TrimLeft();
			strItem.TrimRight();

			int nItem = _ttoi(strItem);
			if ((i == 0) && ((nItem < m_nMinValue1) || (nItem > m_nMaxValue1)))
			{
				static BOOL bRecursedHere = FALSE;
				if (bRecursedHere)
					return TRUE;
				bRecursedHere = TRUE;

				CString strMessage;
				strMessage.Format(_T("Height value must be between %d and %d."), m_nMinValue1, m_nMaxValue1);
				AfxMessageBox(strMessage);

				bRecursedHere = FALSE;
				return FALSE;
			}
			else if ((i == 1) && ((nItem < m_nMinValue2) || (nItem > m_nMaxValue2)))
			{
				static BOOL bRecursedHere = FALSE;
				if (bRecursedHere)
					return TRUE;
				bRecursedHere = TRUE;

				CString strMessage;
				strMessage.Format(_T("Width value must be between %d and %d."), m_nMinValue2, m_nMaxValue2);
				AfxMessageBox(strMessage);

				bRecursedHere = FALSE;
				return FALSE;
			}
		}

		return GcPropertyGridProperty::OnUpdateValue();
	}

	return TRUE;
}

GtBoundedNumberSubProp::GtBoundedNumberSubProp(const CString& strName, const COleVariant& varValue, int nMinValue
	, int nMaxValue, LPCTSTR lpszDescr) : GcPropertyGridProperty(strName, varValue, lpszDescr)
{
	m_nMinValue = nMinValue;
	m_nMaxValue = nMaxValue;
}

BOOL GtBoundedNumberSubProp::OnUpdateValue()
{
	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndInPlace);
	ASSERT_VALID(m_pWndList);
	ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));

	BOOL bRet = TRUE;
	CString strText;
	m_pWndInPlace->GetWindowText(strText);

	BOOL bIsChanged = FormatProperty() != strText;
	if (bIsChanged)
	{
		int nItem = _ttoi(strText);
		if ((nItem < m_nMinValue) || (nItem > m_nMaxValue))
		{
			static BOOL bRecursedHere = FALSE;
			if (bRecursedHere)
				return TRUE;
			bRecursedHere = TRUE;

			CString strMessage;
			strMessage.Format(_T("Value must be between %d and %d."), m_nMinValue, m_nMaxValue);
			AfxMessageBox(strMessage);

			bRecursedHere = FALSE;
			return FALSE;
		}

		bRet = GcPropertyGridProperty::OnUpdateValue();

		if (m_pParent != NULL)
		{
			m_pWndList->OnPropertyChanged(m_pParent);
		}
	}

	return bRet;
}