#include "RhiShaderConstantBufferDesc.h"

#include "../../../Core/CoreIncludes.h"

#ifdef _DEBUG
#include "RhiShaderConstantBufferDesc.inl"
#endif

//---------------------------------------------------------------------------------------------------------
RhiShaderConstantBufferDesc::RhiShaderConstantBufferDesc()
{
	m_name[ 0 ]												=	'\0';

	m_parameterList											=	nullptr;

	m_slotIndex												=	0;
	m_parameterCount										=	0;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
RhiShaderConstantBufferDesc::~RhiShaderConstantBufferDesc()
{
	SAFE_DELETE_ARRAY( m_parameterList );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void RhiShaderConstantBufferDesc::Init( TUint8 a_registerSlot , const char* a_name , TUint32 a_size , TUint8 a_parameterCount )
{
	assert( a_name != nullptr );
	assert( strlen( a_name) < 32 );

	strcpy_s( m_name , a_name );

	m_slotIndex												=	a_registerSlot;
	m_size													=	a_size;

	m_parameterCount										=	a_parameterCount;
	m_parameterList											=	new RhiShaderParameterDesc[ a_parameterCount ];
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void RhiShaderConstantBufferDesc::SetParameterDesc( TUint8 a_index , const char* a_name , TUint16 a_startOffset , TUint8 a_byteCount )
{
	m_parameterList[ a_index ].Set( a_name , m_slotIndex , a_startOffset , a_byteCount );
}
//---------------------------------------------------------------------------------------------------------
