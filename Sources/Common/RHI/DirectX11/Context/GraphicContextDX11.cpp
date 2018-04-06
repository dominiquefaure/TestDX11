
#include "GraphicContextDX11.h"

#include "../SwapChainDX11.h"
#include "../GraphicDeviceDX11.h"

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

	ResetSttes();
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
	m_geometryStates.SetIndexBuffer( a_indexBuffer->GetBuffer() , a_indexBuffer->GetDxFormat() , a_startOffset );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GraphicContextDX11::SetPrimitiveType( RhiPrimitiveType a_type )
{
	m_geometryStates.SetPrimitiveType( a_type );
}
//---------------------------------------------------------------------------------------------------------



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
void GraphicContextDX11::ResetSttes()
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
