#pragma once
#ifndef GNFRAME_H
#define GNFRAME_H

#include <GnRenderTarget.h>
#include <GnScreenMesh.h>
#include <GnRenderView.h>
#include <GnRenderViewSet.h>

class GnFrame : public GnObject
{
protected:
	GnRenderViewSet* mpRenderViewSet;	
	GnRenderView* mpRenderView;
	GnWindowHandle mWindowHandle;
	GnScreenMesh* mesh;
	GnTObjectArray<GtObjectPtr> mObjects;	

public:	
	virtual ~GnFrame(void);

	static GnFrame* Create(GnWindowHandle hwnd);
	bool RecreateRenderTarget(int iWidth, int iHeight);

	void AddObject(GtObject* pObject);
	void RemoveObject(GtObject* val);

	void Update( float fTime );
	void SetTimeCtrl(float ftime, GnTimeController* pTimeCtrl);
	void Stop();

	inline GnWindowHandle GetWindowHandle() const { return mWindowHandle; }
	inline GnRenderViewSet* GetRenderViewSet() const { return mpRenderViewSet; }
	inline GnRenderView* GetRenderView() const { return mpRenderView; }	

protected:
	static Gn2DBackBuffer* CreateBackBuffer(GnWindowHandle hwnd, int iWidth, int iHeight);

protected:
	GnFrame(GnRenderViewSet* pRenderViewSet, GnRenderView* pRenderView);
	
};

GnSmartPointer(GnFrame);

#endif // GNFRAME_H