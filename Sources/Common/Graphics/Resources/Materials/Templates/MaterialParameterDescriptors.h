#ifndef __RENDERER_RESOURCES_MATERIALS_PARAMETER_DESCRIPTORS_H__
#define __RENDERER_RESOURCES_MATERIALS_PARAMETER_DESCRIPTORS_H__

#include "Core/CoreIncludes.h"

enum MaterialParameterType
{
	MATERIAL_PARAMETER_TYPE_INVALID	=	0,
	MATERIAL_PARAMETER_TYPE_SCALAR,
	MATERIAL_PARAMETER_TYPE_VECTOR3,
	MATERIAL_PARAMETER_TYPE_VECTOR4,
	MATERIAL_PARAMETER_TYPE_TEXTURE,
	MATERIAL_PARAMETER_TYPE_SAMPLER
};

/*
* Template class for all the MaterialParameterDescriptors
*/
template< typename ValueType> class TMaterialParameterDescriptor
{
public:


	TMaterialParameterDescriptor( )
	{
		m_parameterType										=	MATERIAL_PARAMETER_TYPE_INVALID;
	}

	virtual ~TMaterialParameterDescriptor()
	{
	}

	/*
	* Get the Type of parameter
	*/
	FORCE_INLINE MaterialParameterType GetType()const
	{
		return m_parameterType;
	}

	/*
	* Get the Parameter name
	*/
	FORCE_INLINE const std::string& GetName()const
	{
		return m_name;
	}


	FORCE_INLINE const ValueType& GetDefault()const
	{
		return m_defaultValue;
	}

	FORCE_INLINE void Init( const std::string& a_name , const ValueType& a_value )
	{
		m_name												=	a_name;
		m_defaultValue										=	a_value;
	}

protected:

	MaterialParameterType	m_parameterType;

	// Name of the Parameter
	std::string		m_name;

	// the default value
	ValueType		m_defaultValue;


};

/////// the different Material Parameters DEscriptors


class MaterialParameterScalarDescriptor : public TMaterialParameterDescriptor<TFloat32 >
{
public:

	MaterialParameterScalarDescriptor()
	{
		m_parameterType										=	MATERIAL_PARAMETER_TYPE_SCALAR;
	}
};

class MaterialParameterVector3Descriptor : public TMaterialParameterDescriptor< Vector3F >
{
public:

	MaterialParameterVector3Descriptor()
	{
		m_parameterType										=	MATERIAL_PARAMETER_TYPE_VECTOR3;
	}
};


#endif