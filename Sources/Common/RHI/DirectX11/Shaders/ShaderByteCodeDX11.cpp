#include "ShaderByteCodeDX11.h"
#include "../../../Core/CoreMacros.h"

#include <d3dcompiler.h>


#include "../../../Core/IO/Includes.h"


static std::string g_shaderTargetType[]=
{
	"vs_5_0",
	"ps_5_0"
};


//-----------------------------------------------------------------------------------------------
ShaderByteCodeDX11::ShaderByteCodeDX11( )
{
	m_compiledBlob											=	NULL;
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
bool ShaderByteCodeDX11::Compile( RhiShaderType a_type , std::string& a_sourceCode , const std::string& a_entryPoint )
{
	return Compile( a_type , a_sourceCode.c_str() , a_sourceCode.size() , a_entryPoint.c_str() );
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
bool ShaderByteCodeDX11::Compile( RhiShaderType a_type , const char* a_sourceCode , int a_size ,  const char* a_entryPoint )
{
	m_type													=	a_type;

	ID3DBlob* t_errorMessage;

	int t_compilationFlag									=	0;

	// Compile the Shader
	HRESULT t_result										=	D3DCompile( a_sourceCode ,
																			a_size,
																			NULL ,
																			NULL ,
																			NULL ,
																			a_entryPoint,
																			g_shaderTargetType[ a_type ].c_str(),
																			t_compilationFlag,
																			0,
																			&m_compiledBlob,
																			&t_errorMessage );

	// if the Compilation succeed
	if( t_result != S_OK )
	{
		//TODO display error messages

		return false;
	}

	return true;

}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
bool ShaderByteCodeDX11::CompileFromFile( RhiShaderType a_type , const std::string& a_filePath )
{

	FileHandle* t_handle									=	FileSystem::GetInstance()->OpenRead( a_filePath , false );

	if( t_handle != NULL )
	{
		// Load the File Content
		int t_size											=	t_handle->GetSize();
		char* t_sourceCode									=	new char[ t_size ];
		int t_readSize										=	t_handle->Read( t_sourceCode , t_size );


//		bool t_result										=	Compile( a_type , t_sourceCode , t_readSize , a_macro );		bool t_result										=	Compile( a_type , t_sourceCode , t_readSize , a_macro );
		bool t_result										=	Compile( a_type , t_sourceCode , t_readSize  );

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

