#ifndef __RHI_BASE_SHADER_DX11_H__
#define __RHI_BASE_SHADER_DX11_H__

#include "../../../../Core/CoreIncludes.h"

class GraphicDeviceDX11;
class GraphicContextDX11;

template<class T>
class BaseShaderDX11
{
	friend class GraphicDeviceDX11;
	friend class GraphicContextDX11;

public:

	BaseShaderDX11()
	{
	}

	virtual ~BaseShaderDX11()
	{
		SAFE_RELEASE( m_shader );
	}

public:

	T* GetShader()
	{
		return m_shader;
	}


protected:

	T* m_shader;
};


#endif