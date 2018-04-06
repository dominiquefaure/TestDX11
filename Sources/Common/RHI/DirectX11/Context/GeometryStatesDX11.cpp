#include "GeometryStatesDX11.h"


D3D_PRIMITIVE_TOPOLOGY g_geometryTopologyDX11[]=
{
	D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
	D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
	D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
	D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
};


//---------------------------------------------------------------------------------------------------------
GeometryStatesDX11::GeometryStatesDX11()
{
	Reset();
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
GeometryStatesDX11::~GeometryStatesDX11()
{
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryStatesDX11::Reset()
{
	for( int i = 0 ; i < MAX_VERTEX_STREAM_DX11 ; i ++ )
	{
		m_vertexStreams[ i ]								=	NULL;
		m_vertexStrides[ i ]								=	0;
		m_vertexOffsets[ i ]								=	0;
	}

	m_streamsDirtyFlags										=	0;

	m_primitiveType											=	RHI_PRIMITIVE_TYPE_INVALID;

	m_dirtyFlag												=	0;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryStatesDX11::SetVertexStream( TUint32 a_index , ID3D11Buffer* a_streamBuffer ,  TUint32 a_stride , TUint32 a_startOffset )
{
	// if not the same informations as the current one
	if( a_streamBuffer != m_vertexStreams[ a_index ] ||  a_stride != m_vertexStrides[ a_index ] || a_startOffset != m_vertexOffsets[ a_index ] )
	{
		 m_vertexStreams[ a_index ]							=	a_streamBuffer;
		 m_vertexStrides[ a_index ]							=	a_stride;
		 m_vertexOffsets[ a_index ]							=	a_startOffset;

		 if( a_streamBuffer != NULL )
		 {
			 m_streamsDirtyFlags							|= 1 << a_index;
		 }
	}
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryStatesDX11::SetIndexBuffer( ID3D11Buffer* a_indexBuffer , DXGI_FORMAT a_format , UINT a_offset )
{
	if( ( a_indexBuffer != m_indexBuffer ) || ( a_format != m_indexFormat ) || ( a_offset != m_indexOffset ) )
	{
		m_indexBuffer										=	a_indexBuffer;
		m_indexFormat										=	a_format;
		m_indexOffset										=	a_offset;

		m_dirtyFlag											|=	DIRTY_FLAG_INDEX_BUFFER;
	}
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryStatesDX11::SetPrimitiveType( RhiPrimitiveType a_type )
{
	if( a_type != m_primitiveType )
	{
		m_primitiveType										=	a_type;

		m_dirtyFlag											|=	DIRTY_FLAG_PRIMITIVE_TYPE;
	}
}
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
void GeometryStatesDX11::Commit( ID3D11DeviceContext* a_context )
{
	if( ( m_dirtyFlag & DIRTY_FLAG_PRIMITIVE_TYPE ) == DIRTY_FLAG_PRIMITIVE_TYPE )
	{
		D3D_PRIMITIVE_TOPOLOGY t_topology					=	g_geometryTopologyDX11[ m_primitiveType ];
		a_context->IASetPrimitiveTopology( t_topology );
	}

	// if the vetex streams have changed
	if( m_streamsDirtyFlags != 0 )
	{
		for( int i = 0 ; i < MAX_VERTEX_STREAM_DX11 ; i ++ )
		{
			if( ( m_streamsDirtyFlags & ( 1 << i ) )!= 0 )
			{
				a_context->IASetVertexBuffers( i, 1, &m_vertexStreams[ i ]  , &m_vertexStrides[ i ] , &m_vertexOffsets[ i ] );
			}
		}

		m_streamsDirtyFlags									=	0;
	}

	if( ( m_dirtyFlag & DIRTY_FLAG_INDEX_BUFFER ) == DIRTY_FLAG_INDEX_BUFFER )
	{
		a_context->IASetIndexBuffer( m_indexBuffer , m_indexFormat , m_indexOffset );
	}

	// reset the Dirty Flag
	m_dirtyFlag												=	0;
}
//---------------------------------------------------------------------------------------------------------
