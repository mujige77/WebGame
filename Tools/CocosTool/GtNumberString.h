#pragma once
class GtNumberString
{
protected:
	gtstring mString;

public:
	GtNumberString(void);
	~GtNumberString(void);

	void SetNumber(gtuint uiNumberLength, gint uiNumber, const gtchar* pcFrontString = NULL
		, const gtchar* pcBackString = NULL);

	inline gtstring& GetString() {
		return mString;
	}
};

