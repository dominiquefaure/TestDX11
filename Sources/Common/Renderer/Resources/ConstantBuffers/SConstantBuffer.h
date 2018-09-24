#ifndef __RENDERER_STRUCT_CONSTANT_BUFFER_H__
#define __RENDERER_STRUCT_CONSTANT_BUFFER_H__

#include "RHI/Includes.h"

/*
 */
template<typename ConstantStruct>
class SConstantBuffer
{
public:

	//-------------------------------------------------------------------------------------------------
	SConstantBuffer( )
	{
		m_constantBuffer									=	nullptr;
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	~SConstantBuffer()
	{
		SAFE_DELETE( m_constantBuffer );
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	const RhiConstantBuffer* GetRhiConstantBuffer()const
	{
		return m_constantBuffer;
	}
	//-------------------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------------------
	/*
	 * Create the Contant Buffer
	 */
	void Init( RhiGraphicDevice* a_device )
	{
		m_constantBuffer									=	a_device->CreateConstantBuffer( sizeof( ConstantStruct ) );
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	/*
	 * Update the Rhi Constant Buffer with struct data
	 */
	void Update( RhiGraphicContext* a_context , ConstantStruct* a_values )
	{
		a_context->UpdateConstantBuffer( m_constantBuffer , a_values , sizeof( ConstantStruct ) );
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	/*
	 * Bind the Rhi constant buffer to the context
	 */
	void Bind( RhiGraphicContext* a_context , RhiShaderType a_type , TUint32 a_slot )
	{
		a_context->SetConstantBuffer( a_type , a_slot , m_constantBuffer );
	}
	//-------------------------------------------------------------------------------------------------

private:

	// The Low level API constantBuffer
	RhiConstantBuffer*	m_constantBuffer;

};

#endif