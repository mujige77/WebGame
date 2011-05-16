#include "GnToolLibPCH.h"
#include "GnFrame.h"
#include "GnDX9SwapChainBuffer.h"
#include "GnToolManager.h"
#include <GnScreenMesh.h>
#include <GnSMRenderView.h>

GnFrame::GnFrame(GnRenderViewSet* pRenderViewSet, GnRenderView* pRenderView) : mpRenderViewSet(pRenderViewSet),
	mpRenderView(pRenderView)
{
	GnToolManager::AddFrame(this);
}


GnFrame::~GnFrame(void)
{
	GnToolManager::RemoveFrame(this);
}

GnFrame* GnFrame::Create(GnWindowHandle hwnd)
{	
	GnRenderViewSet* renderViewSet = GnNew GnRenderViewSet();
	RECT rect;
	GetClientRect(hwnd, &rect);
	Gn2DBackBuffer* backBuffer = CreateBackBuffer(hwnd, rect.right - rect.left, rect.bottom - rect.top);	
	GnRenderTarget* renderTarget = GnRenderTarget::Create(backBuffer);
	renderViewSet->SetRenderTarget(renderTarget);
	renderViewSet->SetClearMode(GnRenderer::CLEAR_ALL);

	GnRenderView* renderView = GnNew GnSMRenderView();
	renderViewSet->Append(renderView);

	GnFrame* pThis = GnNew GnFrame(renderViewSet, renderView);
	pThis->mWindowHandle = hwnd;

	GnSMManager::GetSingleton()->ChangeDisplay( rect.right - rect.left, rect.bottom - rect.top );
	return pThis;
}

Gn2DBackBuffer* GnFrame::CreateBackBuffer(GnWindowHandle hwnd, int iWidth, int iHeight)
{
	GnDirectx9Renderer* pRnderer = GnDirectx9Renderer::GetRenderer();
	
	D3DDISPLAYMODE d3ddm;
	if( FAILED( pRnderer->GetD3D()->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
		return NULL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.BackBufferWidth = iWidth;
	d3dpp.BackBufferHeight = iHeight;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; 

	return GnDX9SwapChainBuffer::Create( d3dpp, pRnderer->GetDevice() );
}

bool GnFrame::RecreateRenderTarget(int iWidth, int iHeight)
{
	Gn2DBackBuffer* backBuffer = CreateBackBuffer(mWindowHandle, iWidth, iHeight);
	if( backBuffer )
	{
		GnRenderTarget* target = GnRenderTarget::Create(backBuffer);
		if( target )
			mpRenderViewSet->SetRenderTarget( target );			
		else
			GnDelete backBuffer;
	}

	GnSMManager::GetSingleton()->ChangeDisplay( iWidth, iHeight );
	for( gtuint i = 0 ; i < mObjects.GetSize() ; i++ )
	{
		GtObject* pObject = mObjects.GetAt( i );
		if( pObject )
		{
			GnVector2 scale = pObject->GetScale();
			pObject->ChanageScale( (gint32)scale.x, (gint32)scale.y );
		}
	}
	//GnDirectx9Renderer* renderTarget = GnDirectx9Renderer::GetRenderer();
	//renderTarget->set
	return true;
}

void GnFrame::SetTimeCtrl(float ftime, GnTimeController* pTimeCtrl)
{
	//if( mesh )
	//{
	//	pTimeCtrl->SetTargetName("mesh");
	//	pTimeCtrl->SetTargetObject(mesh);
	//	pTimeCtrl->Start(ftime);
	//}
}

void GnFrame::Stop()
{
	//if( mesh )
	//{
	//	GnTimeController* timeCtrl = mesh->GetControllers();
	//	if( timeCtrl )
	//		timeCtrl->Stop();
	//}
}

void GnFrame::AddObject(GtObject* pObject)
{
	mObjects.Add( pObject );
	mpRenderView->Append( pObject->GetRootNode() );
	GnLogA("AddObject %d", pObject->GetRootNode());
}

void GnFrame::RemoveObject(GtObject* val)
{
	if( val == NULL )
		return;
	
	mObjects.Remove( val );
	GnObjectForm* node = val->GetRootNode();

	if( node )
		mpRenderView->Remove( node );

	mpRenderView->RemoveAll();
}

void GnFrame::Update(float fTime)
{
	for( gtuint i = 0 ; i < mObjects.GetSize() ; i++ )
	{
		GtObject* object = mObjects.GetAt( i );
		object->Update( fTime );
	}
}