
#include "GraphicContextDX11.h"

#include "../SwapChainDX11.h"
#include "../GraphicDeviceDX11.h"

#include "../Shaders/Includes.h"

#include "../VertexLayout/Includes.h"

#ifdef _DEBUG
#include "GraphicContextDX11.inl"
#endif


//---------------------------------------------------------------------------------------------------------
GraphicContextDX11::GraphicContextDX11( )
{
	m_deviceContext											=	NULL;
	m_swapchain												=	NULL;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
GraphicContextDX11::~GraphicContextDX11()
{
	SAFE_RELEASE( m_deviceContext );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetSwapchain( SwapchainDX11* a_swapchain )
{
	m_swapchain												=	a_swapchain;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::Init( GraphicDeviceDX11* a_owner ,  ID3D11DeviceContext* a_context  )
{
	m_owner													=	a_owner;
	m_deviceContext											=	a_context;
	
	m_pipelineStates.SetStateObjectManager( a_owner->GetStateObjetManager() );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::OnBeginFrame()
{
	// Get the Render Target view of the Swapchain
	ID3D11RenderTargetView* t_renderTargetView				=	m_swapchain->GetRenderTargetView();

	//Set the Render Target
	m_deviceContext->OMSetRenderTargets(1, &t_renderTargetView, nullptr);
	m_deviceContext->RSSetViewports( 1 , m_swapchain->GetViewport() );

	ResetStates();
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::Flush()
{
	m_deviceContext->Flush();
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::Clear( TFloat32 r , TFloat32 g, TFloat32 b )
{
	float t_clearColor[ 4 ];
	
	t_clearColor[ 0 ]										=	r;
	t_clearColor[ 1 ]										=	g;
	t_clearColor[ 2 ]										=	b;
	t_clearColor[ 3 ]										=	1.0f;

	ID3D11RenderTargetView* t_renderTargetView				=	m_swapchain->GetRenderTargetView();
	m_deviceContext->ClearRenderTargetView( t_renderTargetView , t_clearColor );
}
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetVertexStream( int a_index , VertexBufferDX11* a_streamBuffer , TUint32 a_startOffset )
{
	m_geometryStates.SetVertexStream( a_index , a_streamBuffer->GetBuffer() , a_streamBuffer->GetStride() , a_startOffset );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetIndexBuffer( IndexBufferDX11* a_indexBuffer , TUint32 a_startOffset )
{
	if( a_indexBuffer != NULL )
	{
		m_geometryStates.SetIndexBuffer( a_indexBuffer->GetBuffer() , a_indexBuffer->GetDxFormat() , a_startOffset );
	}
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetPrimitiveType( RhiPrimitiveType a_type )
{
	m_geometryStates.SetPrimitiveType( a_type );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetVertexShader( VertexShaderDX11* a_shader )
{
	m_pipelineStates.SetVertexShader( a_shader );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetPixelShader( PixelShaderDX11* a_shader )
{
	m_pipelineStates.SetPixelShader( a_shader );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::GraphicContextDX11::SetVertexLayout( VertexLayoutDX11* a_layout )
{
	m_pipelineStates.SetVertexLayout( a_layout );
}
//---------------------------------------------------------------------------------------------------------



//////////
//// Draw Methods
//////////

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::DrawPrimitive( int a_primitiveCount , int a_startIndex )
{

	CommitStates();

	m_deviceContext->Draw( a_primitiveCount, a_startIndex );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::DrawIndexedPrimitive( int a_indexCount , int a_startIndex , int a_startVertex )
{
	CommitStates();

	m_deviceContext->DrawIndexed( a_indexCount , a_startIndex , a_startVertex );

}
//---------------------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::ResetStates()
{
	m_pipelineStates.Reset();
	m_geometryStates.Reset();

}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::CommitStates()
{
	m_pipelineStates.Commit( m_deviceContext );
	m_geometryStates.Commit( m_deviceContext );
}
//---------------------------------------------------------------------------------------------------------


/////////
// Resources Mapping
/////////

//---------------------------------------------------------------------------------------------------------
bool GraphicContextDX11::MapResource( ID3D11Resource* a_resource ,  int a_subResource ,  void*& a_data , int& a_rowPitch , int& a_depthPitch , D3D11_MAP a_mapType , D3D11_MAP_FLAG a_flag  )
{
	D3D11_MAPPED_SUBRESOURCE t_subresource;

	m_deviceContext->Map( a_resource , a_subResource , a_mapType , a_flag , &t_subresource );

	a_data													=	t_subresource.pData;
	a_rowPitch												=	t_subresource.RowPitch;
	a_depthPitch											=	t_subresource.DepthPitch;

	return ( a_data != NULL );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::UnmapResource( ID3D11Resource* a_resource , int a_subResource )
{
	m_deviceContext->Unmap( a_resource , a_subResource );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::BindConstantBuffer( RhiShaderType a_type , int a_slot , const ConstantBufferDX11* a_buffer )
{
	ID3D11Buffer* t_buffer										=	NULL;

	if( a_buffer != NULL )
	{
		t_buffer												=	a_buffer->GetBuffer();
	}

	// Bind the Constant buffer to the correct type of Shader
	switch( a_type )
	{
		case RHI_SHADER_TYPE_VERTEX_SHADER:
			m_deviceContext->VSSetConstantBuffers( a_slot , 1 , &t_buffer );
		break;

		case RHI_SHADER_TYPE_PIXEL_SHADER:
			m_deviceContext->PSSetConstantBuffers( a_slot , 1 , &t_buffer );
		break;
	}

}
//---------------------------------------------------------------------------------------------------------
