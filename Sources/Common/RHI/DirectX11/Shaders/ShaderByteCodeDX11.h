#ifndef __RHI_SHADER_BYTE_CODE_DX11_H__
#define __RHI_SHADER_BYTE_CODE_DX11_H__

#include <d3d11.h>
#include <string>

#include "../../RhiEnums.h"

class ShaderByteCodeDX11
{


public:

	ShaderByteCodeDX11( );
	~ShaderByteCodeDX11();

	/*
	* Get the Shader Type
	*/
	RhiShaderType GetShaderType()const;

	/*
	* Get the compiled Byte Code
	*/
	const void* GetByteCode()const;

	/*
	* Get the compiled ByteCode Size
	*/
	int GetSize()const;

	/*
	* Compile the ByteCode from an HLSL string
	*/
	bool Compile( RhiShaderType a_type , std::string& a_sourceCode , const std::string& a_entryPoint );

	/*
	* Compile the ByteCode from an HLSL string
	*/
	bool Compile( RhiShaderType a_type , const char* a_sourceCode , int a_size , const char* a_entryPoint = "main" );

	/*
	* Compile the ByteCode, from an HLSL file
	*/
	bool CompileFromFile( RhiShaderType a_type , const std::string& a_filePath );

	/*
	* Load pre-compiled ByteCode
	*/
	bool LoadBinary( RhiShaderType a_type , const std::string& a_filePath );

private :


	RhiShaderType	m_type;

	// Blob used to store the compiled byte code
	ID3DBlob*		m_compiledBlob;

};


#endif