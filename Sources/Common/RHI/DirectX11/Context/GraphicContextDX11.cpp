
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
	m_deviceContext											=	nullptr;
	m_swapchain												=	nullptr;


}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
GraphicContextDX11::~GraphicContextDX11()
{
	SAFE_RELEASE( m_deviceContext );

	m_swapchain												=	nullptr;
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
	ID3D11DepthStencilView* t_depthStenciView				=	m_swapchain->GetDepthStencilView();

	//Set the Render Target
	m_deviceContext->OMSetRenderTargets(1, &t_renderTargetView, t_depthStenciView);
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
	ID3D11DepthStencilView* t_depthStenciView				=	m_swapchain->GetDepthStencilView();

	m_deviceContext->ClearRenderTargetView( t_renderTargetView , t_clearColor );

	m_deviceContext->ClearDepthStencilView( t_depthStenciView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

}
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetVertexStream( TUint32 a_index , VertexBufferDX11* a_streamBuffer , TUint32 a_startOffset )
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
void GraphicContextDX11::DrawPrimitive( TUint32 a_primitiveCount , TUint32 a_startIndex )
{

	CommitStates();

	m_deviceContext->Draw( a_primitiveCount, a_startIndex );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::DrawIndexedPrimitive( TUint32 a_indexCount , TUint32 a_startIndex , TUint32 a_startVertex )
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
// Constant Buffer Methods
/////////

//---------------------------------------------------------------------------------------------------------
TBool GraphicContextDX11::UpdateConstantBuffer( ConstantBufferDX11* a_buffer , const void* a_data , TUint32 a_size )
{
	// Get the GPU Buffer
	ID3D11Buffer* t_buffer									=	a_buffer->m_buffer;


	D3D11_MAPPED_SUBRESOURCE t_subresource;

	m_deviceContext->Map( t_buffer , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &t_subresource );

	// if succeed
	if( t_subresource.pData != NULL )
	{
		// copy the Datas
		memcpy( t_subresource.pData , a_data , a_size );

		// unmap it
		m_deviceContext->Unmap( t_buffer , 0 );

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetConstantBuffer( RhiShaderType a_type , int a_slot , ConstantBufferDX11* a_buffer )
{
	// Get the GPU Buffer
	ID3D11Buffer* t_buffer									=	a_buffer->m_buffer;

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

