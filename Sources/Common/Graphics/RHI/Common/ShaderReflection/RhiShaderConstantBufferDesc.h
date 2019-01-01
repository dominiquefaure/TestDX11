#ifndef __RHI_SHADER_REFLECTION_CONSTANT_BUFFER_DESC_H__
#define __RHI_SHADER_REFLECTION_CONSTANT_BUFFER_DESC_H__

#include "../../../../Core/Base/Includes.h"
#include "../../../../Core/CoreMacros.h"


#include "RhiShaderParameterDesc.h"

#define SHADER_CONSTANT_BUFFER_NAME_MAX_SIZE	32

class RhiShaderConstantBufferDesc
{
	
public:

	RhiShaderConstantBufferDesc();
	~RhiShaderConstantBufferDesc();

	/*
	 * Get the name of the ConstantBuffer
	 */
	FORCE_INLINE const char* GetName()const;

	/*
	 * Get the ConstantBuffer slot to use
	 */
	FORCE_INLINE TUint8 GetSlot()const;

	/*
	 * Get the Size of the Constant Buffer
	 */
	FORCE_INLINE TUint32 GetSize()const;

	/*
	 * Get the number of Parameter defined in this Constant Buffer
	 */
	FORCE_INLINE TUint8 GetParameterCount()const;

	/*
	 * Get the ieme parameter defined for the ConstantBuffer
	 */
	FORCE_INLINE const RhiShaderParameterDesc* GetParameterDesc( TUint32 a_index )const;


	void Init( TUint8 a_registerSlot , const char* a_name , TUint32 a_size , TUint8 a_parameterCount );


	void SetParameterDesc( TUint8 a_index , const char* a_name , TUint16 a_startOffset , TUint8 a_byteCount );

private:

	char					m_name[ SHADER_CONSTANT_BUFFER_NAME_MAX_SIZE ];

	// Size of the ConstantBuffer;
	TUint32					m_size;

	// Slot index the ConstantBuffer is set
	TUint8					m_slotIndex;

	// number of Parameters defined for the ConstantBuffer
	TUint8					m_parameterCount;

	// Array that store the different parameters defined for this CosntantBuffer
	RhiShaderParameterDesc*	m_parameterList;

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "RhiShaderConstantBufferDesc.inl"
#endif



#endif