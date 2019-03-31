#ifndef __RHI_WRAPPER_H__
#define __RHI_WRAPPER_H__


#define RHI_DIRECTX11

// Wrap DX11 classes to Rhi
#ifdef RHI_DIRECTX11


class GraphicDeviceDX11;
class GraphicContextDX11;
class SwapchainDX11;

class VertexBufferDX11;
class IndexBufferDX11;

class ShaderByteCodeDX11;
class VertexShaderDX11;
class PixelShaderDX11;
class VertexLayoutDX11;

class ConstantBufferDX11;
class Texture2DDX11;
class SamplerStateDX11;

typedef GraphicDeviceDX11	RhiGraphicDevice;
typedef GraphicContextDX11	RhiGraphicContext;
typedef SwapchainDX11		RhiSwapchain;

typedef VertexBufferDX11	RhiVertexBuffer;
typedef IndexBufferDX11		RhiIndexBuffer;
typedef VertexLayoutDX11	RhiVertexLayout;

typedef ShaderByteCodeDX11	RhiShaderByteCode;
typedef VertexShaderDX11	RhiVertexShader;
typedef PixelShaderDX11		RhiPixelShader;


typedef ConstantBufferDX11	RhiConstantBuffer;
typedef Texture2DDX11		RhiTexture2D;
typedef SamplerStateDX11	RhiSamplerState;

#include "DirectX11/IncludesDX11.h"

#endif


#endif