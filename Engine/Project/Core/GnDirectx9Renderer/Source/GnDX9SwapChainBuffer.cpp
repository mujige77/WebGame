#include "GnDirectx9RendererPCH.h"
#include "GnDX9SwapChainBuffer.h"
#include "GnDirectx9Renderer.h"

GnDX9SwapChainBuffer::GnDX9SwapChainBuffer(void) : GnDX92DBuffer(true), mpSwapChain(NULL)
{
}

GnDX9SwapChainBuffer::~GnDX9SwapChainBuffer(void)
{
	Release();
}

GnDX9SwapChainBuffer* GnDX9SwapChainBuffer::Create(D3DPRESENT_PARAMETERS d3dpp, LPDIRECT3DDEVICE9 pDevice)
{
	LPDIRECT3DSWAPCHAIN9 pSwapChain = NULL;
	LPDIRECT3DSURFACE9 pSurface = NULL;

	if( CreateBufferData(d3dpp, pDevice, pSwapChain, pSurface) == false )
		return NULL;

	GnDX9SwapChainBuffer* pBuffer =  GnNew GnDX9SwapChainBuffer();
	pBuffer->Init(d3dpp, pSwapChain, pSurface);
	return pBuffer;
}

bool GnDX9SwapChainBuffer::ReCreate(D3DPRESENT_PARAMETERS d3dpp, LPDIRECT3DDEVICE9 pDevice)
{
	Release();

	LPDIRECT3DSWAPCHAIN9 pSwapChain = NULL;
	LPDIRECT3DSURFACE9 pSurface = NULL;

	if( CreateBufferData(d3dpp, pDevice, pSwapChain, pSurface) == false )
		return false;

	Init(d3dpp, pSwapChain, pSurface);
	return true;
}

void GnDX9SwapChainBuffer::Init(D3DPRESENT_PARAMETERS d3dpp, LPDIRECT3DSWAPCHAIN9 pSwapChain,
	LPDIRECT3DSURFACE9 pSurface)
{
	SetWidth(d3dpp.BackBufferWidth);
	SetHeight(d3dpp.BackBufferHeight);
	mpSurface = pSurface;
	mpSwapChain = pSwapChain;
}

void GnDX9SwapChainBuffer::Release()
{
	GnDX92DBuffer::Release();
	GnDxRelease(mpSwapChain);		
}

bool GnDX9SwapChainBuffer::Display()
{
	HRESULT ret = mpSwapChain->Present(NULL, NULL, NULL, NULL, 0);	
	return SUCCEEDED(ret);
}

bool GnDX9SwapChainBuffer::CreateBufferData(D3DPRESENT_PARAMETERS d3dpp, LPDIRECT3DDEVICE9 pDevice,
	LPDIRECT3DSWAPCHAIN9& pSwapChain, LPDIRECT3DSURFACE9& pSurface)
{
	HRESULT hr = S_OK;
	if ( FAILED(hr = pDevice->CreateAdditionalSwapChain(&d3dpp, &pSwapChain)) )
		return false;

	if ( FAILED(pSwapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pSurface)) )
	{
		GnDxRelease(pSwapChain);
		return false;
	}

	return true;
}