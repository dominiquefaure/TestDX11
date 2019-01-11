
//----------------------------------------------------------------------------------------------------
FORCE_INLINE const VertexLayoutDX11* PipelineStatesDX11::GetVertexLayout()const
{
	return m_vertexLayout;	
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
FORCE_INLINE void PipelineStatesDX11::SetWireframe( TBool a_flag )
{
	m_rasterizerStates.SetWireframe( a_flag );
}
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
FORCE_INLINE void PipelineStatesDX11::SetCullingMode( RhiCullingMode a_mode )
{
	m_rasterizerStates.SetCullingMode( a_mode );
}
//----------------------------------------------------------------------------------------------------

