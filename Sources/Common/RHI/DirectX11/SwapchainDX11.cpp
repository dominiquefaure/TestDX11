#include "SwapChainDX11.h"
#include "GraphicDeviceDX11.h"


#ifdef _DEBUG
#include "SwapchainDX11.inl"
#endif


//------------------------------------------------------------------------------
SwapchainDX11::SwapchainDX11()
{
	m_owner													=	NULL;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
SwapchainDX11::~SwapchainDX11()
{
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void SwapchainDX11::Init( GraphicDeviceDX11* a_device , HWND a_handle , TBool a_windowed , TUint32 a_width , TUint32 a_height )
{
	// Save pointer to the Owner Graphic Device
	m_owner													=	a_device;

	// Set the Correct Descriptor
	SetupDescriptor( a_handle , a_windowed , a_width , a_height );

	// Create the Swapchain on Device
	m_swapchain												=	m_owner->CreateDxSwapchain( m_swapchainDesc );

	// Create the RenderTarget View
	CreateRenderTargetView();

	// Set the default Viewport
	SetViewport( 0 , 0 , a_width , a_height );
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void SwapchainDX11::SetupDescriptor( HWND a_handle , TBool a_windowed , TUint32 a_width , TUint32 a_height )
{
	ZeroMemory( &m_swapchainDesc, sizeof( m_swapchainDesc ) );

	m_swapchainDesc.BufferCount								=	2;
	m_swapchainDesc.SwapEffect								=	DXGI_SWAP_EFFECT_DISCARD;

	m_swapchainDesc.BufferDesc.Scaling						=	DXGI_MODE_SCALING_STRETCHED;
	m_swapchainDesc.BufferDesc.ScanlineOrdering				=	DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	m_swapchainDesc.BufferDesc.Format						=	DXGI_FORMAT_R8G8B8A8_UNORM;
	m_swapchainDesc.Flags									=	DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


	m_swapchainDesc.BufferUsage								=	DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_swapchainDesc.SampleDesc.Count						=	1;
	m_swapchainDesc.SampleDesc.Quality						=	0;


	m_swapchainDesc.OutputWindow							=	a_handle;

	if( a_windowed )
	{
		m_swapchainDesc.Windowed							=	true;
		m_swapchainDesc.BufferDesc.Width					=	a_width;
		m_swapchainDesc.BufferDesc.Height					=	a_height;

	}
	else
	{
		// todo
	}

}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------
void SwapchainDX11::CreateRenderTargetView()
{
	// Get the Backbuffer Texture
	ID3D11Texture2D* backBuffer;
	m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**) &backBuffer);

	m_owner->m_d3dDevice->CreateRenderTargetView( backBuffer, nullptr, &m_renderTargetView );

	//release the COM Object
	backBuffer->Release();
	
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
void SwapchainDX11::SetViewport( TUint32 a_x , TUint32 a_y , TUint32 a_width , TUint32 a_height )
{
	ZeroMemory(&m_viewport, sizeof(D3D11_VIEWPORT));

	m_viewport.TopLeftX										=	(FLOAT)a_x;
	m_viewport.TopLeftY										=	(FLOAT)a_y;
	m_viewport.Width										=	(FLOAT)a_width;
	m_viewport.Height										=	(FLOAT)a_height;
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
void SwapchainDX11::Flip()
{
	if( m_swapchain != NULL )
	{
		// Swap the buffer immediatly
		m_swapchain->Present(0, 0);
	}
}
//------------------------------------------------------------------------
