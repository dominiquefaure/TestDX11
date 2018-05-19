#include "GraphicDeviceDX11.h"
#include "SwapchainDX11.h"

#include "../../Core/CoreIncludes.h"

#include <assert.h>


#include "VertexLayout/Includes.h"

#ifdef _DEBUG
#include "GraphicDeviceDX11.inl"
#endif


//-------------------------------------------------------------------------------------------------
GraphicDeviceDX11::GraphicDeviceDX11()
{
	m_mainContext											=	NULL;
	m_swapchain												=	NULL;

	InitShaderBindFlagArray();
	InitBufferUsageArray();

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
GraphicDeviceDX11::~GraphicDeviceDX11()
{
	SAFE_DELETE( m_mainContext );
	SAFE_DELETE( m_swapchain );
	SAFE_DELETE( m_vertexLayoutManager );


	SAFE_RELEASE( m_d3dDevice );
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void GraphicDeviceDX11::Init( HWND a_handle , TUint32 a_width , TUint32 a_height )
{
	// Create the Dx Device
	CreateDevice();

	// Create the Swapchain
	CreateSwapchain( a_handle , a_width , a_height );

	// init the State objects
	m_stateObjectsManager.Init( m_d3dDevice );

	// Setup correctly the Main Context
	InitMainContext();

	InitVertexLayouts();
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
bool GraphicDeviceDX11::CreateDevice()
{
	// Support only Hardware mode
	D3D_DRIVER_TYPE t_driverType							=	D3D_DRIVER_TYPE_HARDWARE;

	//Different level of features supported by the API
	D3D_FEATURE_LEVEL t_featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
			
	int t_featureLevelsCount								=	sizeof(t_featureLevels) / sizeof(t_featureLevels[0]);
	int t_creationFlags										=	0;

#ifdef DEBUG_GRAPHICS
	t_creationFlags											|=	D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Try to Create the Device
	D3D11CreateDevice(	NULL,
						t_driverType,
						NULL,
						t_creationFlags,
						t_featureLevels,
						t_featureLevelsCount,
						D3D11_SDK_VERSION,
						&m_d3dDevice,
						&m_selectedFeatureLevel,
						&m_immediateContext);

			
	return m_d3dDevice != NULL;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void GraphicDeviceDX11::CreateSwapchain( HWND a_handle ,  TUint32 a_width , TUint32 a_height )
{
	m_swapchain											=	new SwapchainDX11();

	m_swapchain->Init( this , a_handle , true , a_width , a_height );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
IDXGISwapChain* GraphicDeviceDX11::CreateDxSwapchain(  DXGI_SWAP_CHAIN_DESC& a_descriptor )
{

	IDXGIDevice* t_dxgiDevice							=	NULL;
	IDXGIAdapter* t_dxgiAdapter							=	NULL;
	IDXGIFactory* t_dxgiFactory							=	NULL;

	IDXGISwapChain* t_swapchain							=	NULL;

	// Get the needed COM Objects
	m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&t_dxgiDevice));
	t_dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&t_dxgiAdapter));
	t_dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&t_dxgiFactory));

	// Create the Swapchain
	t_dxgiFactory->CreateSwapChain(m_d3dDevice, &a_descriptor, &t_swapchain );

	// Release the COM Objects
	SAFE_RELEASE( t_dxgiDevice );
	SAFE_RELEASE( t_dxgiAdapter );
	SAFE_RELEASE( t_dxgiFactory );

	
	return t_swapchain;
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void GraphicDeviceDX11::BeginFrame()
{
	m_mainContext->OnBeginFrame();

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void GraphicDeviceDX11::EndFrame()
{
	m_mainContext->Flush();

	// Flip the Back buffers
	m_swapchain->Flip();
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void GraphicDeviceDX11::InitMainContext()
{
	// setup the Main Context
	m_mainContext											=	new GraphicContextDX11( );

	m_mainContext->Init( this, m_immediateContext );

	//set the swapchain to use
	m_mainContext->SetSwapchain( m_swapchain );
}
//-------------------------------------------------------------------------------------------------





//////////////
//Init Arrays used to perform conversion between Framework format and DX format
/////////////


//-------------------------------------------------------------------------------------------------
void GraphicDeviceDX11::InitShaderBindFlagArray( )
{
	m_BufferBindFlags[ RHI_RESOURCE_BIND_VERTEX_BUFFER ]	=	D3D11_BIND_VERTEX_BUFFER;
	m_BufferBindFlags[ RHI_RESOURCE_BIND_INDEX_BUFFER ]		=	D3D11_BIND_INDEX_BUFFER;
	m_BufferBindFlags[ RHI_RESOURCE_BIND_CONSTANT_BUFFER ]	=	D3D11_BIND_CONSTANT_BUFFER;
	m_BufferBindFlags[ RHI_RESOURCE_BIND_RESOURCE_READ ]	=	D3D11_BIND_SHADER_RESOURCE;
	m_BufferBindFlags[ RHI_RESOURCE_BIND_RENDER_TARGET ]	=	D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void GraphicDeviceDX11::InitBufferUsageArray()
{
	m_bufferUsages[ RHI_BUFFER_USAGE_IMMUTABLE  ].Usage			=	D3D11_USAGE_IMMUTABLE;
	m_bufferUsages[ RHI_BUFFER_USAGE_IMMUTABLE  ].CpuAccessFlag	=	0;

	m_bufferUsages[ RHI_BUFFER_USAGE_STATIC  ].Usage			=	D3D11_USAGE_DEFAULT;
	m_bufferUsages[ RHI_BUFFER_USAGE_STATIC  ].CpuAccessFlag	=	0;

	m_bufferUsages[ RHI_BUFFER_USAGE_DYNAMIC  ].Usage			=	D3D11_USAGE_DYNAMIC;
	m_bufferUsages[ RHI_BUFFER_USAGE_DYNAMIC  ].CpuAccessFlag	=	D3D11_CPU_ACCESS_WRITE;

}
//-------------------------------------------------------------------------------------------------


//////////////
// Buffers Methods
/////////////

//-------------------------------------------------------------------------------------------------
ID3D11Buffer* GraphicDeviceDX11::CreateBuffer( RhiResourceBindType a_bindType, RhiBufferUsage a_usage , TUint32 a_bufferSize , TUint32 a_structuredStrideSize , void* a_initialDatas )
{
	// Setup the Buffer Descriptor
	D3D11_BUFFER_DESC t_descriptor;
	SetBufferDescriptor( t_descriptor , a_bindType , a_usage , a_bufferSize , a_structuredStrideSize );

	ID3D11Buffer* t_buffer									=	NULL;

	// if there is initial data
	if( a_initialDatas )
	{
		// Set the Resource descriptor
		D3D11_SUBRESOURCE_DATA t_resourceData;
		ZeroMemory( &t_resourceData , sizeof(t_resourceData) );

		// set the data to full the buffer with
		t_resourceData.pSysMem								=	a_initialDatas;

		// Create the D3D Buffer
		HRESULT t_result									=	m_d3dDevice->CreateBuffer( &t_descriptor , &t_resourceData , &t_buffer );
	}
	else
	{
		// Create the D3D Buffer
		HRESULT t_result									=	m_d3dDevice->CreateBuffer( &t_descriptor , NULL , &t_buffer );
	}


	//return the buffer created
	return t_buffer;

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void GraphicDeviceDX11::SetBufferDescriptor( D3D11_BUFFER_DESC& a_descriptor , RhiResourceBindType a_bindType, RhiBufferUsage a_usage , TUint32 a_bufferSize , TUint32 a_structuredStrideSize )
{
	ZeroMemory( &a_descriptor , sizeof(a_descriptor) );

	a_descriptor.ByteWidth									=	a_bufferSize;
	a_descriptor.StructureByteStride						=	a_structuredStrideSize;

	a_descriptor.BindFlags									=	m_BufferBindFlags[ a_bindType ];

	a_descriptor.CPUAccessFlags								=	m_bufferUsages[ a_usage ].CpuAccessFlag;
	a_descriptor.Usage										=	m_bufferUsages[ a_usage ].Usage;

}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
VertexBufferDX11* GraphicDeviceDX11::CreateVertexBuffer( RhiBufferUsage a_usage, TUint32 a_size , TUint32 a_vertexStride , void* a_initialDatas )
{
	// Create the Buffer on GPU
	ID3D11Buffer* t_buffer									=	CreateBuffer( RHI_RESOURCE_BIND_VERTEX_BUFFER , a_usage , a_size , 0 , a_initialDatas );

	// Validate that the Buffer has been created
	assert( t_buffer != NULL );

	// Create the Internal VertexBuffer Object
	VertexBufferDX11* t_vertexBuffer						=	new VertexBufferDX11();

	//Initializa it with the cprrect data
	t_vertexBuffer->Init( t_buffer , a_size );

	// Save the Stride info
	t_vertexBuffer->SetStride( a_vertexStride );

	// return the Buffer Created
	return t_vertexBuffer;
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
IndexBufferDX11* GraphicDeviceDX11::CreateIndexBuffer( RhiBufferUsage a_usage , TUint32 a_indexCount , RhiIndexBufferType a_type , void* a_initialDatas )
{
	int t_size												=	a_indexCount;

	if( a_type == INDEX_BUFFER_TYPE_16 )
	{
		t_size												*=	2;
	}
	else
	{
		t_size												*=	4;
	}

	// Create the Buffer on GPU
	ID3D11Buffer* t_buffer									=	CreateBuffer( RHI_RESOURCE_BIND_INDEX_BUFFER , a_usage , t_size , 0 , a_initialDatas );

	assert( t_buffer != NULL );

	// Create the Internal IndexBuffer Object
	IndexBufferDX11* t_indexBuffer							=	new IndexBufferDX11( );

	//Initializa it with the cprrect data
	t_indexBuffer->Init( t_buffer , t_size );

	// Set the IndexBuffer specific properties
	t_indexBuffer->SetProperties( a_type , a_indexCount );

	return t_indexBuffer;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
ConstantBufferDX11* GraphicDeviceDX11::CreateConstantBuffer( int a_size )
{
	// Create the Buffer on GPU
	ID3D11Buffer* t_buffer									=	CreateBuffer( RHI_RESOURCE_BIND_CONSTANT_BUFFER , RHI_BUFFER_USAGE_DYNAMIC , a_size , NULL );

	assert( t_buffer != NULL );

	//Set the Constant Buffer
	ConstantBufferDX11* t_constantBuffer					=	new ConstantBufferDX11();
	t_constantBuffer->Init( t_buffer , a_size );

	// return the ConstantBuffer Created
	return t_constantBuffer;

}
//-------------------------------------------------------------------------------------------------


//////////////
// Shaders Methods
/////////////


//-------------------------------------------------------------------------------------------------
VertexShaderDX11* GraphicDeviceDX11::CreateVertexShader( ShaderByteCodeDX11& a_byteCode )
{
	VertexShaderDX11* t_shader								=	new VertexShaderDX11();

	HRESULT t_result										=	m_d3dDevice->CreateVertexShader( a_byteCode.GetByteCode() , a_byteCode.GetSize() , nullptr , &( t_shader->m_shader ) );
	assert( t_result == S_OK );

	return t_shader;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
PixelShaderDX11* GraphicDeviceDX11::CreatePixelShader( ShaderByteCodeDX11& a_byteCode )
{
	PixelShaderDX11* t_shader								=	new PixelShaderDX11();

	HRESULT t_result										=	m_d3dDevice->CreatePixelShader( a_byteCode.GetByteCode() , a_byteCode.GetSize() , nullptr , &( t_shader->m_shader ) );
	assert( t_result == S_OK );

	return t_shader;
}
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
void GraphicDeviceDX11::InitVertexLayouts()
{
	m_vertexLayoutManager									=	new VertexLayoutManagerDX11();
	m_vertexLayoutManager->Init( this );
}
//-------------------------------------------------------------------------------------------------




//-------------------------------------------------------------------------------------------------
ID3D11InputLayout* GraphicDeviceDX11::CreateInputLayout( D3D11_INPUT_ELEMENT_DESC* a_descriptor , TUint32 a_elementcount , ShaderByteCodeDX11& a_byteCode )
{
	ID3D11InputLayout* t_layout								=	NULL;

	HRESULT t_result										=	m_d3dDevice->CreateInputLayout( a_descriptor,
																								a_elementcount,
																								a_byteCode.GetByteCode(),
																								a_byteCode.GetSize(),
																								&t_layout );
	return t_layout;
}
//-------------------------------------------------------------------------------------------------
