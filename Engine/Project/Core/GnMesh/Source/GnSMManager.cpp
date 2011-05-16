#include "GnMeshPCH.h"
#include "GnSMManager.h"

GnSMManager* GnSMManager::mspSingleton = NULL;

GnSMManager::GnSMManager()
{
	GnRenderer* renderer = GnRenderer::GetRenderer();
	ChangeDisplay( renderer->GetDefaultRenderTarget()->GetWidth( 0 )
		, renderer->GetDefaultRenderTarget()->GetHeight( 0 ) );
}

void GnSMManager::Create()
{
	GnAssert( GnRenderer::GetRenderer() );
	if( mspSingleton )
		return;

	mspSingleton = GnNew GnSMManager();
}

void GnSMManager::Destory()
{
	if( mspSingleton )
		GnDelete mspSingleton;
}

GnSMManager* GnSMManager::GetSingleton()
{
	return mspSingleton;
}

void GnSMManager::ChangeDisplay(guint uiWidth, guint uiHeight)
{
	mDisplayWidth = uiWidth;
	mDisplayHeight = uiHeight;
}

bool GnSMManager::ConvertToVertexRect(GnIRect& rectDisplay, GnFRect& outRect)
{
	outRect.left = ( ( 1.0f * rectDisplay.left ) / mDisplayWidth ) - 0.5f;
	outRect.right = ( ( 1.0f * rectDisplay.right ) / mDisplayWidth ) - 0.5f;
	outRect.top = ( ( -1.0f * rectDisplay.top ) / mDisplayHeight ) + 0.5f;
	outRect.bottom = ( ( -1.0f * rectDisplay.bottom ) / mDisplayHeight ) + 0.5f;
	return true;
}