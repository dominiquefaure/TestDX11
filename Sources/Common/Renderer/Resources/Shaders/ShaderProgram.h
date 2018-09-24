#ifndef __RENDERER_SHADER_PROGRAM_H__
#define __RENDERER_SHADER_PROGRAM_H__

#include "Core/CoreIncludes.h"
#include "RHI/Includes.h"

class ShaderDefinition;

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
	 * return false if there is no permutation available for the actual VertexLayout
	 */
	TBool Apply( RhiGraphicContext* a_context, const RhiVertexLayoutType a_layoutType , const TUint64 a_permutationID );

// Methods
private:

	/*
	 * Init the Buffer that store flag to know if a layout is supported
	 * set all the values to false by default
	 */
	void InitVertexLayoutSupport();

	/*
	 * Get from the JSon node the different vertexLayuout supported
	 */
	void SetSupportedVertexLayouts(const JSonNode* a_rootNode );

	/*
	 * Try to load a Shader Definition from the JSon file
	 * return NULL, if the property is not defined
	 */
	ShaderDefinition* LoadShaderDefinition( const JSonNode* a_rootNode , const std::string& a_propertyName );

// Fields
private:

	// Definition for the different Shaders supported
	ShaderDefinition*	m_vertexShader;
	ShaderDefinition*	m_pixelShader;

	// Arrray that store flags used to know if a given VertexLayout is supported by this Program
	TBool*				m_vertexLayoutSupport;

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "ShaderProgram.inl"
#endif



#endif