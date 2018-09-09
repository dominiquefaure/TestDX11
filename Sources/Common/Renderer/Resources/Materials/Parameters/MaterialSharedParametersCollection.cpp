#include "MaterialSharedParametersCollection.h"

//-------------------------------------------------------------------------------------------------
MaterialSharedParametersCollection::MaterialSharedParametersCollection()
{
	m_parameterDesc											=	nullptr;
	m_slot													=	0;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
MaterialSharedParametersCollection::~MaterialSharedParametersCollection()
{
	m_parameterDesc											=	nullptr;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void MaterialSharedParametersCollection::Init( RhiGraphicDevice* a_device , MaterialParameterDescriptorCollection* a_desc )
{
	m_parameterDesc											=	a_desc;

	m_constantBuffer.Init( a_device , m_parameterDesc->GetMaxRegisterIndex() + 1 );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void MaterialSharedParametersCollection::Bind( TUint32 a_slot )
{
	m_slot													=	a_slot;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
bool MaterialSharedParametersCollection::SetValue( const std::string& a_paramName , TFloat32 a_value )
{
	// Get the Param descriptor
	const MaterialParameterDescriptor* t_descriptor			=	m_parameterDesc->GetDescriptor( a_paramName );

	// if found
	if( t_descriptor != nullptr )
	{
		m_constantBuffer.SetValue( t_descriptor->GetRegisterIndex() , t_descriptor->GetComponentIndex() , a_value );

		return true;
	}
	
	return false;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
bool MaterialSharedParametersCollection::SetValue( const std::string& a_paramName , Vector3F a_value )
{
	// Get the Param descriptor
	const MaterialParameterDescriptor* t_descriptor			=	m_parameterDesc->GetDescriptor( a_paramName );

	// if found
	if( t_descriptor != nullptr )
	{
		m_constantBuffer.SetValue( t_descriptor->GetRegisterIndex() , a_value );

		return true;
	}
	
	return false;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
bool MaterialSharedParametersCollection::SetValue( const std::string& a_paramName , Vector4F a_value )
{
	// Get the Param descriptor
	const MaterialParameterDescriptor* t_descriptor			=	m_parameterDesc->GetDescriptor( a_paramName );

	// if found
	if( t_descriptor != nullptr )
	{
		m_constantBuffer.SetValue( t_descriptor->GetRegisterIndex() , a_value );

		return true;
	}
	
	return false;

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void MaterialSharedParametersCollection::Apply( RhiGraphicContext* a_context )
{
	m_constantBuffer.Commit( a_context  );

	m_constantBuffer.Bind( a_context , RHI_SHADER_TYPE_PIXEL_SHADER , m_slot );
}
//-------------------------------------------------------------------------------------------------
