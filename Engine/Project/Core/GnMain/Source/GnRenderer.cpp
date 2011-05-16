#include "GnMainPCH.h"
#include "GnRenderer.h"

GnRenderer* GnRenderer::mpRenderer = NULL;

GnRenderer::GnRenderer() : mpDefaultRenderTarget(NULL), mpCurrentRenderTarget(NULL)
{
	mBackgroundColor.b = 1.0f;
}

GnRenderer::~GnRenderer()
{
}

GnRenderer* GnRenderer::GetRenderer()
{
	return mpRenderer;
}



void GnRenderer::BeginFrame()
{
	DoBeginFrame();	
}

void GnRenderer::EndFrame()
{
	DoEndFrame();
}

void GnRenderer::RenderFrame()
{
	DoRenderFrame();
}

void GnRenderer::BeginRenderTarget(GnRenderTarget* pRenderTarget, gtuint clearFlags)
{
	mpCurrentRenderTarget = pRenderTarget;
	if( mpCurrentRenderTarget )
		DoBeginRenderTarget(clearFlags);
}

void GnRenderer::BeginDefaultRenderTarget(gtuint clearFlags)
{
	BeginRenderTarget(mpDefaultRenderTarget, clearFlags);
}

void GnRenderer::EndRenderTarget()
{
	if( mpCurrentRenderTarget )
		DoEndRenderTarget();
	mpCurrentRenderTarget = NULL;
}

void GnRenderer::ClearBuffer(gtuint clearFlags)
{
	DoClearBuffer(clearFlags);
}

void GnRenderer::RenderScreenMesh(GnRenderObject* pMesh)
{
	DoRenderScreenMesh( (GnScreenMesh*)pMesh );
}