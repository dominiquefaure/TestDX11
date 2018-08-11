#ifndef __RENDERER_BASE_MATERIAL_PARAMETER_H__
#define __RENDERER_BASE_MATERIAL_PARAMETER_H__

#include "Core/CoreIncludes.h"
#include "../ConstantBuffers/Includes.h"

/*
* Base Class for the Material Parameters types
*/
class BaseMaterialParameter
{
public:
	enum ParameterType
	{
		SCALAR_PARAMETER,
		VECTOR_PARAMETER
	};

public:
	
	BaseMaterialParameter();
	~BaseMaterialParameter();

	/*
	* Get the Type of parameter
	*/
	FORCE_INLINE ParameterType GetType()const;

	/*
	* Get the Parameter name
	*/
	FORCE_INLINE const std::string& GetName()const;

	/*
	* get the Parameter Start offset
	*/
	FORCE_INLINE TUint16 GetStartOffset()const;

	/*
	* Get the number of bytes used by this parameter
	*/
	FORCE_INLINE TUint16 Getbytecount()const;

	/*
	* Initialize the Parameter
	*/
	void Init( const std::string& a_name , TUint16 a_startOffset );


protected:

	void SetType( ParameterType a_type  );

protected:

	ParameterType	m_type;

	// Name of the Parameter
	std::string		m_name;

	// Start ofset of the parameter inside the Constant Buffer
	TUint16			m_startOffset;

	//Number of Bytes
	TUint16			m_byteCount;
};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "BaseMaterialParameter.inl"
#endif


#endif