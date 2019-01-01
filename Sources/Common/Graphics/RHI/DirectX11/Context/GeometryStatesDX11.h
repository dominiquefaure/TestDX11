#ifndef __RHI_GEOMETRY_STATES_DX11_H__
#define __RHI_GEOMETRY_STATES_DX11_H__

// put the number max of stream allowed
#define MAX_VERTEX_STREAM_DX11	8

#include <d3d11.h>

#include "../../../../Core/CoreIncludes.h"

#include "../../RhiEnums.h"

#include "../../Common/Enums/Includes.h"

class GeometryStatesDX11
{

	enum dirtyFlags
	{
		DIRTY_FLAG_PRIMITIVE_TYPE	=	1,
		DIRTY_FLAG_INDEX_BUFFER		=	2
	};

public:

	GeometryStatesDX11();
	~GeometryStatesDX11();

	/*
	* Reset all the values, to be called at beginning of the Context record
	*/
	void Reset();
	

	/*
	* Set one off the Vertex Streams to use
	*
	* @param a_index		:	Index the Stream will be binded at
	* @param a_streamBuffer	:	The Stream storing vertices information's
	* @param a_stride		:	Stride of a vertex
	* @param a_startOffset	:	Start offset in the Stream
	*/
	void SetVertexStream( TUint32 a_index , ID3D11Buffer* a_streamBuffer , TUint32 a_stride , TUint32 a_startOffset );

	/*
	 * Set the Index Buffer to use
	 */
	void SetIndexBuffer( ID3D11Buffer* a_indexBuffer , DXGI_FORMAT a_format , UINT a_offset );

	/*
	* Set the Type of primitive the Vertex Streams represent
	*
	* @param a_type		The Type of primitive to use for next drawing
	*/
	void SetPrimitiveType( RhiPrimitiveType a_type );



	/*
	* commit all the updates made since last call
	*/
	void Commit( ID3D11DeviceContext* a_context );


private:

	// store informations' for the vertex streams to use
	ID3D11Buffer*		m_vertexStreams[ MAX_VERTEX_STREAM_DX11 ];
	UINT				m_vertexStrides[ MAX_VERTEX_STREAM_DX11 ];
	UINT				m_vertexOffsets[ MAX_VERTEX_STREAM_DX11 ];

	TUint32				m_streamsDirtyFlags;


	ID3D11Buffer*		m_indexBuffer;
	DXGI_FORMAT			m_indexFormat;
	UINT				m_indexOffset;

	TUint32				m_dirtyFlag;

	RhiPrimitiveType	m_primitiveType;

};


#endif