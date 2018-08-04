#ifndef __RENDERER_RESOURCES_MATERIALS_H__
#define __RENDERER_RESOURCES_MATERIALS_H__

#include "Core/CoreIncludes.h"
#include "RHI/Includes.h"

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

// Methods
private:

	void LoadFromJSon( const JSonNode* a_rootNode );

// Fields
private:

	// Program that Store the Shaders needed for this Material
	ShaderProgram*	m_shaderProgram;
};

#endif