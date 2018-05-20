#ifndef __RHI_BASE_BUFFER_DX11_H__
#define __RHI_BASE_BUFFER_DX11_H__


#include <d3d11.h>

#include "../../../Core/CoreMacros.h"

class GraphicDeviceDX11;
class GraphicContextDX11;



class BaseBufferDX11 
{
	friend class GraphicDeviceDX11;

public:

	BaseBufferDX11();
	virtual ~BaseBufferDX11();

	/*
	* Get the DX11 Buffer
	*/
	FORCE_INLINE ID3D11Buffer* GetBuffer()const;

	/*
	* Get the Size of the Vertex Buffer
	*/
	FORCE_INLINE int GetSize()const;


//Methods
protected:

	/*
	*  Set the D3D Buffer
	*/
	void Init( ID3D11Buffer* a_buffer , int a_size );


	virtual void OnInit(){}

// Fields
protected:

	// The Dx Buffer
	ID3D11Buffer*	m_buffer;

	// Size of the Buffer in Bytes
	int				m_size;
};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "BaseBufferDX11.inl"
#endif



#endif