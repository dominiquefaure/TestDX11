#ifndef __RHI_VERTEX_BUFFER_DX11_H__
#define __RHI_VERTEX_BUFFER_DX11_H__

#include <d3d11.h>
#include "BaseBufferDX11.h"


class GraphicDeviceDX11;

class VertexBufferDX11 : public BaseBufferDX11
{
	friend class GraphicDeviceDX11;

public:
	VertexBufferDX11();
	virtual ~VertexBufferDX11();

	/*
	* Get the Stride of a Vertex
	*/
	FORCE_INLINE int GetStride()const;

protected:

	/*
	* Set the Size in Bytes used for a Vertex inside the Buffer
	*/
	void SetStride( int a_stride );

private:

	// Size of a Vertex
	int	m_stride;

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "VertexBufferDX11.inl"
#endif


#endif