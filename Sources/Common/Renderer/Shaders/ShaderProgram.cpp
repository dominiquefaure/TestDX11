#include "ShaderProgram.h"


#ifdef _DEBUG
#include "ShaderProgram.inl"
#endif

//---------------------------------------------------------------------------------------------
ShaderProgram::ShaderProgram()
{
	m_vertexShader											=	NULL;
	m_pixelShader											=	NULL;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
ShaderProgram::~ShaderProgram()
{
	SAFE_DELETE( m_vertexShader );
	SAFE_DELETE( m_pixelShader );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void ShaderProgram::Load( const std::string& a_jsonFilePath )
{
	// Load the content of the JSon file
	JsonDocument t_document;
	t_document.Load( a_jsonFilePath );

	m_vertexShader											=	LoadShaderDefinition( t_document.GetRootNode() , "VertexShader" );
	m_pixelShader											=	LoadShaderDefinition( t_document.GetRootNode() , "PixelShader" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
ShaderDefinition* ShaderProgram::LoadShaderDefinition( JSonNode& a_rootNode , const std::string& a_propertyName )
{
	
	// Get the requested property
	JSonProperty t_property								=	a_rootNode.GetProperty( a_propertyName );

	// if the property is valid and is a JSON sub object
	if( t_property.GetType() ==  JSON_PROPERTY_TYPE_NODE )
	{
		// Get the JSon Object
		JSonNode t_obj									=	t_property.GetJSonObject();

		// Create a ew DEfinition and load it's content from the JSOn node properties
		ShaderDefinition* t_definition					=	new ShaderDefinition();
		t_definition->LoadFromJSon( t_obj );

		//return the definition created
		return t_definition;
	}

	return NULL;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void ShaderProgram::Apply( RhiGraphicContext* a_context, const TUint64 a_permutationID )
{
	if( m_vertexShader != NULL )
	{
		ShaderPermutation* t_permutation				=	m_vertexShader->GetPermutation( a_permutationID );

		a_context->SetVertexShader( t_permutation->GetVertexShader() );
	}
	else
	{
		a_context->SetVertexShader( NULL );
	}

	if( m_pixelShader != NULL )
	{
		ShaderPermutation* t_permutation				=	m_pixelShader->GetPermutation( a_permutationID );

		a_context->SetPixelShader( t_permutation->GetPixelShader() );
	}
	else
	{
		a_context->SetPixelShader( NULL );
	}

}
//---------------------------------------------------------------------------------------------
