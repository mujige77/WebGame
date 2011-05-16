#include "GnDirectx9RendererPCH.h"
#include "GnDX92DBuffer.h"


LPDIRECT3DSURFACE9 GnDX92DBuffer::msCurrentBuffers[4] = {NULL, NULL, NULL, NULL};

void GnDX92DBuffer::ClearRenderTarget(LPDIRECT3DDEVICE9 pDevice, gtuint numTarget)
{
	if (numTarget != 0 && msCurrentBuffers[numTarget])
	{
		pDevice->SetRenderTarget(numTarget, NULL);
		msCurrentBuffers[numTarget] = NULL;
	}
}

bool GnDX92DBuffer::SetRenderTarget(LPDIRECT3DDEVICE9 pDevice, gtuint numTarget)
{
	if (mpSurface != msCurrentBuffers[numTarget])
	{
		// Go ahead and set the render target
		HRESULT hr = pDevice->SetRenderTarget(numTarget, mpSurface);		
		if (FAILED(hr))
		{
			GnLogA("SetRenderTarget %lu", hr);
			return false;
		}
		msCurrentBuffers[numTarget] = mpSurface;
	}
	return true;
}

void GnDX92DBuffer::Release()
{
	GnDxRelease(mpSurface);
}