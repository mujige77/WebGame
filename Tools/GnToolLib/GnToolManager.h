#pragma once

#include <GnDirectx9Renderer.h>
#include <GnRenderFrame.h>

class GnFrame;
class GnToolManager : public GnMemoryObject
{
private:
	static GnToolManager* mSingletone;
	static GnList<GnFrame*> mFrames;
	
protected:
	static GnRenderFramePtr mspsRenderFrame;
	GnRendererPtr mpsRenderer;

public:
	GnToolManager(void);
	~GnToolManager(void);
	static void StartupEBM();
	static void ShutdownEBM();
	static GnToolManager* Singletone();

	bool CreateRenderer(GnWindowHandle hwnd);
	void Render(GnWindowHandle hwnd);
	void Update(float fTime, GnWindowHandle hwnd);

	static void AddFrame(GnFrame* frame);
	static void RemoveFrame(GnFrame* frame);	
};