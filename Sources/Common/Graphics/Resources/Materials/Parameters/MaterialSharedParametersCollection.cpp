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


///////
// Get Values
///////

//-------------------------------------------------------------------------------------------------
bool MaterialSharedParametersCollection::GetValue( const std::string& a_paramName , TFloat32& a_value )const
{
	// Get the Param descriptor
	const MaterialParameterDescriptor* t_descriptor			=	m_parameterDesc->GetDescriptor( a_paramName );

	if( t_descriptor != nullptr )
	{
		if( t_descriptor->GetType() == MaterialParameterDescriptor::MATERIAL_PARAMETER_SCALAR )
		{
			a_value											=	m_constantBuffer.GetValue( t_descriptor->GetRegisterIndex() , t_descriptor->GetComponentIndex() );

			return true;
		}
	}

	return false;

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
bool MaterialSharedParametersCollection::GetValue( const std::string& a_paramName , Vector3F& a_value )const
{
	// Get the Param descriptor
	const MaterialParameterDescriptor* t_descriptor			=	m_parameterDesc->GetDescriptor( a_paramName );

	if( t_descriptor != nullptr )
	{
		if( t_descriptor->GetType() == MaterialParameterDescriptor::MATERIAL_PARAMETER_VECTOR3 )
		{
			Vector4F t_value								=	m_constantBuffer.GetValue( t_descriptor->GetRegisterIndex() );
			
			a_value.Set( t_value.x , t_value.y , t_value.z );

			return true;
		}
	}

	return false;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
bool MaterialSharedParametersCollection::GetValue( const std::string& a_paramName , Vector4F& a_value )const
{
	// Get the Param descriptor
	const MaterialParameterDescriptor* t_descriptor			=	m_parameterDesc->GetDescriptor( a_paramName );

	if( t_descriptor != nullptr )
	{
		if( t_descriptor->GetType() == MaterialParameterDescriptor::MATERIAL_PARAMETER_VECTOR4 )
		{
			a_value											=	m_constantBuffer.GetValue( t_descriptor->GetRegisterIndex()  );

			return true;
		}
	}

	return false;
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
TFloat32 MaterialSharedParametersCollection::GetScalar( const std::string& a_paramName )const
{
	// Get the Param descriptor
	const MaterialParameterDescriptor* t_descriptor			=	m_parameterDesc->GetDescriptor( a_paramName );

	if( t_descriptor != nullptr )
	{
		if( t_descriptor->GetType() == MaterialParameterDescriptor::MATERIAL_PARAMETER_SCALAR )
		{
			return m_constantBuffer.GetValue( t_descriptor->GetRegisterIndex() , t_descriptor->GetComponentIndex() );
		}
	}

	return 0.0f;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
Vector3F MaterialSharedParametersCollection::GetVector3( const std::string& a_paramName )const
{
	// Get the Param descriptor
	const MaterialParameterDescriptor* t_descriptor			=	m_parameterDesc->GetDescriptor( a_paramName );

	if( t_descriptor != nullptr )
	{
		if( t_descriptor->GetType() == MaterialParameterDescriptor::MATERIAL_PARAMETER_VECTOR3 )
		{
			Vector4F t_vec	=	 m_constantBuffer.GetValue( t_descriptor->GetRegisterIndex() );

			return Vector3F( t_vec.x , t_vec.y , t_vec.z );
		}
	}

	return 0.0f;

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
Vector4F MaterialSharedParametersCollection::GetVector4( const std::string& a_paramName )const
{
	// Get the Param descriptor
	const MaterialParameterDescriptor* t_descriptor			=	m_parameterDesc->GetDescriptor( a_paramName );

	if( t_descriptor != nullptr )
	{
		if( t_descriptor->GetType() == MaterialParameterDescriptor::MATERIAL_PARAMETER_VECTOR4 )
		{
			return m_constantBuffer.GetValue( t_descriptor->GetRegisterIndex() );
		}
	}

	return 0.0f;
}
//-------------------------------------------------------------------------------------------------


///////
// Set Values
///////

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
