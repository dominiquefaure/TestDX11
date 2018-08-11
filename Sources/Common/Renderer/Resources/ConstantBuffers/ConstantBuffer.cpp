#include "ConstantBuffer.h"


//-------------------------------------------------------------------------------------------------
ConstantBuffer::ConstantBuffer( )
{
	m_internalBuffer										=	NULL;
	m_constantBuffer										=	NULL;
	m_isDirty												=	false;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
ConstantBuffer::~ConstantBuffer()
{
	SAFE_DELETE_ARRAY( m_internalBuffer );
	SAFE_DELETE( m_constantBuffer );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ConstantBuffer::Init( RhiGraphicDevice* a_device , TUint32 a_size )
{
	m_size													=	a_size;
	m_internalBuffer										=	new TUint8[ m_size ];
	m_constantBuffer										=	a_device->CreateConstantBuffer( m_size );

	for( int i = 0 ; i < m_size ; i ++ )
	{
		m_internalBuffer[ i ]								=	0;
	}
	m_isDirty												=	true;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ConstantBuffer::Update( TUint32 a_offset , TUint32 a_byteCount , const void* a_value )
{
	assert( ( a_offset + a_byteCount) <= m_size );
	memcpy( m_internalBuffer + a_offset , a_value , a_byteCount );

	m_isDirty												=	true;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ConstantBuffer::Update( const RhiShaderParameterDesc* a_param , const void* a_value )
{
	assert( ( a_param->GetBufferOffset() + a_param->GetByteCount() ) <= m_size );
	memcpy( m_internalBuffer + a_param->GetBufferOffset() , a_value , a_param->GetByteCount() );

	m_isDirty												=	true;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ConstantBuffer::Commit( RhiGraphicContext* a_context , RhiShaderType a_type , TUint32 a_slot )
{
	// Update the Rhi buffer is needed
	if( m_isDirty )
	{
		a_context->UpdateConstantBuffer( m_constantBuffer ,  m_internalBuffer , m_size );
	}


	//reset the Flag
	m_isDirty												=	false;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ConstantBuffer::Bind( RhiGraphicContext* a_context , RhiShaderType a_type , TUint32 a_slot )
{
	if( m_isDirty )
	{
		Commit( a_context , a_type , a_slot );
	}

	// set the Buffer as the active one for the given Shader- Slot
	a_context->SetConstantBuffer( a_type , a_slot , m_constantBuffer );

}
//-------------------------------------------------------------------------------------------------
