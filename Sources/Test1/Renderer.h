#pragma once

#include "Window.h"
#include <d3d11.h>

class Renderer {
public:
	Renderer(Window& window);

	void BeginFrame();
	void EndFrame();

private:
	void CreateDevice(Window& window);
	void CreateRenderTarget();

	// Device stuff
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_deviceContext = nullptr;

	// Render target
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
};
