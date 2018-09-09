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
void Material::Apply( RhiGraphicContext* a_context )
{
	m_defaultSharedValues.Apply( a_context );
}
//-------------------------------------------------------------------------------------------------
