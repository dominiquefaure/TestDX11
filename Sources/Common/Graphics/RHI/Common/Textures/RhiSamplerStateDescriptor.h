#ifndef __RHI_SAMPLER_STATE_DESCRIPTOR_H__
#define __RHI_SAMPLER_STATE_DESCRIPTOR_H__

#include "Core/CoreIncludes.h"
#include "RhiTextureEnums.h"


struct RhiSamplerStateDescriptor
{
public:

	RhiSamplerStateDescriptor(	RhiSamplerFilter a_filter,
								RhiSamplerAdressMode a_addressU,
								RhiSamplerAdressMode a_addressV,
								RhiSamplerAdressMode a_addressW,
								TUint32 a_mipBias = 0,
								TUint32 a_maxAnisotropy = 0,
								TUint32 a_minLOD = 0,
								TUint32 a_maxLOD = -1,
								RhiSamplerComparisonFunction	a_comparison = RHI_SAMPLER_COMPARISON_FUNC_NEVER )
	{
	}

// properties
	// Filter to use to sample the Textures
	RhiSamplerFilter				m_filter;
	RhiSamplerComparisonFunction	m_comparisonFunc;

	RhiSamplerAdressMode			m_addressU;
	RhiSamplerAdressMode			m_addressV;
	RhiSamplerAdressMode			m_addressW;

	TUint8							m_maxAnisotropy;

	// use int instead of Float to store the values
	TUint8							m_mipLODBias;
	TUint8							m_minLOD;
	TUint8							m_maxLOD; // if -1 no max
	
};


#endif
