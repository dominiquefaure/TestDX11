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
	m_isDirty												=	false;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ConstantBufferDX11::Update( TUint8* a_datas , TUint32 a_offset , TUint32 a_size )
{
	assert( ( a_offset + a_size) <= m_size );
	memcpy( m_cpuBuffer + a_offset , a_datas , a_size );

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

