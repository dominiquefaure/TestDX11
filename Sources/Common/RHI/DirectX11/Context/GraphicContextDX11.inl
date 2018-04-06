
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
