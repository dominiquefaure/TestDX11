#include "IndexBufferDX11.h"


#ifdef _DEBUG
#include "IndexBufferDX11.inl"
#endif

//---------------------------------------------------------------
IndexBufferDX11::IndexBufferDX11()
{
	m_dxFormat												=	DXGI_FORMAT_R32_UINT;
}
//---------------------------------------------------------------

//---------------------------------------------------------------
IndexBufferDX11::~IndexBufferDX11()
{

}
//---------------------------------------------------------------

//---------------------------------------------------------------
void IndexBufferDX11::SetProperties( RhiIndexBufferType a_type , TUint32 a_count )
{
	m_type													=	a_type;

	switch( a_type )
	{
		case INDEX_BUFFER_TYPE_16:
			m_dxFormat										=	DXGI_FORMAT_R16_UINT;
		break;

		case INDEX_BUFFER_TYPE_32:
			m_dxFormat										=	DXGI_FORMAT_R32_UINT;
		break;
	}

	m_indexCount											=	a_count;
}
//---------------------------------------------------------------
