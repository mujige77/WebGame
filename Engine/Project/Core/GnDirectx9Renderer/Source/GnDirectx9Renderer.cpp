#include "GnDirectx9RendererPCH.h"
#include "GnDirectx9Renderer.h"
#include "GnDX92DBuffer.h"
#include "GnDX9SwapChainBuffer.h"
#include "GnDX9FactoryManager.h"
#include "GnScreenMesh.h"
#include "GnDX9MeshData.h"
#include "GnDX9DataStream.h"
#include "GnDX9Texture.h"
GnDirectx9Renderer::GnDirectx9Renderer() : mpD3D(NULL), mpDevice(NULL)
{
}

GnDirectx9Renderer::~GnDirectx9Renderer()
{
	Release();
}

GnDirectx9Renderer* GnDirectx9Renderer::Create(guint uiWidth, guint uiHeight, GnWindowHandle hwnd)
{
	mpRenderer = GnNew GnDirectx9Renderer();

	GnDirectx9Renderer* pRenderer = (GnDirectx9Renderer*)mpRenderer;
	if( pRenderer->Init(uiWidth, uiHeight, hwnd) == false )
	{
		GnDelete mpRenderer;	
		return NULL;
	}
	GnDX9FactoryManager::Create();
	return pRenderer;
}

bool GnDirectx9Renderer::Init(guint uiWidth, guint uiHeight, GnWindowHandle hwnd)
{
	/// 디바이스를 생성하기위한 D3D객체 생성
	if( NULL == ( mpD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return false;

	D3DDISPLAYMODE d3ddm;
	if( FAILED( mpD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
		return false;

	CollectDevieceInfo();

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.BackBufferWidth = uiWidth;
	d3dpp.BackBufferHeight = uiHeight;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; 

	DWORD dwVSProcess = ( mD3DCaps9.VertexShaderVersion < D3DVS_VERSION(1,0) ) 
		? D3DCREATE_SOFTWARE_VERTEXPROCESSING : D3DCREATE_HARDWARE_VERTEXPROCESSING;	
	if( FAILED( mpD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, dwVSProcess, &d3dpp, &mpDevice ) ) )
	{
		return false;
	}

	GnDX92DBuffer* defaultBuffer = GnDX9SwapChainBuffer::Create(d3dpp, mpDevice);
	if( defaultBuffer == NULL )
	{
		GnLog(GnText("Failed Create BackBuffer"));
		return false;
	}

	mpDefaultRenderTarget = GnRenderTarget::Create(defaultBuffer);

	SetDynamicLight();
	return true;
}

void GnDirectx9Renderer::CollectDevieceInfo()
{
	mpD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &mD3DCaps9 );
}

GnDirectx9Renderer* GnDirectx9Renderer::GetRenderer()
{
	return (GnDirectx9Renderer*)mpRenderer;
}

void GnDirectx9Renderer::DoBeginFrame()
{	
	if( FAILED(	mpDevice->BeginScene() ) )
	{
		GnAssert(false);
		GnLogA("failed BeginFrame");
		return;
	}
}

void GnDirectx9Renderer::DoEndFrame()
{
	
	if( FAILED( mpDevice->EndScene() ) )
	{
		GnAssert(false);
		GnLogA("failed EndFrame");
		return;
	}
}

void GnDirectx9Renderer::DoRenderFrame()
{
	while( mUseDisplayBuffers.GetCount() )
	{		
		GnListIterator<GnDX92DBuffer*> iter = mUseDisplayBuffers.GetIterator();
		GnDX92DBuffer* buffer = iter.Item();
		buffer->Display();
		mUseDisplayBuffers.Remove(iter);
	}
}

void GnDirectx9Renderer::DoBeginRenderTarget(gtuint clearFlags)
{
	GnDX92DBuffer::ClearRenderTarget(mpDevice, 1);
	GnDX92DBuffer::ClearRenderTarget(mpDevice, 2);
	GnDX92DBuffer::ClearRenderTarget(mpDevice, 3);
	for( gtuint i  = 0 ; i < mpCurrentRenderTarget->GetBufferCount() ; i++ )
	{
		GnDX92DBuffer* buffer =  (GnDX92DBuffer*)mpCurrentRenderTarget->GetBackBuffer(i);
		buffer->SetRenderTarget(mpDevice, i);
	}

	DoClearBuffer(clearFlags);
}

void GnDirectx9Renderer::DoEndRenderTarget()
{
	for ( gtuint i = 0 ; i < mpCurrentRenderTarget->GetBufferCount() ; i++)
	{
		GnDX92DBuffer* buffer =  (GnDX92DBuffer*)mpCurrentRenderTarget->GetBackBuffer(i);
		if( buffer->CanDisplay() )
			mUseDisplayBuffers.Append(buffer);
	}
}


void GnDirectx9Renderer::DoClearBuffer(gtuint clearFlags)
{
	if( clearFlags == CLEAR_NONE )
		return;
	
	if( FAILED( mpDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, mBackgroundColor.GetRGBA(), 1.0f, 0L ) ) )
	{
		GnLogA("Failed DoClearBuffer");
	}
}


void GnDirectx9Renderer::DoRenderScreenMesh(GnScreenMesh* pMesh)
{
	HRESULT hr;

	GnAssert( pMesh && GnIsKindOf(GnDX9MeshData, pMesh->GetMeshData()) );
	GnDX9MeshData* meshData = (GnDX9MeshData*)pMesh->GetMeshData();	
	meshData->Update();

	hr = mpDevice->SetVertexDeclaration( meshData->GetDeclaration() );
	//GnLogA(  "SetVertexDeclaration %d", hr );

	GnDataStreamList& streams =  meshData->GetDataStreams();
	GnListIterator<GnDataStream*> iter = streams.GetIterator();
	while( iter.Valid() )
	{
		GnDX9DataStream* dx9Stream = (GnDX9DataStream*)iter.Item();		
		//HRESULT hr = mpDevice->SetStreamSourceFreq(dx9Stream->GetNumStream(), 1);
		hr = mpDevice->SetStreamSource( dx9Stream->GetNumStream(),
 			dx9Stream->GetVertexBuffer(), 0, dx9Stream->GetStrideSize());
		GnLogA( "Setstream %d %d %d %d", hr, dx9Stream->GetNumStream(), dx9Stream->GetVertexBuffer(), dx9Stream->GetStrideSize() );
		iter.Forth();
	}	

	GnTextureProperty* texProperty = (GnTextureProperty*)pMesh->GetProperty(GnTextureProperty::GetPropertyType());
	if( texProperty )
	{
		GnDX9Texture* tex = (GnDX9Texture*)texProperty->GetTexture(0);
		if( tex )
		{
			GnLogA( "Settexture %s\n", tex->GetTextureFileName() );
			mpDevice->SetTexture(0, tex->GetDX9Texture());
		}
		else
		{
			GnLogA( "Settexture NULL" );
			mpDevice->SetTexture(0, NULL);
		}
	}
	else
	{
		GnLogA( "Settexture NULL NOPROP");
		mpDevice->SetTexture(0, NULL);
	}

	mpDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
	// SRCBLEND 와 DESTBLEND set 
	mpDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	mpDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity( &matWorld );
	//matWorld._41 =  ( ( 1.0f * 0.5f ) / GetCurrentRenderTarget()->GetWidth(0)) + 0.5f;
	mpDevice->SetTransform( D3DTS_WORLD, &matWorld );
	hr = mpDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, pMesh->GetPrimitiveCount(pMesh->GetNumVertex()) );
	GnLogA( "DrawPrimitive %d %d %d" ,hr,  pMesh->GetNumVertex(), pMesh->GetPrimitiveCount(pMesh->GetNumVertex()) );
}

