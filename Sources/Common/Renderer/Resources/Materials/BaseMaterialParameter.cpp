#include "BaseMaterialParameter.h"

//In debug configuration, the inlline methods need to be include inside a cpp file, to avoid function redefinition errors
#ifdef _DEBUG
#include "BaseMaterialParameter.inl"
#endif

//-------------------------------------------------------------------------------------------------
BaseMaterialParameter::BaseMaterialParameter( )
{
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMaterialParameter::SetType( ParameterType a_type )
{
	m_type													=	a_type;

	switch( m_type )
	{
		case SCALAR_PARAMETER:
			m_byteCount										=	4;
		break;

		case VECTOR_PARAMETER:
			m_byteCount										=	24;
		break;

		default:
		break;
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
BaseMaterialParameter::~BaseMaterialParameter()
{
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMaterialParameter::Init( const std::string& a_name , TUint16 a_startOffset )
{
	m_name													=	a_name;
	m_startOffset											=	a_startOffset;
}
//-------------------------------------------------------------------------------------------------
