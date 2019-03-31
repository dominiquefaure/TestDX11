#include "GraphicDeviceDX11.h"
#include "SwapchainDX11.h"

#include "../../../Core/CoreIncludes.h"

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
	InitTextureFormatArray();

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
	
	// Init the different Internal managers
	InitManagers( );

	// Setup correctly the Main Context, need to be done after all managers have been created
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
void GraphicDeviceDX11::InitManagers( )
{
	// init the State objects
	m_stateObjectsManager.Init( m_d3dDevice );

	m_samplerStateManager.Init( m_d3dDevice );
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


//////////////
// Textures Methods
/////////////

//-------------------------------------------------------------------------------------------------
void GraphicDeviceDX11::InitTextureFormatArray()
{
	m_textureFormat[ TEXTURE_FORMAT_R8G8B8A8 ].m_DXFormat			=	DXGI_FORMAT_R8G8B8A8_UNORM;
	m_textureFormat[ TEXTURE_FORMAT_R8G8B8A8 ].m_blockWidth			=	1;
	m_textureFormat[ TEXTURE_FORMAT_R8G8B8A8 ].m_blockHeight		=	1;
	m_textureFormat[ TEXTURE_FORMAT_R8G8B8A8 ].m_blockSize			=	4;

	m_textureFormat[ TEXTURE_FORMAT_B8G8R8A8 ].m_DXFormat			=	DXGI_FORMAT_B8G8R8A8_UNORM;
	m_textureFormat[ TEXTURE_FORMAT_B8G8R8A8 ].m_blockWidth			=	1;
	m_textureFormat[ TEXTURE_FORMAT_B8G8R8A8 ].m_blockHeight		=	1;
	m_textureFormat[ TEXTURE_FORMAT_B8G8R8A8 ].m_blockSize			=	4;

	m_textureFormat[ TEXTURE_FORMAT_DEPTH_STENCIL ].m_DXFormat		=	DXGI_FORMAT_D24_UNORM_S8_UINT;
	m_textureFormat[ TEXTURE_FORMAT_DEPTH_STENCIL ].m_blockWidth	=	1;
	m_textureFormat[ TEXTURE_FORMAT_DEPTH_STENCIL ].m_blockHeight	=	1;
	m_textureFormat[ TEXTURE_FORMAT_DEPTH_STENCIL ].m_blockSize		=	4;

	m_textureFormat[ TEXTURE_FORMAT_DXT1 ].m_DXFormat				=	DXGI_FORMAT_BC1_UNORM;
	m_textureFormat[ TEXTURE_FORMAT_DXT1 ].m_blockWidth				=	4;
	m_textureFormat[ TEXTURE_FORMAT_DXT1 ].m_blockHeight			=	4;
	m_textureFormat[ TEXTURE_FORMAT_DXT1 ].m_blockSize				=	8;

}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
Texture2DDX11* GraphicDeviceDX11::CreateTexture2D( const RhiTextureDescriptor& a_descriptor, const TUint8* a_data  )
{
	D3D11_TEXTURE2D_DESC t_desc;
	ZeroMemory( &t_desc , sizeof(D3D11_TEXTURE2D_DESC ) );

	SetTextureDescriptor( t_desc , a_descriptor );

	ID3D11Texture2D* t_dxTexture;
	HRESULT t_result;

	D3D11_SUBRESOURCE_DATA* t_subResources					=	BuildSubResourceData( a_descriptor , a_data );
	t_result												=	m_d3dDevice->CreateTexture2D( &t_desc , t_subResources , &t_dxTexture );

	// Free the resources
//	SAFE_DELETE_ARRAY( t_subResources );

	// if succeed
	if( t_result == S_OK )
	{
		// Create a new Texture2D
		Texture2DDX11* t_texture							=	new Texture2DDX11();

		//set it's data
		t_texture->Init( this , a_descriptor , t_dxTexture );

		// return it
		return t_texture;
	}

	return NULL;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void GraphicDeviceDX11::SetTextureDescriptor(  D3D11_TEXTURE2D_DESC& a_dxDescriptor , const RhiTextureDescriptor& a_descriptor )
{
	a_dxDescriptor.Width									=	a_descriptor.m_width;
	a_dxDescriptor.Height									=	a_descriptor.m_height;
	a_dxDescriptor.MipLevels								=	a_descriptor.m_mipmapCount;
	a_dxDescriptor.ArraySize								=	1;
	a_dxDescriptor.SampleDesc.Count							=	1;
	a_dxDescriptor.SampleDesc.Quality						=	0;
	a_dxDescriptor.Format									=	m_textureFormat[ a_descriptor.m_format ].m_DXFormat;
	a_dxDescriptor.BindFlags								=	m_BufferBindFlags[ a_descriptor.m_shaderUsage ];

	a_dxDescriptor.Usage									=	m_bufferUsages[ a_descriptor.m_usage ].Usage;
	a_dxDescriptor.CPUAccessFlags							=	m_bufferUsages[ a_descriptor.m_usage ].CpuAccessFlag;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
D3D11_SUBRESOURCE_DATA* GraphicDeviceDX11::BuildSubResourceData( const RhiTextureDescriptor& a_descriptor, const TUint8* a_data )
{
	if( a_data != NULL )
	{
		TUint32 t_width										=	a_descriptor.m_width;
		TUint32 t_height									=	a_descriptor.m_height;
		TUint32 t_mipCount									=	a_descriptor.m_mipmapCount;
		TextureFormat* t_format								=	&m_textureFormat[ a_descriptor.m_format ];

		// Set the Resource descriptor
		D3D11_SUBRESOURCE_DATA* t_resourceData				=	new D3D11_SUBRESOURCE_DATA[ t_mipCount ];
		
		TUint32 t_offset									=	0;

		for( int i = 0 ; i <t_mipCount ; i ++ )
		{
			TUint32 t_numBlockX								=	max( 1 , ( t_width >> i ) / t_format->m_blockWidth );
			TUint32 t_numBlockY								=	max( 1 , ( t_height >> i ) / t_format->m_blockHeight );

			TUint32 t_rowPitch								=	t_numBlockX * t_format->m_blockSize;
			TUint32 t_slicePitch							=	t_numBlockY * t_rowPitch;

			// set the data to full the buffer with
			t_resourceData[i].pSysMem						=	&a_data[ t_offset ];
			t_resourceData[i].SysMemPitch					=	t_rowPitch;
			t_resourceData[i].SysMemSlicePitch				=	t_slicePitch;
		
			t_offset										+=	t_slicePitch;
		}

		return t_resourceData;
	}

	return NULL;
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
ID3D11ShaderResourceView* GraphicDeviceDX11::CreateShaderResourceView( ID3D11Texture2D* a_texture , RhiTextureFormat a_format , TUint32 a_mipCount , TUint32 a_mostDetailedMip )
{
	ID3D11ShaderResourceView* t_view						=	NULL;


	D3D11_SHADER_RESOURCE_VIEW_DESC t_desc;
	ZeroMemory( &t_desc , sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC) );

	t_desc.Format											=	m_textureFormat[ a_format ].m_DXFormat;
	t_desc.ViewDimension									=	D3D_SRV_DIMENSION_TEXTURE2D;
	t_desc.Texture2D.MostDetailedMip						=	a_mostDetailedMip;
	t_desc.Texture2D.MipLevels								=	a_mipCount;

	HRESULT t_result										=	m_d3dDevice->CreateShaderResourceView( a_texture, &t_desc , &t_view );

	return t_view;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
SamplerStateDX11* GraphicDeviceDX11::CreateSamplerState( const RhiSamplerStateDescriptor& a_descriptor )
{
	return m_samplerStateManager.CreateSamplerState( a_descriptor );
}
//-------------------------------------------------------------------------------------------------
