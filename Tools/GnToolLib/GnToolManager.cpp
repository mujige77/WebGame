#include "GnToolLibPCH.h"
#include "GnToolManager.h"
#include "GnFrame.h"

GnToolManager* GnToolManager::mSingletone = NULL;
GnList<GnFrame*> GnToolManager::mFrames;
GnRenderFramePtr GnToolManager::mspsRenderFrame;
GnToolManager::GnToolManager(void)
{
}


GnToolManager::~GnToolManager(void)
{
}

void GnToolManager::StartupEBM()
{
	mSingletone = GnNew GnToolManager();
}

void GnToolManager::ShutdownEBM()
{
	GnDelete mSingletone;
	mspsRenderFrame = NULL;
}

GnToolManager* GnToolManager::Singletone()
{
	return mSingletone;
}

bool GnToolManager::CreateRenderer(HWND hwnd)
{
	RECT rect;
	GetClientRect(hwnd, &rect);
	mpsRenderer = GnDirectx9Renderer::Create(rect.right - rect.left, rect.bottom - rect.top, hwnd);
	mspsRenderFrame = GnNew GnRenderFrame();
	return true;
}

void GnToolManager::Render(GnWindowHandle hwnd)
{
	mspsRenderFrame->Draw();	
	//mpsRenderer->BeginFrame();
	//GnListIterator<GnFrame*> iter = mFrames.GetIterator();
	//while(iter.Valid())
	//{
	//	iter.Item()->Render();
	//	iter.Forth();
	//}
	//
	//mpsRenderer->EndFrame();	
	mspsRenderFrame->Render();
}

void GnToolManager::Update(float fTime, GnWindowHandle hwnd)
{
	GnListIterator<GnFrame*> iter = mFrames.GetIterator();
	while(iter.Valid())
	{
		if( iter.Item()->GetWindowHandle() == hwnd )
		{
			iter.Item()->Update( fTime );
			break;
		}
		iter.Forth();
	}

	mspsRenderFrame->Update(fTime);	
}

void GnToolManager::AddFrame(GnFrame* frame)
{
	mFrames.Append(frame);  
	mspsRenderFrame->Append(frame->GetRenderViewSet());
	GnLogA("AddFrame");
}

void GnToolManager::RemoveFrame(GnFrame* frame)
{
	GnListIterator<GnFrame*> iter = mFrames.GetIterator();
	while(iter.Valid())
	{
		if( frame == iter.Item() )
		{
			mFrames.Remove(iter);
			return;
		}
		iter.Forth();
	}
	mspsRenderFrame->Remove(frame->GetRenderViewSet());
	GnLogA("RemoveFrame");
}