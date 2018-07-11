#include "BaseBufferDX11.h"


#ifdef _DEBUG
#include "BaseBufferDX11.inl"
#endif


//-------------------------------------------------------------------------------------------------
BaseBufferDX11::BaseBufferDX11()
{
	m_buffer												=	NULL;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
BaseBufferDX11::~BaseBufferDX11()
{
	SAFE_RELEASE( m_buffer );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseBufferDX11::Init( ID3D11Buffer* a_buffer , int a_size )
{
	m_buffer												=	a_buffer;
	m_size													=	a_size;
}
//-------------------------------------------------------------------------------------------------

