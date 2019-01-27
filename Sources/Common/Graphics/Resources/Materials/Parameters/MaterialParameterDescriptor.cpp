#include "MaterialParameterDescriptor.h"

//In debug configuration, the inlline methods need to be include inside a cpp file, to avoid function redefinition errors
#ifdef _DEBUG
#include "MaterialParameterDescriptor.inl"
#endif

//-------------------------------------------------------------------------------------------------
MaterialParameterDescriptor::MaterialParameterDescriptor( )
{
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
MaterialParameterDescriptor::~MaterialParameterDescriptor()
{
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void MaterialParameterDescriptor::Init( ParameterType a_type , const std::string& a_name , TUint16 a_registerIndex , TUint16 a_compomentIndex )
{
	m_type													=	a_type;
	m_name													=	a_name;
	m_registerIndex											=	a_registerIndex;
	m_componentIndex										=	a_compomentIndex;
}
//-------------------------------------------------------------------------------------------------
