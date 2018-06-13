#ifndef __RHI_SWAPCHAIN_DX11_H__
#define __RHI_SWAPCHAIN_DX11_H__


#include <d3d11.h>
#include <d3dcompiler.h>

#include "../../Core/CoreIncludes.h"

class GraphicDeviceDX11;

class SwapchainDX11
{
	friend class GraphicDeviceDX11;

public:

	SwapchainDX11();
	~SwapchainDX11();

	/*
	* Get the Swapchain default Viewport
	*/
	FORCE_INLINE const D3D11_VIEWPORT* GetViewport()const;


	/*
	* Get the Render TargetView
	*/
	FORCE_INLINE ID3D11RenderTargetView* GetRenderTargetView();

	FORCE_INLINE ID3D11DepthStencilView* GetDepthStencilView();

	/*
	* Set the Viewport of the Swapchain
	*/
	void SetViewport( TUint32 x, TUint32 y , TUint32 width , TUint32 height );



	/*
	* Flip the BackBuffers
	*/
	void Flip();


//Methods
private:

	/*
	* Initialize the Swapchain
	*/
	void Init( GraphicDeviceDX11* a_device , HWND a_handle , TBool a_windowed , TUint32 a_width , TUint32 a_height );

	/*
	* Set the Descriptor used to create the Swapcahin on the Device
	*/
	void SetupDescriptor( HWND a_handle , TBool a_windowed , TUint32 a_width , TUint32 a_height );

	/*
	* Create the Render Target representing the Swapchain
	*/
	void CreateRenderTargetView();


	void CreateDepthBuffer(  TUint32 a_width , TUint32 a_height  );


// Fields
private:

	GraphicDeviceDX11*		m_owner;

	// Describe swapchain on D3D
	DXGI_SWAP_CHAIN_DESC	m_swapchainDesc;

	// The DX Swapchain
	IDXGISwapChain*			m_swapchain;

	// RenderTarget view, allowing to bind the SwapChain buffer to the pipeline
	ID3D11RenderTargetView*	m_renderTargetView;

	// The default viewport of the SwapChain
	D3D11_VIEWPORT			m_viewport;


	ID3D11Texture2D*		m_depthTexture;
	ID3D11DepthStencilView* m_depthStencilView;

};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "SwapchainDX11.inl"
#endif

#endif