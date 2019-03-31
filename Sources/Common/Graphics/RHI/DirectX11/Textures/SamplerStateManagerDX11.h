#ifndef __RHI_SANPLER_STATE_MANAGER_DX11_H__
#define __RHI_SANPLER_STATE_MANAGER_DX11_H__

#include <d3d11.h>

#include "../../Common/Textures/Includes.h"

#include "SamplerStateDX11.h"

class GraphicDeviceDX11;

class SamplerStateManagerDX11
{

	friend class GraphicDeviceDX11;

private:

	SamplerStateManagerDX11( );
	~SamplerStateManagerDX11();

	/*
	* Set the Device
	*/
	void Init( ID3D11Device* a_device );


	/*
	* Create a Sampler State
	*/
	SamplerStateDX11* CreateSamplerState( const RhiSamplerStateDescriptor& a_descriptor );

// Methods
private:

	/*
	* Setup correctly a DX11 Sampler State Descriptor
	*/
	void SetupSamplerDesc( const RhiSamplerStateDescriptor& a_descriptor , D3D11_SAMPLER_DESC& a_desc );

	D3D11_FILTER GetFilter( const RhiSamplerFilter& a_filter , TUint32 a_maxAnisotropy , TBool a_useComparison );

	D3D11_TEXTURE_ADDRESS_MODE GetAddressMode( const RhiSamplerAdressMode a_mode );

	D3D11_COMPARISON_FUNC GetComparisonFunction( const RhiSamplerComparisonFunction a_comp );

// Fields
private:

	// The DX Device representing the Graphic Card
	ID3D11Device*	m_d3dDevice;

};

#endif