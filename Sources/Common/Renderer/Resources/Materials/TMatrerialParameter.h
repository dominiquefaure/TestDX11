#ifndef __RENDERER_BASE_TMATERIAL_PARAMETER_H__
#define __RENDERER_BASE_TMATERIAL_PARAMETER_H__

#include "Core/CoreIncludes.h"
#include "../ConstantBuffers/Includes.h"

#include "BaseMaterialParameter.h"


template<typename T> class TMaterialParameter : public BaseMaterialParameter
{
public:

	//-------------------------------------------------------------------------------------------------
	inline T GetValue()const
	{
		return m_value;
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	inline void SetValue( T a_newValue )
	{
		m_value												=	a_newValue;
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	inline void Apply( ConstantBuffer* a_buffer )
	{
		a_buffer->Update( m_startOffset , m_byteCount , &m_value );
	}
	//-------------------------------------------------------------------------------------------------

protected:

	// the Parameter value
	T	m_value;
};

#endif