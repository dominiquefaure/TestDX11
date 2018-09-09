#include "MaterialParameterDescriptorCollection.h"

//In debug configuration, the inlline methods need to be include inside a cpp file, to avoid function redefinition errors
#ifdef _DEBUG
#include "MaterialParameterDescriptorCollection.inl"
#endif


//-------------------------------------------------------------------------------------------------
MaterialParameterDescriptorCollection::MaterialParameterDescriptorCollection()
{
	m_isglobal												=	false;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
MaterialParameterDescriptorCollection::~MaterialParameterDescriptorCollection()
{
	SAFE_DELETE_OBJECT_VECTOR_ARRAY( m_paramList );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TSint32 MaterialParameterDescriptorCollection::IndexOf( const std::string& a_name )const
{
	int t_count												=	m_paramList.size();
	for( int i = 0 ; i < t_count ; i ++ )
	{
		if( m_paramList[ i ]->GetName() == a_name )
		{
			return i;
		}
	}

	// not found
	return -1;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
const MaterialParameterDescriptor* MaterialParameterDescriptorCollection::GetDescriptor( const std::string& a_name )const
{
	int t_count												=	m_paramList.size();
	for( int i = 0 ; i < t_count ; i ++ )
	{
		if( m_paramList[ i ]->GetName() == a_name )
		{
			return m_paramList[ i ];
		}
	}

	// not found
	return nullptr;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void MaterialParameterDescriptorCollection::Init( const std::string& a_name )
{
	m_name													=	a_name;
	if( m_name == "$Global")
	{
		m_isglobal											=	true;
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TUint32 MaterialParameterDescriptorCollection::AddParameter(  const std::string& a_name , MaterialParameterDescriptor::ParameterType a_type , TUint16 a_registerIndex , TUint16 a_compomentIndex )
{
	// Create a new Descriptor
	MaterialParameterDescriptor* t_descriptor				=	new MaterialParameterDescriptor();
	t_descriptor->Init( a_type , a_name , a_registerIndex , a_compomentIndex );

	// Add it to the list
	m_paramList.push_back( t_descriptor );

	// return it's index
	return ( m_paramList.size() - 1 );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TUint32 MaterialParameterDescriptorCollection::GetMaxRegisterIndex()
{
	TUint32 t_maxRegister									=	0;

	// parse the parameters
	TUint32 t_count											=	m_paramList.size();
	for( int i = 0 ; i < t_count ; i ++ )
	{
		if( m_paramList[ i ]->GetRegisterIndex() > t_maxRegister )
		{
			t_maxRegister									=	m_paramList[ i ]->GetRegisterIndex();
		}
	}

	return t_maxRegister;
}
//-------------------------------------------------------------------------------------------------
