#include "Material.h"
#include "../Shaders/Includes.h"

//-------------------------------------------------------------------------------------------------
Material::Material()
{
	m_shaderProgram											=	nullptr;

//	m_vectorParam.Init( "Color" , 0 );
//	m_vectorParam.SetValue( Vector3F( 0.5 , 0.8 , 0.02 ) );

	m_parameterConstants.Init( RhiManager::GetInstance()->GetGraphicDevice() , 256 );

	m_parameterConstants.SetValue( 0 , Vector4F( 0.5 , 0.8 , 0.02 ) );

//	m_vectorParam.Apply( &m_parameterConstants );

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
	m_parameterConstants.Commit( a_context , RHI_SHADER_TYPE_PIXEL_SHADER , 0 );
	m_parameterConstants.Bind( a_context , RHI_SHADER_TYPE_PIXEL_SHADER , 0 );
}
//-------------------------------------------------------------------------------------------------
