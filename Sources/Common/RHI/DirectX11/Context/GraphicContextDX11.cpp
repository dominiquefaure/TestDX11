
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

	for( int i = 0 ; i < VS_PARAMETER_SLOT_COUNT ; i ++ )
	{
		m_vsConstantBuffers[ i ]							=	nullptr;
	}

	for( int i = 0 ; i < PS_PARAMETER_SLOT_COUNT ; i ++ )
	{
		m_psConstantBuffers[ i ]							=	nullptr;
	}

}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
GraphicContextDX11::~GraphicContextDX11()
{
	ReleaseConstantBuffers();

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

	InitConstantBuffers( a_owner );

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

	CommitConstantBuffers();
}
//---------------------------------------------------------------------------------------------------------


/////////
// Constant Buffer Methods
/////////



//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::InitConstantBuffers( GraphicDeviceDX11* a_device )
{
	m_vsConstantBuffers[ VS_PARAMETER_SLOT_PER_FRAME ]		=	a_device->CreateConstantBuffer( VS_PER_FRAME_CONSTANT_BUFFER_SIZE );
	m_vsConstantBuffers[ VS_PARAMETER_SLOT_PER_DRAW ]		=	a_device->CreateConstantBuffer( VS_PER_DRAW_CONSTANT_BUFFER_SIZE );

	m_psConstantBuffers[ PS_PARAMETER_SLOT_MATERIAL ]		=	a_device->CreateConstantBuffer( PS_MATERIAL_CONSTANT_BUFFER_SIZE );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::ReleaseConstantBuffers()
{
	// releasee the different VS Constant Bufers
	for( int i = 0 ; i < VS_PARAMETER_SLOT_COUNT ; i ++ )
	{
		SAFE_DELETE( m_vsConstantBuffers[ i ] );
	}

	// releasee the different PS Constant Bufers
	for( int i = 0 ; i < PS_PARAMETER_SLOT_COUNT ; i ++ )
	{
		SAFE_DELETE( m_psConstantBuffers[ i ] );
	}
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
TBool GraphicContextDX11::UpdateConstantBuffer( ID3D11Buffer* a_buffer , void* a_data , TUint32 a_size )
{
	D3D11_MAPPED_SUBRESOURCE t_subresource;

	m_deviceContext->Map( a_buffer , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &t_subresource );

	// if succeed
	if( t_subresource.pData != NULL )
	{
		// copy the Datas
		memcpy( t_subresource.pData , a_data , a_size );

		// unmap it
		m_deviceContext->Unmap( a_buffer , 0 );

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::CommitConstantBuffers( )
{
	for( int i = 0 ; i < VS_PARAMETER_SLOT_COUNT ; i ++ )
	{
		m_vsConstantBuffers[ i ]->Commit( this , RHI_SHADER_TYPE_VERTEX_SHADER , i );
	}

	for( int i = 0 ; i < PS_PARAMETER_SLOT_COUNT ; i ++ )
	{
		m_psConstantBuffers[ i ]->Commit( this , RHI_SHADER_TYPE_PIXEL_SHADER , i );
	}
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetConstantBuffer( RhiShaderType a_type , int a_slot , ID3D11Buffer* a_buffer )
{
	// Bind the Constant buffer to the correct type of Shader
	switch( a_type )
	{
		case RHI_SHADER_TYPE_VERTEX_SHADER:
			m_deviceContext->VSSetConstantBuffers( a_slot , 1 , &a_buffer );
		break;

		case RHI_SHADER_TYPE_PIXEL_SHADER:
			m_deviceContext->PSSetConstantBuffers( a_slot , 1 , &a_buffer );
		break;
	}
}
//---------------------------------------------------------------------------------------------------------





//////
// PS ConstantBuffer Methods
//////

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetVSShaderParameter( VSParameterSlot a_slot , TUint32 a_index , TUint32 a_byteCount , const void* a_value )
{
	m_vsConstantBuffers[ a_slot ]->Update( a_index , a_byteCount , a_value );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetVSShaderParameter( VSParameterSlot a_slot , TUint32 a_index , const Vector3F* a_value )
{
	m_vsConstantBuffers[ a_slot ]->Update( a_index , sizeof( Vector3F) , a_value );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetVSShaderParameter( VSParameterSlot a_slot , TUint32 a_index , const Matrix44* a_value )
{
	m_vsConstantBuffers[ a_slot ]->Update( a_index , sizeof( Matrix44) , a_value );
}
//---------------------------------------------------------------------------------------------------------


//////
// PS ConstantBuffer Methods
//////

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetPSShaderParameter( PSParameterSlot a_slot , TUint32 a_index , TUint32 a_byteCount , const void* a_value )
{
	m_psConstantBuffers[ a_slot ]->Update( a_index , a_byteCount , a_value );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetPSShaderParameter( PSParameterSlot a_slot , TUint32 a_index , const Vector3F* a_value )
{
	m_psConstantBuffers[ a_slot ]->Update( a_index , sizeof( Vector3F) , a_value );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetPSShaderParameter( PSParameterSlot a_slot , TUint32 a_index , const Matrix44* a_value )
{
	m_psConstantBuffers[ a_slot ]->Update( a_index , sizeof( Matrix44) , a_value );
}
//---------------------------------------------------------------------------------------------------------
