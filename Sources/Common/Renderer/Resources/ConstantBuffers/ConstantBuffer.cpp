#include "ConstantBuffer.h"


//-------------------------------------------------------------------------------------------------
ConstantBuffer::ConstantBuffer( )
{
	m_constantBuffer										=	NULL;
	m_isDirty												=	false;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
ConstantBuffer::~ConstantBuffer()
{
	SAFE_DELETE( m_constantBuffer );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ConstantBuffer::Init( RhiGraphicDevice* a_device , TUint32 a_registerCount )
{
	m_size													=	a_registerCount * sizeof( Vector4F);

	m_internalBuffer.Allocate( a_registerCount );

	m_constantBuffer										=	a_device->CreateConstantBuffer( m_size );

	m_isDirty												=	true;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
Vector4F ConstantBuffer::GetValue( TUint32 a_registerIndex )const
{
	return m_internalBuffer[ a_registerIndex ];
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
TFloat32 ConstantBuffer::GetValue( TUint32 a_registerIndex , TUint32 a_componentIndex )const
{
	assert( a_componentIndex < 4 );
	return m_internalBuffer[ a_registerIndex ][ a_componentIndex ];
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void ConstantBuffer::SetValue( TUint32 a_registerIndex , const Vector4F& a_value )
{
	m_internalBuffer[ a_registerIndex ]						=	a_value;

	m_isDirty												=	true;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ConstantBuffer::SetValue( TUint32 a_registerIndex , TUint32 a_componentIndex , const TFloat32& a_value )
{
	assert( a_componentIndex < 4 );

	m_internalBuffer[ a_registerIndex ][ a_componentIndex ]	=	a_value;
	m_isDirty												=	true;
}
//-------------------------------------------------------------------------------------------------

/*
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
*/
//-------------------------------------------------------------------------------------------------
void ConstantBuffer::Commit( RhiGraphicContext* a_context , RhiShaderType a_type , TUint32 a_slot )
{
	// Update the Rhi buffer is needed
	if( m_isDirty )
	{
		a_context->UpdateConstantBuffer( m_constantBuffer ,  m_internalBuffer.GetBuffer() , m_size );
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
