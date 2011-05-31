// GcFloatSpinButtonCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CocosTool.h"
#include "GcFloatSpinButtonCtrl.h"
#define AFX_UM_UPDATESPIN (WM_USER + 101)

// GcFloatSpinButtonCtrl

GcFloatSpinButtonCtrl::GcFloatSpinButtonCtrl() : mDelta(0.0f)
{

}

GcFloatSpinButtonCtrl::~GcFloatSpinButtonCtrl()
{
}


BEGIN_MESSAGE_MAP(GcFloatSpinButtonCtrl, CMFCSpinButtonCtrl)
	ON_NOTIFY_REFLECT(UDN_DELTAPOS, &GcFloatSpinButtonCtrl::OnDeltapos)
END_MESSAGE_MAP()



// GcFloatSpinButtonCtrl 메시지 처리기입니다.




void GcFloatSpinButtonCtrl::OnDeltapos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	float fDelta = (float)pNMUpDown->iDelta;
	mDelta += fDelta / 1000;	
	GetParent()->PostMessage(AFX_UM_UPDATESPIN);
	CString strDelta;
	strDelta.Format( _T("%.3f"), mDelta);
	SetWindowText( strDelta );

	if( GetBuddy() )
		GetBuddy()->SetWindowText( strDelta );
}


LRESULT GcFloatSpinButtonCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = CMFCSpinButtonCtrl::WindowProc(message, wParam, lParam);

	switch( message )
	{
	case UDM_SETBUDDY:
		{
			CWnd* buddy = GetBuddy();
			CString strDelta;
			if( buddy && buddy->GetSafeHwnd() == (HWND)wParam )
			{
				buddy->GetWindowText( strDelta );
				_stscanf_s( strDelta.GetString(), _T("%f"), &mDelta );
			}
		}
	}
	return ret;
}
