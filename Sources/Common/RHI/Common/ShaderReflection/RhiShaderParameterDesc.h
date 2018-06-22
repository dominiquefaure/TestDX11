#ifndef __RHI_SHADER_REFLECTION_PARAMETER_DESC_H__
#define __RHI_SHADER_REFLECTION_PARAMETER_DESC_H__

#include "../../../Core/Base/Includes.h"
#include "../../../Core/CoreMacros.h"

#define SHADER_PARAMETER_NAME_MAX_SIZE	28


class RhiShaderParameterDesc
{

public:

	RhiShaderParameterDesc();
	~RhiShaderParameterDesc();

	/*
	 * Get the name of this Parameter
	 */
	FORCE_INLINE const char* GetName()const;

	/*
	 * Get the ConstantBuffer slot to use
	 */
	FORCE_INLINE TUint8 GetBufferSlot()const;

	/*
	 * Get the Start Offset i the Constant Buffer
	 */
	FORCE_INLINE TUint16 GetBufferOffset()const;

	/*
	 * Get the umber of Bytes required
	 */
	FORCE_INLINE TUint8 GetByteCount()const;

	/*
	 * Set the Parameter Properties
	 */
	void Set( const char* a_name , TUint8 a_slot , TUint16 a_offset , TUint8 a_byteCount );

private:

	char	m_name[ SHADER_PARAMETER_NAME_MAX_SIZE ];

	// constant Buffer slot
	TUint8	m_bufferSlot;

	// NUmber of Bytes used by this parameter
	TUint8	m_byteCount;

	// start offset in the Constant buffer
	TUint16	m_bufferOffset;

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "RhiShaderParameterDesc.inl"
#endif



#endif