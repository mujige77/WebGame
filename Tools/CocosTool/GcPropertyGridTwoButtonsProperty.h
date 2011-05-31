#pragma once
#include "GcPropertyGridProperty.h"
class GcPropertyGridTwoButtonsProperty : public GcPropertyGridProperty
{
public:
	GcPropertyGridTwoButtonsProperty(int buttonImageIndex, const CString& strName
		, const COleVariant& varValue, LPCTSTR lpszDescr = NULL);

protected:
	virtual BOOL HasButton() const { return TRUE; }
	virtual void AdjustButtonRect();
	virtual void OnClickButton(CPoint point);
	virtual void OnDrawButton(CDC* pDC, CRect rectButton);

	CImageList m_images;
};
