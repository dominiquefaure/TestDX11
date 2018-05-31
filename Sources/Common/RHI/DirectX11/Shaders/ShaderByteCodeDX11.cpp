#include "ShaderByteCodeDX11.h"
#include "../../../Core/CoreMacros.h"

#include <d3dcompiler.h>


#include "../../../Core/IO/Includes.h"


static std::string g_shaderTargetType[]=
{
	"vs_5_0",
	"ps_5_0"
};

#define MAX_SHADER_MACRO_COUNT	128

LPCSTR g_shaderMacroList[]=
{
	"VERTEX_COLOR",
	"VERTEX_TEXCOORD",
	"",
	"",
	"",
	"",
	"",
	"",
	"DUMMY_COLOR"
};



//-----------------------------------------------------------------------------------------------
ShaderByteCodeDX11::ShaderByteCodeDX11( )
{
	m_compiledBlob											=	NULL;
	m_macroList												=	NULL;
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
ShaderByteCodeDX11::~ShaderByteCodeDX11()
{
	SAFE_RELEASE( m_compiledBlob );
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
RhiShaderType ShaderByteCodeDX11::GetShaderType()const
{
	return m_type;
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
const void* ShaderByteCodeDX11::GetByteCode()const
{
	return m_compiledBlob->GetBufferPointer();
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
int ShaderByteCodeDX11::GetSize()const
{
	return m_compiledBlob->GetBufferSize();
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
bool ShaderByteCodeDX11::Compile( std::string& a_sourceCode , RhiShaderCompilationParams& a_params )
{
	return Compile( a_sourceCode.c_str() , a_sourceCode.size() , a_params );
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
bool ShaderByteCodeDX11::Compile( const char* a_sourceCode , int a_size , RhiShaderCompilationParams& a_params )
{
	m_type													=	a_params.m_shaderType;

	ID3DBlob* t_errorMessage;

	int t_compilationFlag									=	0;

	// Build the Array that store the different macro needed
	BuildMacroList( a_params.m_permutationFlags );

	// Compile the Shader
	HRESULT t_result										=	D3DCompile( a_sourceCode ,
																			a_size,
																			NULL ,
																			m_macroList ,
																			NULL ,
																			a_params.m_entryPoint.c_str(),
																			g_shaderTargetType[ m_type ].c_str(),
																			t_compilationFlag,
																			0,
																			&m_compiledBlob,
																			&t_errorMessage );

	// Free the Macro List
	SAFE_DELETE_ARRAY( m_macroList );

	// if the Compilation succeed
	if( t_result != S_OK )
	{
		//TODO display error messages
		assert( false );
		return false;
	}

	return true;

}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
bool ShaderByteCodeDX11::CompileFromFile( const std::string& a_filePath , RhiShaderCompilationParams& a_params )
{
	FileHandle* t_handle									=	FileSystem::GetInstance()->OpenRead( a_filePath , false );

	if( t_handle != NULL )
	{
		// Load the File Content
		int t_size											=	t_handle->GetSize();
		char* t_sourceCode									=	new char[ t_size ];
		int t_readSize										=	t_handle->Read( t_sourceCode , t_size );


		bool t_result										=	Compile( t_sourceCode , t_readSize , a_params );

		delete[] t_sourceCode;

		// Free the File Handle
		delete t_handle;

		return t_result;
	}

	return false;
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
bool ShaderByteCodeDX11::LoadBinary( RhiShaderType a_type , const std::string& a_filePath )
{
	FileHandle* t_handle									=	FileSystem::GetInstance()->OpenRead( a_filePath , true );

	if( t_handle != NULL )
	{
		// Load the File Content
		int t_size											=	t_handle->GetSize();
		char* t_sourceCode									=	new char[ t_size ];

		t_handle->Read( t_sourceCode , t_size );

		// Free the File Handle
		delete t_handle;

		// Create the Blob and copy the Shader byte code into it
		D3DCreateBlob( t_size , &m_compiledBlob );
		memcpy( m_compiledBlob->GetBufferPointer() , t_sourceCode , t_size );

		return true;
	}
	
	return false;
}
//-----------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------
void ShaderByteCodeDX11::InitMacroList( )
{
	m_macroList												=	new D3D_SHADER_MACRO[ MAX_SHADER_MACRO_COUNT ];

	// force values to NULL
	for( int i = 0 ; i < MAX_SHADER_MACRO_COUNT ; i ++ )
	{
		m_macroList[ i ].Name								=	NULL;
		m_macroList[ i ].Definition							=	NULL;
	}

	m_macroCount											=	0;
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
void ShaderByteCodeDX11::PushMacro( RhiShaderCompilationMacros a_macroID )
{
	assert( m_macroCount < MAX_SHADER_MACRO_COUNT );
	
	m_macroList[ m_macroCount ].Name						=	g_shaderMacroList[ a_macroID ];
	m_macroList[ m_macroCount ].Definition					=	"";

	m_macroCount ++;
}
//-----------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------
void ShaderByteCodeDX11::BuildMacroList( const TUint64 a_macro )
{
	InitMacroList( );

	for( int i = 0 ; i < SHADER_MACRO_COUNT ; i ++ )
	{
		if( ISBITSET( a_macro , i ) )
		{
			PushMacro( (RhiShaderCompilationMacros)i );
		}
	}
}
//-----------------------------------------------------------------------------------------------
