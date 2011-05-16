#include "GnMainPCH.h"
#include "GnRenderViewSet.h"

GnRenderViewSet::GnRenderViewSet() : mClearMode(GnRenderer::CLEAR_NONE)
{
	SetActive(true);
	SetUseRendererBackgroundColor(true);
	SetKeepRendererBackgroundColor(false);
	mBackgroundColor.b = 1.0f;
}

GnRenderViewSet::~GnRenderViewSet()
{
}

void GnRenderViewSet::Render()
{
	GnRenderer* pRenderer = GnRenderer::GetRenderer();
	

	GnRenderTarget* renderTarget = mpsRenderTarget; 
	if( renderTarget == NULL )
		renderTarget = pRenderer->GetDefaultRenderTarget();
	GnAssert(renderTarget);


	GnRenderTarget* currentRenderTarget = pRenderer->GetCurrentRenderTarget();
	if( currentRenderTarget == renderTarget )
	{
		if( mClearMode != GnRenderer::CLEAR_NONE )
		{
			if( GetUseRendererBackgroundColor() )
			{
				pRenderer->ClearBuffer(mClearMode);
			}
			else if( GetKeepRendererBackgroundColor() )
			{
				pRenderer->SetBackgroundColor(mBackgroundColor);
				pRenderer->ClearBuffer(mClearMode);
			}
			else
			{
				GnColorA color;
				pRenderer->GetBackgroundColor(color);
				pRenderer->SetBackgroundColor(mBackgroundColor);
				pRenderer->ClearBuffer(mClearMode);
				pRenderer->SetBackgroundColor(color);
			}
		}

	}
	else
	{
		if( currentRenderTarget )
			pRenderer->EndRenderTarget();

		if( GetUseRendererBackgroundColor() )
		{
			pRenderer->BeginRenderTarget(renderTarget, mClearMode);
		}
		else if( GetKeepRendererBackgroundColor() )
		{
			pRenderer->SetBackgroundColor(mBackgroundColor);
			pRenderer->BeginRenderTarget(renderTarget, mClearMode);
		}
		else
		{
			GnColorA color;
			pRenderer->GetBackgroundColor(color);
			pRenderer->SetBackgroundColor(mBackgroundColor);
			pRenderer->BeginRenderTarget(renderTarget, mClearMode);
			pRenderer->SetBackgroundColor(color);
		}
	}
	pRenderer->SetCamera(NULL);
	RenderView();
}

void GnRenderViewSet::RenderView()
{
	ElementIterator iter = mList.GetIterator();

	GnRenderView* view;
	while( iter.Valid() )
	{
		view = iter.Item();
		if( view && view->GetActive() )
			view->Render();

		iter.Forth();
	}
}

void GnRenderViewSet::Update(float fTime)
{
	ElementIterator iter = mList.GetIterator();
	GnRenderView* view;
	while( iter.Valid() )
	{
		view = iter.Item();
		if( view && view->GetActive() )
		{
			view->Update(fTime);
		}

		iter.Forth();
	}
}