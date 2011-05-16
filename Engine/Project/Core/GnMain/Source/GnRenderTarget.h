#ifndef GNRENDERTARGET_H
#define GNRENDERTARGET_H

#include "Gn2DBackBuffer.h"

class GNMAIN_ENTRY GnRenderTarget : public GnSmartObject
{
	enum
	{
		MAX_BACKBUFFER_COUNT = 4,
	};
protected:
	Gn2DBackBufferPtr mpBackBuffers[MAX_BACKBUFFER_COUNT];	
	gtuint mBackBufferCount;

public:
	virtual ~GnRenderTarget();
	static GnRenderTarget* Create(Gn2DBackBuffer* backBuffers);
	void AddBackBuffer(Gn2DBackBuffer* pBackBuffer);
	inline gtuint GetBufferCount() { return mBackBufferCount; }	

	inline Gn2DBackBuffer* GetBackBuffer(gtuint num)
	{
		GnAssert(mBackBufferCount > num);
		return mpBackBuffers[num];
	}

	guint GetWidth(gtuint index)
	{
		if(mBackBufferCount >= index)
			return mpBackBuffers[index]->GetWidth();
		return 0;
	};
	guint GetHeight(gtuint index)
	{
		if(mBackBufferCount >= index)
			return mpBackBuffers[index]->GetHeight();
		return 0;
	};

protected:
	GnRenderTarget();	

};
GnSmartPointer(GnRenderTarget);

#endif // GNRENDERTARGET_H