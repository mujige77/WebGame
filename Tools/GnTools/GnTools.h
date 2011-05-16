#ifndef GNTOOLS_H
#define GNTOOLS_H

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CGnToolsApp:
// 이 클래스의 구현에 대해서는 GnTools.cpp을 참조하십시오.
//
class GnFrame;
GnFrame* GetActiveGnFrame();

class CGnToolsApp : public CWinAppEx
{
public:
	CGnToolsApp();


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	COleTemplateServer m_server;
		// 문서 만들기에 대한 서버 개체입니다.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGnToolsApp theApp;

#endif // GNTOOLS_H