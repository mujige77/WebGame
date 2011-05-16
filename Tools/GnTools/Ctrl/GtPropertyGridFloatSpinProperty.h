#pragma once
#include "GtPropertyGridProperty.h"
class GtPropertyGridFloatSpinProperty : public GtPropertyGridProperty
{
protected:
	float mFloatVlaue;
	float mAccumulateDelta;
public:
	GtPropertyGridFloatSpinProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	GtPropertyGridFloatSpinProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);
	virtual ~GtPropertyGridFloatSpinProperty(void);

	void EnableFloatSpinControl(bool bEnable, int iMin, int iMax);
	virtual CSpinButtonCtrl* CreateSpinControl(CRect rectSpin);
	virtual BOOL OnUpdateValue();
	virtual BOOL OnEndEdit();
};

