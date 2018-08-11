
//-------------------------------------------------------------------------------------------------
FORCE_INLINE BaseMaterialParameter::ParameterType BaseMaterialParameter::GetType()const
{
	return m_type;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE const std::string& BaseMaterialParameter::GetName()const
{
	return m_name;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE TUint16 BaseMaterialParameter::GetStartOffset()const
{
	return m_startOffset;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FORCE_INLINE TUint16 BaseMaterialParameter::Getbytecount()const
{
	return m_byteCount;
}
//-------------------------------------------------------------------------------------------------