#ifndef __RENDERER_MATERIAL_PARAMETER_DESCRIPTOR_H__
#define __RENDERER_MATERIAL_PARAMETER_DESCRIPTOR_H__

#include "Core/CoreIncludes.h"


/*
* Describe a Material Parameter
* RegisterIndex and ComponentIndex only valid for non Gloabl parameters
*/
class MaterialParameterDescriptor
{
public:
	enum ParameterType
	{
		MATERIAL_PARAMETER_SCALAR,
		MATERIAL_PARAMETER_VECTOR3,
		MATERIAL_PARAMETER_VECTOR4
	};

public:
	
	MaterialParameterDescriptor();
	~MaterialParameterDescriptor();

	/*
	* Get the Type of parameter
	*/
	FORCE_INLINE ParameterType GetType()const;

	/*
	* Get the Parameter name
	*/
	FORCE_INLINE const std::string& GetName()const;

	/*
	* Get the RegisterIndex
	*/
	FORCE_INLINE TUint16 GetRegisterIndex()const;

	/*
	* Get the 1st Component to use in the Register
	*/
	FORCE_INLINE TUint16 GetComponentIndex()const;

	/*
	* Initialize the Parameter
	*/
	void Init( ParameterType a_type , const std::string& a_name , TUint16 a_registerIndex , TUint16 a_compomentIndex );




protected:

	ParameterType	m_type;

	// Name of the Parameter
	std::string		m_name;

	// Index of the Vector4 register the parameter used
	TUint16			m_registerIndex;

	//Index of the 1st Component of the register to use
	TUint16			m_componentIndex;

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "MaterialParameterDescriptor.inl"
#endif



#endif