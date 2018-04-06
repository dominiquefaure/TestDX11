#ifndef __RHI_VERTEX_SHADER_DX11_H__
#define __RHI_VERTEX_SHADER_DX11_H__


#include <d3d11.h>
#include "BaseShaderDX11.h"

class GraphicDeviceDX11;

class VertexShaderDX11 : public BaseShaderDX11<ID3D11VertexShader>
{
	friend class GraphicDeviceDX11;

protected:

	VertexShaderDX11()
	{
	}
	
	virtual ~VertexShaderDX11()
	{
	}

};


#endif