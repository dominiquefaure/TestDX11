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

class VertexShaderDX11;
class PixelShaderDX11;
class ShaderByteCodeDX11;
class VertexLayoutDX11;

class ConstantBufferDX11;

typedef GraphicDeviceDX11	RhiGraphicDevice;
typedef GraphicContextDX11	RhiGraphicContext;
typedef SwapchainDX11		RhiSwapchain;

typedef VertexBufferDX11	RhiVertexBuffer;
typedef IndexBufferDX11		RhiIndexBuffer;

typedef VertexLayoutDX11	RhiVertexLayout;
typedef VertexShaderDX11	RhiVertexShader;
typedef PixelShaderDX11		RhiPixelShader;
typedef ShaderByteCodeDX11	RhiShaderByteCode;

typedef ConstantBufferDX11	RhiConstantBuffer;

#include "DirectX11/IncludesDX11.h"

#endif


#endif