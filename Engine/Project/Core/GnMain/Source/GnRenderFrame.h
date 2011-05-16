#ifndef GNRENDERFRAME_H
#define GNRENDERFRAME_H

#include "GnRenderViewSet.h"
#include "GnListManager.h"

class GNMAIN_ENTRY GnRenderFrame : public GnListManager<GnRenderViewSet, GnRenderViewSetPtr>
{
public:
	GnRenderFrame();
	virtual ~GnRenderFrame();

	void Draw();
	void Render();
	void Update(float fTime);
private:
};

GnSmartPointer(GnRenderFrame);

#endif // GNRENDERFRAME_H