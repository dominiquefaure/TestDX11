#include "ShaderProgram.h"


#ifdef _DEBUG
#include "ShaderProgram.inl"
#endif

#include "ShaderDefinition.h"



// Array that store the permutationFlags to add in order to get valid shader that match the VertexLayout
TUint64 g_shaderLayoutPermutationFlags[]=
{
	0, // RHI_VERTEX_ELEMENT_TYPE_POSITION : none
	1, // RHI_VERTEX_ELEMENT_TYPE_COLOR : SHADER_MACRO_VERTEX_COLOR
	3, // RHI_VERTEX_ELEMENT_TYPE_TEXCOORD0 : SHADER_MACRO_VERTEX_COLOR | SHADER_MACRO_VERTEX_TEXTURED
};


//---------------------------------------------------------------------------------------------
ShaderProgram::ShaderProgram()
{
	m_vertexShader											=	NULL;
	m_pixelShader											=	NULL;

	InitVertexLayoutSupport();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
ShaderProgram::~ShaderProgram()
{
	SAFE_DELETE( m_vertexShader );
	SAFE_DELETE( m_pixelShader );

	SAFE_DELETE_ARRAY( m_vertexLayoutSupport );
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

	SetSupportedVertexLayouts( t_document.GetRootNode() );
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
void ShaderProgram::InitVertexLayoutSupport()
{
	m_vertexLayoutSupport								=	new TBool[ RHI_VERTEX_LAYOUT_COUNT ];

	for( int i = 0 ; i < RHI_VERTEX_LAYOUT_COUNT ; i ++ )
	{
		m_vertexLayoutSupport[ i ]						=	false;
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void ShaderProgram::SetSupportedVertexLayouts( JSonNode& a_rootNode )
{
	// Get the Property that store the list of supported VertexLayout
	JSonProperty t_datas									=	a_rootNode.GetProperty( "SupportedLayouts" );
	if( t_datas.IsArray() )
	{
		int t_size											=	t_datas.GetArraySize();

		TUint64* t_layouts									=	new TUint64[ t_size ];

		// read the Datas
		t_datas.GetInt64Array( t_layouts , t_size );

		for( int i = 0 ; i < t_size;  i ++ )
		{
			int t_index										=	t_layouts[ i ];
			m_vertexLayoutSupport[ t_index ]				=	true;
		}
	}
	
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
TBool ShaderProgram::Apply( RhiGraphicContext* a_context, const TUint64 a_permutationID )
{
	TUint64 t_layoutIndex									=	(TUint64)a_context->GetVertexLayout()->GetLayoutType();
	if( m_vertexLayoutSupport[ t_layoutIndex ] )
	{
		// add the permutations flags related to the VertexLayout
		TUint64 t_permutationID								=	a_permutationID | g_shaderLayoutPermutationFlags[ t_layoutIndex ];	

		if( m_vertexShader != NULL )
		{
			ShaderPermutation* t_permutation				=	m_vertexShader->GetPermutation( t_permutationID );

			a_context->SetVertexShader( t_permutation->GetVertexShader() );
		}
		else
		{
			a_context->SetVertexShader( NULL );
		}

		if( m_pixelShader != NULL )
		{
			ShaderPermutation* t_permutation				=	m_pixelShader->GetPermutation( t_permutationID );

			a_context->SetPixelShader( t_permutation->GetPixelShader() );
		}
		else
		{
			a_context->SetPixelShader( NULL );
		}

		return true;
	};

	return false;
}
//---------------------------------------------------------------------------------------------
