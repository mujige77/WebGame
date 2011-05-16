// GnTextureFile.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GnTools.h"
#include "GnTextureFile.h"


// GnTextureFile

IMPLEMENT_DYNAMIC(GnTextureFile, CWnd)

GnTextureFile::GnTextureFile()
{

}

GnTextureFile::~GnTextureFile()
{
}


BEGIN_MESSAGE_MAP(GnTextureFile, CWnd)
END_MESSAGE_MAP()



// GnTextureFile 메시지 처리기입니다.



//
//BOOL GnTextureFile::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect,
//	CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//	//if (!mSplitter.CreateStatic(this,2,1))
//	//{
//	//	TRACE0("Failed to create split bar ");
//	//	return FALSE;    // failed to create
//	//}
//	//if(!mSplitter.CreateView(0,0,RUNTIME_CLASS(GnTextureFileView),CSize(10,200),pContext))
//	//{
//	//	TRACE0("Failed to create CDBVListView ");
//	//	return FALSE;    // failed to create
//	//}
//	//if(!mSplitter.CreateView(1,0,RUNTIME_CLASS(GnTextureView),CSize(10,100),pContext))
//	//{
//	//	TRACE0("Failed to create CEmpView ");
//	//	return FALSE;    // failed to create
//	//}
//	
//	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
//}
