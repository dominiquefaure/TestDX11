#ifndef __RENDERER_RESOURCES_MATERIAL_TEMPLATE_H__
#define __RENDERER_RESOURCES_MATERIAL_TEMPLATE_H__

#include "Core/CoreIncludes.h"
#include "Graphics/Resources/Shaders/Includes.h"

#include "MaterialParameterDescriptors.h"
/*
* Define the Template of a set of Materials.
*
* a Template contains:
*	- Shader program to use
*	- Description on the different Parameters that can be set per Material/Instance
*/
class MaterialTemplate : public Asset
{

public:

	MaterialTemplate();
	virtual ~MaterialTemplate();

	/*
	* Get the MaterialTemplate path
	*/
	FORCE_INLINE const std::string& GetPath()const;

	/*
	* Get the ShaderProgram used by this Template
	*/
	FORCE_INLINE ShaderProgram* GetShaderProgram()const;

protected:


	virtual void LoadFromJSon( const JSonNode* a_rootNode );

// Methods
private:

	/*
	* Add a scalar parameter to the Template
	*/
	void AddScalarParameter( const std::string& a_name , TFloat32 a_defaultValue );

	/*
	* Add a Vector3 parameter to the Template
	*/
	void AddVector3Parameter( const std::string& a_name , const Vector3F& a_defaultValue );


	/////// Loading Methods


	/*
	* Load the Shader program from JSon node
	*/ 
	void LoadShaderProgram( const JSonNode* a_rootNode );

	/*
	* Load all the parameters
	*/
	void LoadParameters( const JSonNode* a_rootNode );

	/*
	* Load all the Scalar parameters from JSon file
	*/ 
	void LoadScalarParameters( const JSonNodeArrayProperty* a_nodes );

	/*
	* Load the Scalar parameter represented by the given node
	*/
	void LoadScalarParameter( const JSonNode* a_parameterNode );


	/*
	* Load all the Vector3 parameters from JSon file
	*/ 
	void LoadVector3Parameters( const JSonNodeArrayProperty* a_nodes );

	/*
	* Load the Vector3 parameter represented by the given node
	*/
	void LoadVector3Parameter( const JSonNode* a_parameterNode );

// Fields
private:

	// Template Path
	std::string									m_path;

	// Program that Store the Shaders needed for this Material
	ShaderProgram*								m_shaderProgram;

	// Array that store all the Scalar parameters descriptors
	TArray<MaterialParameterScalarDescriptor*>	m_scalarParameters;

	// Array that store all the Vector3 parameters descriptors
	TArray<MaterialParameterVector3Descriptor*>	m_vector3Parameters;



};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "MaterialTemplate.inl"
#endif


typedef ReferenceCountedPtr<MaterialTemplate>	MaterialTemplateRef;

#endif