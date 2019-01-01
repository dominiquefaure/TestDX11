#ifndef __RHI_INDEX_BUFFER_DX11_H__
#define __RHI_INDEX_BUFFER_DX11_H__

#include <d3d11.h>
#include "BaseBufferDX11.h"

#include "../../../../Core/CoreIncludes.h"

#include "../../RhiEnums.h"
#include "../../Common/Enums/Includes.h"


class GraphicDeviceDX11;

class IndexBufferDX11 : public BaseBufferDX11
{
	friend class GraphicDeviceDX11;

public:
	IndexBufferDX11();
	virtual ~IndexBufferDX11();


	/*
	* Get the number of Index present in the IndexBuffer
	*/
	FORCE_INLINE TUint32 GetIndexCount()const;

	/*
	* Get the Format of the Index Buffer
	*/
	FORCE_INLINE RhiIndexBufferType GetFormat()const;

	/*
	* Get the DX Format of the Buffer
	*/
	FORCE_INLINE DXGI_FORMAT GetDxFormat();

protected:

	/*
	* Set the Index buffer specific properties
	*/
	void SetProperties( RhiIndexBufferType a_type , TUint32 a_count );


private:

	RhiIndexBufferType	m_type;
	DXGI_FORMAT			m_dxFormat;

	TUint32				m_indexCount;


};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "IndexBufferDX11.inl"
#endif


#endif