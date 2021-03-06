#include "ShaderDefinition.h"

#ifdef _DEBUG
#include "ShaderDefinition.inl"
#endif

//---------------------------------------------------------------------------------------------
ShaderDefinition::ShaderDefinition()
{
	m_type													=	RHI_SHADER_TYPE_NOT_SET;
	m_sourceCode											=	"";
	m_permutationMask										=	0;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
ShaderDefinition::~ShaderDefinition()
{
	
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
ShaderPermutation* ShaderDefinition::GetPermutation( const TUint64 a_permutationID )
{
	// remove the flags not managed by this Shader
	TUint64 t_permitutationID								=	a_permutationID & m_permutationMask;

	ShaderPermutation* t_permutation						=	m_permutationMap[ t_permitutationID ];

	if( t_permutation == NULL )
	{
		return CreatePermutation( t_permitutationID );

	}
	return t_permutation;	
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void ShaderDefinition::SetPermutationMask( TUint64 a_mask )
{
	m_permutationMask										=	a_mask;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void ShaderDefinition::SetSourceCode( RhiShaderType a_type , const std::string& a_sourceCode )
{
	m_type													=	a_type;
	m_sourceCode											=	a_sourceCode;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void ShaderDefinition::LoadSourceCode( RhiShaderType a_type , const std::string& a_filePath )
{
	m_type													=	a_type;
	FileHandle* t_handle									=	FileSystem::GetInstance()->OpenRead( a_filePath , false );

	if( t_handle != NULL )
	{
		// Load the File Content
		int t_size											=	t_handle->GetSize();
		char* t_sourceCode									=	new char[ t_size + 1];
		int t_readSize										=	t_handle->Read( t_sourceCode , t_size );

		t_sourceCode[ t_readSize ]='\0';

		SetSourceCode( a_type , t_sourceCode );

		// Free the File Handle
		delete t_handle;

		delete[] t_sourceCode;
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void ShaderDefinition::LoadFromJSon( JSonNode& a_rootNode )
{
	// Get the Shader Type
	m_type													=	static_cast<RhiShaderType>( a_rootNode.GetInt64Property("Type" ) );

	m_permutationMask										=	a_rootNode.GetInt64Property("PermutationMask" );

	std::string& t_filePath									=	a_rootNode.GetStringProperty( "SourcePath" );

	LoadSourceCode( m_type , t_filePath );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
ShaderPermutation* ShaderDefinition::CreatePermutation( const TUint64 a_permutationID )
{
	// Generate the byte code matching the permutation
	RhiShaderByteCode t_byteCode;
	t_byteCode.Compile( m_type , m_sourceCode , a_permutationID , "main" );

	//get the device
	RhiGraphicDevice* t_device								=	RhiManager::GetInstance()->GetGraphicDevice();

	// Create the Permutation
	ShaderPermutation* t_permutation						=	new ShaderPermutation();
	t_permutation->Init( t_device , m_type , t_byteCode , a_permutationID );

	// Add the Permutation to the List
	m_permutationMap[ a_permutationID ]						=	t_permutation;

	return t_permutation;
}
//---------------------------------------------------------------------------------------------

