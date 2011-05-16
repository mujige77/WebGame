#include "GnMainPCH.h"
#include "GnRenderFrame.h"

GnRenderFrame::GnRenderFrame()
{
}

GnRenderFrame::~GnRenderFrame()
{
}

void GnRenderFrame::Draw()
{
	GnRenderer* renderer = GnRenderer::GetRenderer();
	renderer->BeginFrame();

	ElementIterator iter = mList.GetIterator();
	GnRenderViewSet* step;
	while( iter.Valid() )
	{
		step = iter.Item();
		if( step && step->GetActive() )
			step->Render();

		iter.Forth();
	}
	if( mList.GetCount() )
	{
		renderer->EndRenderTarget();
	}

	renderer->EndFrame();
}

void GnRenderFrame::Render()
{
	GnRenderer* renderer = GnRenderer::GetRenderer();
	renderer->RenderFrame();
}

void GnRenderFrame::Update(float fTime)
{
	ElementIterator iter = mList.GetIterator();
	GnRenderViewSet* step;
	while( iter.Valid() )
	{
		step = iter.Item();
		if( step && step->GetActive() )
		{
			step->Update(fTime);
		}
		iter.Forth();
	}
}