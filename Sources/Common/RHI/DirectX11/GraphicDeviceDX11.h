#ifndef __RHI_GRAPHIC_DEVICE_DX11_H__
#define __RHI_GRAPHIC_DEVICE_DX11_H__



#include <d3d11.h>
#include <d3dcompiler.h>

#include "../../Core/CoreIncludes.h"

#include "../RhiEnums.h"

#include "Buffers/Includes.h"
#include "Context/GraphicContextDX11.h"

#include "StateObjects/StateObjectsManagerDX11.h"
#include "Shaders/Includes.h"


// Inernal structure to save DX parameters associed to a ShaderUsage enum
struct BufferUsageParams
{
	D3D11_USAGE	Usage;
	UINT		CpuAccessFlag;
};


class VertexLayoutDX11;
class VertexLayoutManagerDX11;

class GraphicDeviceDX11
{
	friend class SwapchainDX11;
	friend class VertexLayoutDX11;

public:

	GraphicDeviceDX11();
	~GraphicDeviceDX11();

	/*
	* Get the Main Graphic Context sued to display on Screen
	*/
	FORCE_INLINE GraphicContextDX11* GetMainContext();

	/*
	* Get the Swap chain
	*/
	FORCE_INLINE SwapchainDX11* GetSwapchain();

	/*
	* Get the Object that store all the create StateObjects
	*/
	FORCE_INLINE StateObjectsManagerDX11* GetStateObjetManager();




	/*
	* Initialize the Device
	*/
	void Init( HWND a_handle , TUint32 a_width , TUint32 a_height );

	/*
	* Called at the Start of a Frame
	*/
	void BeginFrame();

	/*
	* Called at the End of a Frame, submit all the rendering commands to Gpu
	*/
	void EndFrame();


	/*
	* Create a new VertexBuffer
	*
	* @param a_usage		: what will be the usage of this Buffer , generally static
	* @param a_size			: Buffer Size
	* @param a_vertexStride	: number of bytes used by vertex
	* @parm a_initialDatas	: Set initial content, required if the usage is static
	*/
	VertexBufferDX11* CreateVertexBuffer( RhiBufferUsage a_usage, TUint32 a_size , TUint32 a_vertexStride  , void* a_initialDatas = NULL );

	/*
	* Create a new IndexBuffer
	*
	* @param a_usage		: what will be the usage of this Buffer , generally static
	* @param a_indexCount	: Max Number of Index
	* @param a_type			: Format of 1 Index ( 16bits or 32bits )
	* @parm a_initialDatas	: Set initial content, required if the usage is static
	*/
	IndexBufferDX11* CreateIndexBuffer( RhiBufferUsage a_usage , TUint32 a_indexCount , RhiIndexBufferType a_type , void* a_initialDatas = NULL );


	/*
	* Create a Vertex Shader from compiled ByteCode
	*
	* @param a_byteCode :	Object that contain the compiled byte code for the shader
	*/
	VertexShaderDX11* CreateVertexShader( ShaderByteCodeDX11& a_byteCode );

	/*
	* Create a Pixel Shader from compiled ByteCode
	*
	* @param a_byteCode :	Object that contain the compiled byte code for the shader
	*/
	PixelShaderDX11* CreatePixelShader( ShaderByteCodeDX11& a_byteCode );


	/*
	* Get the Vertex Layout matching the given Type
	*/
	FORCE_INLINE VertexLayoutDX11* GetVertexLayout( RhiVertexLayoutType a_type );

	/*
	* Get the Vertex Layout matching the given Key
	*/
	FORCE_INLINE VertexLayoutDX11* GetVertexLayout( RhiVertexLayoutTypeKey a_key );


	/*
	* Create a new Constant Buffer
	*/
	ConstantBufferDX11* CreateConstantBuffer( int a_size );


private:

	/*
	* Create the D3D Device	
	*/
	bool CreateDevice();

	/*
	* Create the Swapchain
	*/
	void CreateSwapchain( HWND a_handle , TUint32 a_width , TUint32 a_height );

	/*
	* Initialize correctly the Main Graphic Context
	*/
	void InitMainContext();

	/*
	* Init the Array used to Convert RhiShaderResourceBinding enum to DX BindFlag 
	*/
	void InitShaderBindFlagArray();

	/*
	* Init the Array that Define the Dx values associed to a RhiBufferUsage
	*/
	void InitBufferUsageArray();

	/*
	* Create all the Vertex Layout supported
	*/
	void InitVertexLayouts();

	/*
	* Create a DX11 Swapchain According to the given Descriptor
	*/
	IDXGISwapChain* CreateDxSwapchain( DXGI_SWAP_CHAIN_DESC& a_descriptor );



	/*
	* Create a ID3D11 Buffer according to the given parameters
	*
	* @param a_bindType				:	The way the Buffer will be binded to the Pipeline
	* @param a_usage				:	Intended usage we will make of the Buffer
	* @param a_bufferSize			:	Size in bytes of the Buffer
	* @param a_structuredStrideSize	:	Size of an Element (size of the structure) for StructuredBuffer
	* @param a_initialDatas			:	Initial data to write to the Buffer
	*/
	ID3D11Buffer* CreateBuffer( RhiResourceBindType a_bindType, RhiBufferUsage a_usage , TUint32 a_bufferSize , TUint32 a_structuredStrideSize , void* a_initialDatas = NULL );

	/*
	* Setup correctly a Buffer Descriptor
	*/
	void SetBufferDescriptor( D3D11_BUFFER_DESC& a_descriptor , RhiResourceBindType a_bindType, RhiBufferUsage a_usage , TUint32 a_bufferSize , TUint32 a_structuredStrideSize = 0 );


	/*
	* Create an input Layout
	*/
	ID3D11InputLayout* CreateInputLayout( D3D11_INPUT_ELEMENT_DESC* a_descriptor , TUint32 a_elementcount , ShaderByteCodeDX11& a_byteCode );

private:

	// The Device representing the Graphic Card
	ID3D11Device*			m_d3dDevice;

	// Context that send commands directly to the Gpu
	ID3D11DeviceContext*	m_immediateContext;

	// DirectX feature available
	D3D_FEATURE_LEVEL		m_selectedFeatureLevel;

	SwapchainDX11*			m_swapchain;

	// the Main context, using the D3D Immediate Context
	GraphicContextDX11*		m_mainContext;


	// store the DX BindFlag associed to a RhiResourceBindType
	UINT					m_BufferBindFlags[ RHI_RESOURCE_BIND_COUNT ];

	// Store the different properties matching a RhiBufferUsage
	BufferUsageParams		m_bufferUsages[ RHI_BUFFER_USAGE_COUNT ];



	VertexLayoutManagerDX11*	m_vertexLayoutManager;

	StateObjectsManagerDX11	m_stateObjectsManager;
};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "GraphicDeviceDX11.inl"
#endif


#endif