#include "GnMainPCH.h"
#include "GnRenderTarget.h"

GnRenderTarget::GnRenderTarget() : mBackBufferCount(0)
{

}
GnRenderTarget::~GnRenderTarget()
{
}

GnRenderTarget* GnRenderTarget::Create(Gn2DBackBuffer* backBuffers)
{
	GnRenderTarget* renderTarget = GnNew GnRenderTarget();
	renderTarget->AddBackBuffer(backBuffers);
	return renderTarget;
}

void GnRenderTarget::AddBackBuffer(Gn2DBackBuffer* pBackBuffer)
{
	if( mBackBufferCount >= GnRenderer::GetRenderer()->GetMaxSimultaneousRenderTargetBuffer() )
	{
		GnLog(GnText("Warring : Over BackBuffer Count"));
		return;
	}
	mpBackBuffers[mBackBufferCount++] = pBackBuffer;
	
}
