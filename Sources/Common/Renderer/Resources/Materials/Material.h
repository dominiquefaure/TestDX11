#ifndef __RENDERER_RESOURCES_MATERIALS_H__
#define __RENDERER_RESOURCES_MATERIALS_H__

#include "Core/CoreIncludes.h"
#include "RHI/Includes.h"

#include "MaterialParameterVector3.h"

class ShaderProgram;

class Material : public ReferenceCounted
{
public:

	Material();
	virtual ~Material();

	ShaderProgram* GetShaderProgram() { return m_shaderProgram; }

	/*
	* Load the Material definition from a JSON File
	*/
	void Load( const std::string& a_filePath );

	/*
	* Apply the Material to the Context
	*/
	void Apply( RhiGraphicContext* a_context );


// Methods
private:

	void LoadFromJSon( const JSonNode* a_rootNode );

// Fields
private:

	// Program that Store the Shaders needed for this Material
	ShaderProgram*	m_shaderProgram;


	// Constant Buffer used to provide all the Material parameters
	ConstantBuffer				m_parameterConstants;

//	MaterialParameterVector3	m_vectorParam;
};

#endif