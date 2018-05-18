
//-------------------------------------------------------------------------------------------------
FORCE_INLINE GraphicContextDX11* GraphicDeviceDX11::GetMainContext()
{
	return m_mainContext;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE SwapchainDX11* GraphicDeviceDX11::GetSwapchain()
{
	return m_swapchain;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE VertexLayoutDX11* GraphicDeviceDX11::GetVertexLayout( RhiVertexLayoutType a_type )
{
	return m_vertexLayoutManager->GetLayout( a_type );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE VertexLayoutDX11* GraphicDeviceDX11::GetVertexLayout( RhiVertexLayoutTypeKey a_key )
{
	return m_vertexLayoutManager->GetLayout( a_key );
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
FORCE_INLINE StateObjectsManagerDX11* GraphicDeviceDX11::GetStateObjetManager()
{
	return &m_stateObjectsManager;
}
//-------------------------------------------------------------------------------------------------
