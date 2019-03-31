#ifndef __GRAPHICS_RHI_SAMPLER_STATE_DX11_H__
#define __GRAPHICS_RHI_SAMPLER_STATE_DX11_H__

#include "../../Common/Includes.h"
#include <d3d11.h>


class SamplerStateDX11
{

public:

	ID3D11SamplerState* GetResource()
	{
		return m_dxSamplerState;
	}

private:
	

	ID3D11SamplerState*	m_dxSamplerState;
};

#endif