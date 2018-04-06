

//------------------------------------------------------------------
FORCE_INLINE const D3D11_VIEWPORT* SwapchainDX11::GetViewport()const
{
	return &m_viewport;
}
//------------------------------------------------------------------

//------------------------------------------------------------------
FORCE_INLINE ID3D11RenderTargetView* SwapchainDX11::GetRenderTargetView()
{
	return m_renderTargetView;
}
//------------------------------------------------------------------

