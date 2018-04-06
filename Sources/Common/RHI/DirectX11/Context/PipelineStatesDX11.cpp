#include "PipelineStatesDX11.h"

#include "../StateObjects/StateObjectsManagerDX11.h"

#include "../Shaders/Includes.h"

#ifdef _DEBUG
#include "PipelineStatesDX11.inl"
#endif


//----------------------------------------------------------------------------------------------------
PipelineStatesDX11::PipelineStatesDX11()
{
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
PipelineStatesDX11::~PipelineStatesDX11()
{
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
void PipelineStatesDX11::SetStateObjectManager( StateObjectsManagerDX11* a_manager )
{
	m_stateObjectsManager									=	a_manager;
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
void PipelineStatesDX11::Reset()
{
	m_rasterizerStates.SetDefault();
	m_vertexShader											=	NULL;
	m_pixelShader											=	NULL;

	m_lastRasterizerUID										=	0;
	m_dirtyFlags											=	0;	
}
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
void PipelineStatesDX11::SetVertexShader( VertexShaderDX11* a_shader )
{
	if( m_vertexShader != a_shader )
	{
		m_vertexShader										=	a_shader;
		m_dirtyFlags										|=	DIRTY_FLAG_VERTEX_SHADER;
	}
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
void PipelineStatesDX11::SetPixelShader( PixelShaderDX11* a_shader )
{
	if( m_pixelShader != a_shader )
	{
		m_pixelShader										=	a_shader;
		m_dirtyFlags										|=	DIRTY_FLAG_PIXEL_SHADER;
	}

}
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
void PipelineStatesDX11::Commit( ID3D11DeviceContext* a_context )
{
	// Get the Current State UID
	TUint64 t_uid											=	m_rasterizerStates.GetUID();

	// if the UID have changed
	if( t_uid != m_lastRasterizerUID )
	{
		// get the Rasterizer State
		ID3D11RasterizerState* t_state						=	m_stateObjectsManager->GetRasterizerState( t_uid );
	
		// if no matching state, create a new one
		if( t_state == NULL )
		{
			// Generate the correct decriptor
			D3D11_RASTERIZER_DESC t_desc;
			m_rasterizerStates.SetupRasterizerState( t_desc );

			// create the RsterizerState
			t_state											=	m_stateObjectsManager->CreateRasterizerState( t_uid , t_desc );
		}

		// Set the Rasterizer state to the Context
		a_context->RSSetState( t_state );

		// save the new UID
		m_lastRasterizerUID									=	t_uid;
	}

	if( ( m_dirtyFlags & DIRTY_FLAG_VERTEX_SHADER ) == DIRTY_FLAG_VERTEX_SHADER )
	{
		a_context->VSSetShader( m_vertexShader->GetShader() , 0, 0 );
	}

	if( ( m_dirtyFlags & DIRTY_FLAG_PIXEL_SHADER ) == DIRTY_FLAG_PIXEL_SHADER )
	{
		a_context->PSSetShader( m_pixelShader->GetShader() , 0, 0 );
	}

	// reset the dirty flag
	m_dirtyFlags											=	0;
}
//----------------------------------------------------------------------------------------------------
