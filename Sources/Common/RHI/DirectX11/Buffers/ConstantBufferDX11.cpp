#include "ConstantBufferDX11.h"

//-------------------------------------------------------------------------------------------------
ConstantBufferDX11::ConstantBufferDX11()
{
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
ConstantBufferDX11::~ConstantBufferDX11()
{

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void ConstantBufferDX11::Update( GraphicContextDX11* a_context , void* a_datas , TUint32 a_size )
{
	// Try to map the REsource
	void* t_bufferDatas										=	Map( a_context , D3D11_MAP_WRITE_DISCARD );


	//if succeed, update the buffer content
	if( t_bufferDatas != NULL )
	{
		// copy the Datas
		memcpy( t_bufferDatas , a_datas , a_size );
	
		// unmap the resource
		Unmap( a_context );
	}

}
//-------------------------------------------------------------------------------------------------
