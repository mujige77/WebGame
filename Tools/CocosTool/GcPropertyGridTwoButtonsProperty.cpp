#include "StdAfx.h"
#include "GcPropertyGridTwoButtonsProperty.h"


GcPropertyGridTwoButtonsProperty::GcPropertyGridTwoButtonsProperty(int buttonImageIndex
	, const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr)
	: GcPropertyGridProperty(strName, varValue, lpszDescr)
{
	CBitmap bmp;
	bmp.LoadBitmap(buttonImageIndex);

	m_images.Create(14, 14, ILC_MASK | ILC_COLOR8, 0, 0);
	m_images.Add(&bmp, RGB(255, 0, 255));
}

void GcPropertyGridTwoButtonsProperty::AdjustButtonRect()
{
	CMFCPropertyGridProperty::AdjustButtonRect();
	m_rectButton.left -= m_rectButton.Width();
}

void GcPropertyGridTwoButtonsProperty::OnClickButton(CPoint point)
{
	BOOL bIsLeft = point.x < m_rectButton.CenterPoint().x;
	AfxMessageBox(bIsLeft ? _T("Left button clicked") : _T("Right button clicked"));
}

void GcPropertyGridTwoButtonsProperty::OnDrawButton(CDC* pDC, CRect rectButton)
{
	for (int i = 0; i < 2; i++)
	{
		CMFCToolBarButton button;

		CRect rect = rectButton;

		if (i == 0)
		{
			rect.right = rect.left + rect.Width() / 2;
		}
		else
		{
			rect.left = rect.right - rect.Width() / 2;
		}

		CMFCVisualManager::AFX_BUTTON_STATE state = CMFCVisualManager::ButtonsIsHighlighted;

		CMFCVisualManager::GetInstance()->OnFillButtonInterior(pDC, &button, rect, state);

		m_images.Draw(pDC, i, CPoint(rect.left, rect.top), ILD_NORMAL);

		CMFCVisualManager::GetInstance()->OnDrawButtonBorder(pDC, &button, rect, state);
	}
}