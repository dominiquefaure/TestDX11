#include "RhiShaderParameterDesc.h"

#include "../../../../Core/CoreIncludes.h"

#ifdef _DEBUG
#include "RhiShaderParameterDesc.inl"
#endif


//---------------------------------------------------------------------------------------------------------
RhiShaderParameterDesc::RhiShaderParameterDesc()
{
	m_name[ 0 ]												=	'\0';
	m_bufferSlot											=	0;
	m_bufferOffset											=	0;
	m_byteCount												=	0;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
RhiShaderParameterDesc::~RhiShaderParameterDesc()
{
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void RhiShaderParameterDesc::Set( const char* a_name , TUint8 a_slot , TUint16 a_offset , TUint8 a_byteCount )
{
	assert( a_name != NULL );
	assert( strlen( a_name) < 32 );

	strcpy_s( m_name , a_name );

	m_bufferSlot											=	a_slot;
	m_bufferOffset											=	a_offset;
	m_byteCount												=	a_byteCount;
}
//---------------------------------------------------------------------------------------------------------
