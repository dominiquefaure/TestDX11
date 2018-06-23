

//---------------------------------------------------------------------------------------------------------
FORCE_INLINE TUint8 RhiShaderConstantBufferDesc::GetSlot()const
{
	return m_slotIndex;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
FORCE_INLINE TUint8 RhiShaderConstantBufferDesc::GetParameterCount()const
{
	return m_parameterCount;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
FORCE_INLINE const RhiShaderParameterDesc* RhiShaderConstantBufferDesc::GetParameterDesc( TUint32 a_index )const
{
	assert( a_index < m_parameterCount );

	return &m_parameterList[ a_index ];
}
//---------------------------------------------------------------------------------------------------------
