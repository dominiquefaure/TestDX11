#include "ConstantBufferDX11.h"

#include "../Context/GraphicContextDX11.h"


//-------------------------------------------------------------------------------------------------
ConstantBufferDX11::ConstantBufferDX11()
{
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
ConstantBufferDX11::~ConstantBufferDX11()
{
	SAFE_DELETE_ARRAY( m_cpuBuffer );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ConstantBufferDX11::OnInit()
{
	m_cpuBuffer												=	new TUint8[ m_size ];
	memset( m_cpuBuffer , 0 , m_size );

	m_isDirty												=	false;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ConstantBufferDX11::Update( TUint32 a_index , TUint32 a_byteCount , const void* a_value )
{
	assert( ( a_index + a_byteCount) <= m_size );
	memcpy( m_cpuBuffer + a_index , a_value , a_byteCount );

	m_isDirty												=	true;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ConstantBufferDX11::Commit( GraphicContextDX11* a_context , RhiShaderType a_type , TUint32 a_slot )
{
	// Updat eth GPU buffer is needed
	if( m_isDirty )
	{
		a_context->UpdateConstantBuffer( m_buffer ,  m_cpuBuffer , m_size );
	}

	// set the Buffer as the active one for the given Shader- Slot
	a_context->SetConstantBuffer( a_type , a_slot , m_buffer );

	//reset the Flag
	m_isDirty												=	false;
}
//-------------------------------------------------------------------------------------------------

