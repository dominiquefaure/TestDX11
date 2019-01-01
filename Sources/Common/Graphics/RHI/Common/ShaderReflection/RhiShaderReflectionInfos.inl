
//---------------------------------------------------------------------------------------------------------
FORCE_INLINE TUint32 RhiShaderReflectionInfos::GetConstantBufferCount( )const
{
	return m_constantBufferCount;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
FORCE_INLINE const RhiShaderConstantBufferDesc* RhiShaderReflectionInfos::GetConstantBufferDesc( TUint32 a_index )const
{
	assert( a_index < m_constantBufferCount );

	return &m_constantBufferList[ a_index];
}
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
FORCE_INLINE RhiShaderConstantBufferDesc* RhiShaderReflectionInfos::GetConstantBufferDesc( TUint32 a_index )
{
	assert( a_index < m_constantBufferCount );

	return &m_constantBufferList[ a_index];
}
//---------------------------------------------------------------------------------------------------------

