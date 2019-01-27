#include "Material.h"
#include "../Shaders/Includes.h"

//-------------------------------------------------------------------------------------------------
Material::Material()
{
	m_shaderProgram											=	nullptr;

	m_sharedParametersDesc.AddParameter( "Color" , MaterialParameterDescriptor::MATERIAL_PARAMETER_VECTOR3 , 0 , 0 );

	m_defaultSharedValues.Init( RhiManager::GetInstance()->GetGraphicDevice() , &m_sharedParametersDesc );
	m_defaultSharedValues.SetValue( "Color" ,  Vector4F( 0.9 , 0.8 , 0.02 ) );
	m_defaultSharedValues.Bind( 0 );

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
Material::~Material()
{
	SAFE_DELETE( m_shaderProgram );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void Material::Load( const std::string& a_filePath )
{
	// Load the Json File
	JSonReader t_reader;
	t_reader.Load( a_filePath );

	LoadFromJSon( t_reader.GetRootNode() );

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void Material::LoadFromJSon( const JSonNode* a_rootNode )
{
	const std::string& t_path								=	a_rootNode->GetStringProperty("Program" );

	m_shaderProgram											=	new ShaderProgram();
	m_shaderProgram->Load( t_path );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void Material::Apply( RhiGraphicContext* a_context , RhiVertexLayoutType a_layoutType , TUint64 a_customFlags )
{
	m_defaultSharedValues.Apply( a_context );

	m_shaderProgram->Apply( a_context , a_layoutType , a_customFlags );
}
//-------------------------------------------------------------------------------------------------


//////////
// Get parameters
/////////

//-------------------------------------------------------------------------------------------------
TFloat32 Material::GetScalarParameter( const std::string& a_paramName )const
{
	TFloat32 t_value										=	0.0f;

	m_defaultSharedValues.GetValue( a_paramName , t_value );

	return t_value;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
Vector3F Material::GetVector3Parameter( const std::string& a_paramName )const
{
	Vector3F t_value;

	m_defaultSharedValues.GetValue( a_paramName , t_value );

	return t_value;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
Vector4F Material::GetVector4Parameter( const std::string& a_paramName )const
{
	Vector4F t_value;

	m_defaultSharedValues.GetValue( a_paramName , t_value );

	return t_value;
}
//-------------------------------------------------------------------------------------------------


//////////
// Set parameters
/////////

//-------------------------------------------------------------------------------------------------
void Material::SetParameter( const std::string& a_paramName , const TFloat32 a_value )
{
	m_defaultSharedValues.SetValue( a_paramName , a_value );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void Material::SetParameter( const std::string& a_paramName , const Vector3F& a_value )
{
	m_defaultSharedValues.SetValue( a_paramName , a_value );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void Material::SetParameter( const std::string& a_paramName , const Vector4F& a_value )
{
	m_defaultSharedValues.SetValue( a_paramName , a_value );
}
//-------------------------------------------------------------------------------------------------
