#ifndef __RENDERER_SHADER_PROGRAM_H__
#define __RENDERER_SHADER_PROGRAM_H__

#include "../../Core/CoreIncludes.h"

#include "ShaderDefinition.h"

class ShaderProgram
{
public:

	ShaderProgram();
	~ShaderProgram();

	/*
	 * Get the Vertex Shader Deinition 
	 */
	FORCE_INLINE ShaderDefinition* GetVertexShaderDefinition();

	/*
	 * Get the Pixel Shader Deinition 
	 */
	FORCE_INLINE ShaderDefinition* GetPixelShaderDefinition();

	/*
	 * Load the Shader program data from a json file
	 */
	void Load( const std::string& a_jsonFilePath );

	/*
	 * Apply the correct shaders to the Context
	 */
	void Apply( RhiGraphicContext* a_context, const TUint64 a_permutationID );

// Methods
private:


	/*
	 * Try to load a Shader Definition from the JSon file
	 * return NULL, if the property is not defined
	 */
	ShaderDefinition* LoadShaderDefinition( JSonNode& a_rootNode , const std::string& a_propertyName );

// Fields
private:

	// Definition for the different Shaders supported
	ShaderDefinition*	m_vertexShader;
	ShaderDefinition*	m_pixelShader;
};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "ShaderProgram.inl"
#endif



#endif