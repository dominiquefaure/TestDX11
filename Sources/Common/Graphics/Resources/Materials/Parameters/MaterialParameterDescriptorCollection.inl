
//-------------------------------------------------------------------------------------------------
FORCE_INLINE const std::string& MaterialParameterDescriptorCollection::GetName()const
{
	return m_name;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE TBool MaterialParameterDescriptorCollection::IsGlobalCB()const
{
	return m_isglobal;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE TUint32 MaterialParameterDescriptorCollection::GetParameterCount()const
{
	return m_paramList.size();
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE const MaterialParameterDescriptor* MaterialParameterDescriptorCollection::GetParameterAt( TUint32 a_index )const
{
	assert( a_index < m_paramList.size() );
	return m_paramList[ a_index ];
}
//-------------------------------------------------------------------------------------------------