void GnDirectx9Renderer::SetDynamicLight()
{
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	//light.Direction = D3DXVECTOR3( 0.0f, 50.0f, 0.0f );
	ZeroMemory( &light, sizeof(D3DLIGHT9) );
	light.Type       = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r  = 0.5f;
	light.Diffuse.g  = 0.5f;
	light.Diffuse.b  = 0.5f;
	vecDir = D3DXVECTOR3( 0.0f, -1.0f, 0.3f );
	//vecDir =  D3DXVECTOR3( cosf ( timeGetTime()/700.0f ), 1.0f,  sinf( timeGetTime()/700.0f ));
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
	light.Range       = 500.0f;
	mpDevice->SetLight( 0, &light );
	mpDevice->LightEnable( 0, TRUE );
	mpDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// Finally, turn on some ambient light.
	mpDevice->SetRenderState( D3DRS_AMBIENT, 0xffffFFFF);		//환경광 설정	
	mpDevice->SetRenderState( D3DRS_FILLMODE , D3DFILL_SOLID  );
	mpDevice->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );		//그라우드 셰이딩 모드 지정

	mpDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );	 //밉맵필터링 적용
	mpDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR ); //밉맵필터링 적용
}

void GnDirectx9Renderer::SetCamera(GnCamera* cam)
{
	D3DXMATRIXA16 matOrtho;
	D3DXMATRIXA16 matView;
	D3DXMatrixIdentity( &matView );	
	D3DXMatrixOrthoOffCenterLH( &matOrtho, -0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 1.0f );	
	mpDevice->SetTransform( D3DTS_VIEW, &matView );
	mpDevice->SetTransform( D3DTS_PROJECTION, &matOrtho );
}

gtuint GnDirectx9Renderer::GetMaxSimultaneousRenderTargetBuffer()
{
	return mD3DCaps9.NumSimultaneousRTs;
}

void GnDirectx9Renderer::Release()
{
	if( mpDefaultRenderTarget )
		GnDelete mpDefaultRenderTarget;

	GnDxRelease(mpD3D);
	GnDxRelease(mpDevice);
	GnDX9FactoryManager::Destory();
}