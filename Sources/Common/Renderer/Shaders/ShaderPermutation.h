#ifndef __RENDERER_SHADER_PERMUTATION_H__
#define __RENDERER_SHADER_PERMUTATION_H__

#include "../../RHI/Includes.h"



class ShaderPermutation
{
	
public:

	ShaderPermutation();
	~ShaderPermutation();

	/*
	 * Get the Shader Type
	 */
	FORCE_INLINE RhiShaderType GetType()const;

	/*
	 * Get the Vertex Shader, not NULL only if Shader type is Vertex Shader
	 */
	FORCE_INLINE RhiVertexShader* GetVertexShader();

	/*
	 * Get the Pixel Shader, not NULL only if Shader type is Pixel Shader
	 */
	FORCE_INLINE RhiPixelShader* GetPixelShader();

	/*
	 * Get the Reflection informations
	 */
	FORCE_INLINE const RhiShaderReflectionInfos* GetReflectionInfos()const;

	/*
	 * Init the Permutation
	 */
	void Init( RhiGraphicDevice* a_device , RhiShaderType a_type , RhiShaderByteCode& a_byteCode , TUint64 a_permitationID );

// Fields
private:

	// type of Shader generated for this Permutation
	RhiShaderType				m_shaderType;

	// Id of the Permutation
	TUint64						m_permutationID;

	// Pointer to the generated Shader. only 1 is valid,matching the Shader type
	RhiVertexShader*			m_vertexShader;
	RhiPixelShader*				m_pixelShader;

	// information's about the shader 
	RhiShaderReflectionInfos*	m_relectionInfos;
};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "ShaderPermution.inl"
#endif


#endif
