#ifndef GNDX92DBUFFER_H
#define GNDX92DBUFFER_H

#include <Gn2DBackBuffer.h>

class GnDX92DBuffer : public Gn2DBackBuffer
{
private:
	static LPDIRECT3DSURFACE9 msCurrentBuffers[4];

protected:
	LPDIRECT3DSURFACE9 mpSurface;
	bool mIsDisplayBuffer;

public:
	inline GnDX92DBuffer(bool isDisplayBuffer = false) : mIsDisplayBuffer(isDisplayBuffer), mpSurface(NULL)
	{};
	virtual ~GnDX92DBuffer(){};

public:
	// 이전에 디바이스에 지정 했던 렌더 타켓이 msCurrentBuffers에 있다면 NULL 시킨다. 
	static void ClearRenderTarget(LPDIRECT3DDEVICE9 pDevice, gtuint numTarget);

	// msCurrentBuffers에 현재 버퍼의 서페이스가 없다면 디바이스에 타켓으로 mpSurface를 지정하고
	// msCurrentBuffers에 저장해둔다.
	bool SetRenderTarget(LPDIRECT3DDEVICE9 pDevice, gtuint numTarget);	
	
	// 렌더링이 가능한 버퍼인지를 확인.
	inline bool CanDisplay() { return mIsDisplayBuffer; }

	virtual void Release();	
};

#endif // GNDX92DBUFFER_H