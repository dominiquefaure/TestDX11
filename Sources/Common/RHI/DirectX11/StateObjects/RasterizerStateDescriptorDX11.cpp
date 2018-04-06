#include "RasterizerStateDescriptorDX11.h"

#ifdef _DEBUG
#include "RasterizerStateDescriptorDX11.inl"
#endif

#define RASTERIZER_STATE_UID_WIREFRAME_SHIFT_COEF	0
#define RASTERIZER_STATE_UID_CULLING_SHIFT_COEF		1

//----------------------------------------------------------------------------------------------------
RasterizerStateDescriptorDX11::RasterizerStateDescriptorDX11()
{
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
RasterizerStateDescriptorDX11::~RasterizerStateDescriptorDX11()
{
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
void RasterizerStateDescriptorDX11::SetDefault()
{
	m_useWireframe											=	false;
	m_cullingMode											=	RHI_CULLING_MODE_NONE;
}
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
TUint64 RasterizerStateDescriptorDX11::GetUID() const
{
	TUint64 t_uid											=	0;

	if( m_useWireframe )
	{
		t_uid												|=	1 << RASTERIZER_STATE_UID_WIREFRAME_SHIFT_COEF;
	}

	// the 2 1st bis are for the culling mode
	t_uid													|=	(int)m_cullingMode << RASTERIZER_STATE_UID_CULLING_SHIFT_COEF;

	// return the computed UID
	return t_uid;
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
void RasterizerStateDescriptorDX11::SetupRasterizerState( D3D11_RASTERIZER_DESC& a_desc )
{
	ZeroMemory( &a_desc , sizeof( a_desc) );

	if( m_useWireframe )
	{
		a_desc.FillMode										=	D3D11_FILL_WIREFRAME;
	}
	else
	{
		a_desc.FillMode										=	D3D11_FILL_SOLID;
	}
	a_desc.CullMode											=	(D3D11_CULL_MODE)m_cullingMode;

	a_desc.FrontCounterClockwise							=	true;
	a_desc.DepthBias										=	0;
	a_desc.DepthBiasClamp									=	0.0f;
	a_desc.SlopeScaledDepthBias								=	false;
	a_desc.DepthClipEnable									=	false;
	a_desc.ScissorEnable									=	false;
	a_desc.MultisampleEnable								=	false;
}
//----------------------------------------------------------------------------------------------------
