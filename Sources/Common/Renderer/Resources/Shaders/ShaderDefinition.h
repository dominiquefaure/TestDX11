#ifndef __RENDERER_SHADER_H__
#define __RENDERER_SHADER_H__

#include "Core/CoreIncludes.h"

#include "RHI/Includes.h"

class ShaderPermutation;

class ShaderDefinition
{
	
public:

	ShaderDefinition();
	~ShaderDefinition();

	/*
	 * Get Mask for the different permutation supported
	 *
	 */
	FORCE_INLINE TUint64 GetPermutationMask();

	/*
	 * Get the Shader Permutation matching the ID
	 */
	ShaderPermutation* GetPermutation( const TUint64 a_permutationID );

	/*
	 * Se tthe Permutation mask
	 */
	void SetPermutationMask( TUint64 a_mask );

	/*
	 * Set the Source Code to use
	 */
	void SetSourceCode( RhiShaderType a_type , const std::string& a_sourceCode );

	/*
	 * Load the Source code from a file
	 */
	void LoadSourceCode( RhiShaderType a_type , const std::string& a_filePath );

	/*
	 * Load all the Shader information's from a JSon node
	 */
	void LoadFromJSon( const JSonNode* a_rootNode );

// Methods
private:

	/*
	 * Create a new Permutation
	 */
	ShaderPermutation* CreatePermutation( const TUint64 a_permutationID );

// Fields
private:

	// Type of the Shader
	RhiShaderType							m_type;

	// Mask used to filter permutations flags not supported
	TUint64									m_permutationMask;

	// Shader source code, allow to generate permutation at runtime
	std::string								m_sourceCode;

	// name of the Shader Entry point method
	std::string								m_entryPoint;

	// map that store the Different Permutations
	std::map<TUint64 , ShaderPermutation* >	m_permutationMap;

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "ShaderDefinition.inl"
#endif


#endif