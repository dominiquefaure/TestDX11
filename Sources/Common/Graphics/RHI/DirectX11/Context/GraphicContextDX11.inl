
//----------------------------------------------------------------------------------------------------
FORCE_INLINE void GraphicContextDX11::SetWireframe( TBool a_wireframe )
{
	m_pipelineStates.SetWireframe( a_wireframe );
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE void GraphicContextDX11::SetCullingMode( RhiCullingMode a_mode)
{
	m_pipelineStates.SetCullingMode( a_mode );
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE const VertexLayoutDX11* GraphicContextDX11::GetVertexLayout()const
{
	return m_pipelineStates.GetVertexLayout();
}
//----------------------------------------------------------------------------------------------------
