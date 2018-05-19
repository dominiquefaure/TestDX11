#include "BaseBufferDX11.h"
#include "../Context/GraphicContextDX11.h"

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

//-------------------------------------------------------------------------------------------------
void* BaseBufferDX11::Map( GraphicContextDX11* a_context , D3D11_MAP a_mapType , D3D11_MAP_FLAG a_flag )
{
	void* t_bufferDatas;
	int t_rowPitch;
	int t_depthPitch;

	//Try to map the resource
	if( a_context->MapResource( m_buffer , 0 , t_bufferDatas , t_rowPitch , t_depthPitch , a_mapType , a_flag ) )
	{
		return t_bufferDatas;
	}

	return NULL;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseBufferDX11::Unmap( GraphicContextDX11* a_context )
{
	a_context->UnmapResource( m_buffer , 0 );
}
//-------------------------------------------------------------------------------------------------
