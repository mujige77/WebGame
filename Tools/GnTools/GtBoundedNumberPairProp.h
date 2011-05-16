#pragma once
#include "GtPropertyGridProperty.h"
class GtBoundedNumberPairProp : public GtPropertyGridProperty
{
private:
	int m_nMinValue1;
	int m_nMaxValue1;
	int m_nMinValue2;
	int m_nMaxValue2;

public:
	GtBoundedNumberPairProp(const CString& strGroupName, int nMinValue1, int nMaxValue1
		, int nMinValue2, int nMaxValue2, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	virtual ~GtBoundedNumberPairProp(void);

	virtual BOOL OnUpdateValue();
};

class GtBoundedNumberSubProp : public GtPropertyGridProperty
{
public:
	GtBoundedNumberSubProp(const CString& strName, const COleVariant& varValue, int nMinValue,
		int nMaxValue, LPCTSTR lpszDescr = NULL);

	virtual BOOL OnUpdateValue();
private:
	int m_nMinValue;
	int m_nMaxValue;
};