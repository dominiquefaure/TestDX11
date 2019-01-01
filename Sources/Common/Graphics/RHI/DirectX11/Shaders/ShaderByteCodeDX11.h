#ifndef __RHI_SHADER_BYTE_CODE_DX11_H__
#define __RHI_SHADER_BYTE_CODE_DX11_H__

#include <d3d11.h>
#include <string>

#include <d3dcompiler.h>

#include "../../../../Core/Base/Includes.h"
#include "../../RhiEnums.h"
#include "../../Common/RhiShaderCompilationParams.h"
#include "../../Common/ShaderReflection/Includes.h"


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
	* a_sourceCode	String that store the HSLS code
	* a_params		set of parameters to drive the compilation
	*/
	bool Compile( std::string& a_sourceCode , RhiShaderCompilationParams& a_params );

	/*
	* Compile the ByteCode from an HLSL string
	* a_sourceCode	String that store the HSLS code
	* a_size		Size of the source code string
	* a_params		set of parameters to drive the compilation
	*/
	bool Compile( const char* a_sourceCode , int a_size , RhiShaderCompilationParams& a_params );

	/*
	* Compile the ByteCode, from an HLSL file
	* a_filePath	HLSL file path
	* a_params		set of parameters to drive the compilation
	*/
	bool CompileFromFile( const std::string& a_filePath , RhiShaderCompilationParams& a_params );

	/*
	* Load pre-compiled ByteCode
	*/
	bool LoadBinary( RhiShaderType a_type , const std::string& a_filePath );


	/*
	 * use the relection system, to get information's about the different parameters that can be passed to the shader
	 */
	RhiShaderReflectionInfos* GenerateRelectionInfos();

// Methods
private:

	/*
	 * Build the List of Macro to define
	 */
	void BuildMacroList( const TUint64 a_macro );

	/*
	* Init the Internal Macro list, and populate it with default environement values
	*/
	void InitMacroList( );

	void PushMacro( RhiShaderCompilationMacros a_macro );

	/*
	 * Setup a ConstantBufferDesc from the reflection system information's
	 */
	void SetupConstantBufferDesc( RhiShaderConstantBufferDesc* a_targetDesc , TUint32 a_registerSlot , ID3D11ShaderReflectionConstantBuffer* a_reclectionCB );

// Fields
private :


	// indicate the Type of Shader ( VS , PS ... )
	RhiShaderType		m_type;

	// Blob used to store the compiled byte code
	ID3DBlob*			m_compiledBlob;

	// internal array that store all the macro defined to compile a Shader. 
	D3D_SHADER_MACRO*	m_macroList;

	// number of macro defined
	int					m_macroCount;
};


#endif