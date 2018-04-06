#ifndef __RHI_PIXEL_SHADER_DX11_H__
#define __RHI_PIXEL_SHADER_DX11_H__


#include <d3d11.h>
#include "BaseShaderDX11.h"

class GraphicDeviceDX11;

class PixelShaderDX11 : public BaseShaderDX11<ID3D11PixelShader>
{
	friend class GraphicDeviceDX11;

protected:

	PixelShaderDX11()
	{
	}
	
	virtual ~PixelShaderDX11()
	{
	}

};


#endif