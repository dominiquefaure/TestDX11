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
bool ShaderByteCodeDX11::Compile( RhiShaderType a_type , std::string& a_sourceCode )
{
	return Compile( a_type , a_sourceCode.c_str() , a_sourceCode.size() );
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
bool ShaderByteCodeDX11::Compile( RhiShaderType a_type , const char* a_sourceCode , int a_size )
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
																			"main",
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

	int t_size												=	t_handle->GetSize();
	char* t_sourceCode										=	new char[ t_size ];
	t_handle->Read( t_sourceCode , t_size );

	// Free the File Handle
	delete t_handle;


	return Compile( a_type , t_sourceCode , t_size );

	return false;
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
bool ShaderByteCodeDX11::LoadBinary( RhiShaderType a_type , const std::string& a_filePath )
{
//	FileHandle* t_handle									=	FileSystem::GetInstance()->OpenRead( a_filePath , true );


	return false;
}
//-----------------------------------------------------------------------------------------------

