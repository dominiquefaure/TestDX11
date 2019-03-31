
#include "SamplerStateManagerDX11.h"

#include <d3d11.h>

//-------------------------------------------------------------------------------------------------
SamplerStateManagerDX11::SamplerStateManagerDX11( )
{
	m_d3dDevice												=	nullptr;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
SamplerStateManagerDX11::~SamplerStateManagerDX11()
{
	m_d3dDevice												=	nullptr;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void SamplerStateManagerDX11::Init( ID3D11Device* a_device )
{
	m_d3dDevice												=	a_device;
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
SamplerStateDX11* SamplerStateManagerDX11::CreateSamplerState( const RhiSamplerStateDescriptor& a_descriptor )
{
	// setup the descriptor
	D3D11_SAMPLER_DESC t_desc;
	SetupSamplerDesc( a_descriptor , t_desc );

	// Create the Sampler State
    ID3D11SamplerState* t_sampler                            =    NULL;
    m_d3dDevice->CreateSamplerState( &t_desc ,  &t_sampler);


	SamplerStateDX11* t_samplerState						=	new SamplerStateDX11();

	return t_samplerState;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void SamplerStateManagerDX11::SetupSamplerDesc( const RhiSamplerStateDescriptor& a_descriptor , D3D11_SAMPLER_DESC& a_desc )
{
	ZeroMemory(&a_desc,sizeof(D3D11_SAMPLER_DESC));

	a_desc.AddressU											=	GetAddressMode( a_descriptor.m_addressU );
	a_desc.AddressV											=	GetAddressMode( a_descriptor.m_addressV );
	a_desc.AddressW											=	GetAddressMode( a_descriptor.m_addressW );

	// todo, add parameters clamp
	TUint32 t_maxAnisotropy									=	a_desc.MaxAnisotropy;

	// are we using a comparison function?
	TBool t_useComparison									=	( a_descriptor.m_comparisonFunc != RHI_SAMPLER_COMPARISON_FUNC_NEVER );


	a_desc.MipLODBias										=	a_desc.MipLODBias;
	a_desc.MaxAnisotropy									=	t_maxAnisotropy;
	a_desc.MinLOD											=	a_desc.MinLOD;
	a_desc.MaxLOD											=	a_desc.MaxLOD;

	a_desc.Filter											=	GetFilter( a_descriptor.m_filter , t_maxAnisotropy , t_useComparison );
	a_desc.ComparisonFunc									=	GetComparisonFunction( a_descriptor.m_comparisonFunc );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
D3D11_FILTER SamplerStateManagerDX11::GetFilter( const RhiSamplerFilter& a_filter , TUint32 a_maxAnisotropy , TBool a_useComparison )
{
	switch( a_filter )
	{
		case RHI_SAMPLER_FILTER_POINT:
			if( a_useComparison )
			{
				return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
			}
			return D3D11_FILTER_MIN_MAG_MIP_POINT;
		break;

		case RHI_SAMPLER_FILTER_BILINEAR:
			if( a_useComparison )
			{
				return D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
			}
			return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		break;

		case RHI_SAMPLER_FILTER_TRILINEAR:
			if( a_useComparison )
			{
				return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
			}
			return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		break;

		case RHI_SAMPLER_FILTER_ANISOTROPIC_POINT:
			if( a_maxAnisotropy == 1 )
			{
				if( a_useComparison )
				{
					return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
				}
				return D3D11_FILTER_MIN_MAG_MIP_POINT;
			}
			else
			{
				// D3D11 doesn't allow using point filtering for mip filter when using anisotropic filtering
				if( a_useComparison )
				{
					return D3D11_FILTER_COMPARISON_ANISOTROPIC;
				}
				return D3D11_FILTER_ANISOTROPIC;
			}
			break;

		case RHI_SAMPLER_FILTER_ANISOTROPIC_LINEAR:
			if( a_maxAnisotropy == 1 )
			{
				if( a_useComparison )
				{
					return D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
				}
				return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			}
			else
			{
				if( a_useComparison )
				{
					return D3D11_FILTER_COMPARISON_ANISOTROPIC;
				}
				return D3D11_FILTER_ANISOTROPIC;
			}
		break;

	}
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
D3D11_TEXTURE_ADDRESS_MODE SamplerStateManagerDX11::GetAddressMode( const RhiSamplerAdressMode a_mode )
{
	switch( a_mode )
	{
		case RHI_SAMPLER_MODE_CLAMP:
			return D3D11_TEXTURE_ADDRESS_CLAMP;
		case RHI_SAMPLER_MODE_MIRROR: 
			return D3D11_TEXTURE_ADDRESS_MIRROR;
		case RHI_SAMPLER_MODE_BORDER: 
			return D3D11_TEXTURE_ADDRESS_BORDER;
		default: 
			return D3D11_TEXTURE_ADDRESS_WRAP;
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
D3D11_COMPARISON_FUNC SamplerStateManagerDX11::GetComparisonFunction( const RhiSamplerComparisonFunction a_comp )
{
	switch( a_comp )
	{
		case RHI_SAMPLER_COMPARISON_FUNC_LESS :
			return D3D11_COMPARISON_LESS;

		default:
			return D3D11_COMPARISON_NEVER;
	}
}
//-------------------------------------------------------------------------------------------------
