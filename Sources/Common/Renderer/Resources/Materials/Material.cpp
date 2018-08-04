#include "Material.h"
#include "../Shaders/Includes.h"

//-------------------------------------------------------------------------------------------------
Material::Material()
{
	m_shaderProgram											=	nullptr;
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
