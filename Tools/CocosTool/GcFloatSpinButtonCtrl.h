#pragma once


// GcFloatSpinButtonCtrl

class GcFloatSpinButtonCtrl : public CMFCSpinButtonCtrl
{

protected:
	float mDelta;

public:
	GcFloatSpinButtonCtrl();
	virtual ~GcFloatSpinButtonCtrl();

	inline float GetDelta() { return mDelta; }
	inline void SetDelta(float val) { mDelta = val; }

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDeltapos(NMHDR *pNMHDR, LRESULT *pResult);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


