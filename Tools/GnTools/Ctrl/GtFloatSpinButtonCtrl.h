#pragma once


// GtFloatSpinButtonCtrl

class GtFloatSpinButtonCtrl : public CMFCSpinButtonCtrl
{
	DECLARE_DYNAMIC(GtFloatSpinButtonCtrl)

protected:
	float mDelta;

public:
	GtFloatSpinButtonCtrl();
	virtual ~GtFloatSpinButtonCtrl();

	inline float GetDelta() { return mDelta; }
	inline void SetDelta(float val) { mDelta = val; }

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDeltapos(NMHDR *pNMHDR, LRESULT *pResult);
};


