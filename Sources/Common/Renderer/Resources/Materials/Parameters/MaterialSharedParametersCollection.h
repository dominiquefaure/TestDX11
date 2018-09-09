#ifndef __RENDERER_MATERIAL_SHARED_PARAMETERS_COLLECTION_H__
#define __RENDERER_MATERIAL_SHARED_PARAMETERS_COLLECTION_H__

#include "Core/CoreIncludes.h"
#include "Renderer/Resources/ConstantBuffers/Includes.h"

#include "MaterialParameterDescriptorCollection.h"


class MaterialSharedParametersCollection
{

public:

	MaterialSharedParametersCollection();
	~MaterialSharedParametersCollection();

	/*
	* Init the Collection. Create the constant buffer
	*/
	void Init( RhiGraphicDevice* a_device , MaterialParameterDescriptorCollection* a_desc );

	/*
	* Bind the Shader to a slot
	* todo compute the slot from shader instance
	*/
	void Bind( TUint32 a_slot );

	/*
	* Set Scalar value
	*
	* @param a_paramName	name of the parameter we want to set the value
	* @param a_value		New value to set
	* @return true if the operation succeed
	*/
	bool SetValue( const std::string& a_paramName , TFloat32 a_value );

	/*
	* Set Vector3 value
	*
	* @param a_paramName	name of the parameter we want to set the value
	* @param a_value		New value to set
	* @return true if the operation succeed
	*/
	bool SetValue( const std::string& a_paramName , Vector3F a_value );

	/*
	* Set Vector4 value
	*
	* @param a_paramName	name of the parameter we want to set the value
	* @param a_value		New value to set
	* @return true if the operation succeed
	*/
	bool SetValue( const std::string& a_paramName , Vector4F a_value );

	/*
	* Apply the Parameters, if needed to the Context
	*/
	void Apply( RhiGraphicContext* a_context );

private:

	// Constant Buffer Slot
	TUint32									m_slot;

	// The constant buffer
	ConstantBuffer							m_constantBuffer;

	// Collection that describe the parameters
	MaterialParameterDescriptorCollection*	m_parameterDesc;
};

#endif