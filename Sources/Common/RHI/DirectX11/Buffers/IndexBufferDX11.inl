#ifndef __RHI_INDEX_BUFFER_DX11_INL__
#define __RHI_INDEX_BUFFER_DX11_INL__


//------------------------------------------------------------------
FORCE_INLINE TUint32 IndexBufferDX11::GetIndexCount()const
{
	return m_indexCount;
}
//------------------------------------------------------------------

//------------------------------------------------------------------
FORCE_INLINE RhiIndexBufferType IndexBufferDX11::GetFormat()const
{
	return m_type;
}
//------------------------------------------------------------------

//------------------------------------------------------------------
FORCE_INLINE DXGI_FORMAT IndexBufferDX11::GetDxFormat()
{
	return m_dxFormat;
}
//------------------------------------------------------------------

#endif