#ifndef __RHI_BASE_BUFFER_DX11_INL__
#define __RHI_BASE_BUFFER_DX11_INL__



//-------------------------------------------------------------------
/*
* Get the DX11 Buffer
*/
FORCE_INLINE ID3D11Buffer* BaseBufferDX11::GetBuffer()const
{
	return m_buffer;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
/*
* Get the Size of the Vertex Buffer
*/
FORCE_INLINE int BaseBufferDX11::GetSize()const
{
	return m_size;
}
//-------------------------------------------------------------------


#endif
