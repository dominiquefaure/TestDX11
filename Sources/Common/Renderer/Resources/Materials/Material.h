#ifndef __RENDERER_RESOURCES_MATERIALS_H__
#define __RENDERER_RESOURCES_MATERIALS_H__

#include "Core/CoreIncludes.h"
#include "RHI/Includes.h"
#include "../ConstantBuffers/Includes.h"

#include "Parameters/Includes.h"

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
	void Apply( RhiGraphicContext* a_context , RhiVertexLayoutType a_layoutType , TUint64 a_customFlags );


	/*
	* Get a Scalar parameter current value
	*/
	TFloat32 GetScalarParameter( const std::string& a_paramName )const;

	/*
	* Get a Scalar parameter current value
	*/
	Vector3F GetVector3Parameter( const std::string& a_paramName )const;

	/*
	* Get a Scalar parameter current value
	*/
	Vector4F GetVector4Parameter( const std::string& a_paramName )const;

	/*
	* Set a Scalar value
	*/
	void SetParameter( const std::string& a_paramName , const TFloat32 a_value );

	/*
	* Set a Vector3 value
	*/
	void SetParameter( const std::string& a_paramName , const Vector3F& a_value );

	/*
	* Set a Vector4 value
	*/
	void SetParameter( const std::string& a_paramName , const Vector4F& a_value );


// Methods
private:

	void LoadFromJSon( const JSonNode* a_rootNode );

// Fields
private:

	// Program that Store the Shaders needed for this Material
	ShaderProgram*	m_shaderProgram;

	// Describe all the Shared parameters
	MaterialParameterDescriptorCollection	m_sharedParametersDesc;

	//default SharedParameters to use
	MaterialSharedParametersCollection		m_defaultSharedValues;
};

#endif