#pragma once
#include "GcPropertyGridProperty.h"
class GcPropertyGridFloatSpinProperty : public GcPropertyGridProperty
{
protected:
	float mFloatVlaue;
	float mAccumulateDelta;
public:
	GcPropertyGridFloatSpinProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	GcPropertyGridFloatSpinProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);
	virtual ~GcPropertyGridFloatSpinProperty(void);

	void EnableFloatSpinControl(bool bEnable, int iMin, int iMax);
	virtual CSpinButtonCtrl* CreateSpinControl(CRect rectSpin);
	virtual BOOL OnUpdateValue();
	virtual BOOL OnEndEdit();
};

