#ifndef __RENDERER_STRUCT_CONSTANT_BUFFER_H__
#define __RENDERER_STRUCT_CONSTANT_BUFFER_H__

#include "Graphics/RHI/Includes.h"

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
	 * Update the internal data structure
	 */
	void Update( ConstantStruct* a_values )
	{
		memcpy( &m_content , a_values , sizeof( ConstantStruct ) );
		m_isDirty											=	true;
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	/*
	* flush the internal data to the RHI ConstantBuffer
	*/
	void Flush( RhiGraphicContext* a_context )
	{
		// update the Constant Buffer if needed
		if( m_isDirty )
		{
			a_context->UpdateConstantBuffer( m_constantBuffer , &m_content , sizeof( ConstantStruct ) );
			m_isDirty										=	false;
		}
	}
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	/*
	 * Bind the Rhi constant buffer to the context
	 */
	void Bind( RhiGraphicContext* a_context , RhiShaderType a_type , TUint32 a_slot )
	{
		Flush( a_context );

		a_context->SetConstantBuffer( a_type , a_slot , m_constantBuffer );
	}
	//-------------------------------------------------------------------------------------------------

private:

	// The Low level API constantBuffer
	RhiConstantBuffer*	m_constantBuffer;

	// Internal copy of the Struct. allow
	ConstantStruct		m_content;

	// does the ConstantBuffer need to be updated
	TBool				m_isDirty;
};

#endif