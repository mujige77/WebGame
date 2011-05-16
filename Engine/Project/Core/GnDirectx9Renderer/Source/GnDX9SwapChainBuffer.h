#ifndef GNDX9SWAPCHAINBUFFER_H
#define GNDX9SWAPCHAINBUFFER_H

#include "GnDX92DBuffer.h"

class GNDIRECTX9RENDERER_ENTRY GnDX9SwapChainBuffer : public GnDX92DBuffer
{
public:	
	virtual ~GnDX9SwapChainBuffer(void);

	static GnDX9SwapChainBuffer* Create(D3DPRESENT_PARAMETERS d3dpp, LPDIRECT3DDEVICE9 pDevice);
	bool ReCreate(D3DPRESENT_PARAMETERS d3dpp, LPDIRECT3DDEVICE9 pDevice);
	void Init(D3DPRESENT_PARAMETERS d3dpp, LPDIRECT3DSWAPCHAIN9 pSwapChain, LPDIRECT3DSURFACE9 pSurface);
	virtual void Release();
	virtual bool Display();

protected:
	static bool CreateBufferData(D3DPRESENT_PARAMETERS d3dpp, LPDIRECT3DDEVICE9 pDevice,
		LPDIRECT3DSWAPCHAIN9& pSwapChain, LPDIRECT3DSURFACE9& pSurface);

protected:
	GnDX9SwapChainBuffer(void);

protected:
	LPDIRECT3DSWAPCHAIN9			mpSwapChain;
};

#endif // GNDX9SWAPCHAINBUFFER_H