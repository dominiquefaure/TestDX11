#include "StaticGeometry.h"

#ifdef _DEBUG
#include "StaticGeometry.inl"
#endif


//-----------------------------------------------------------------------------------------------
StaticGeometry::StaticGeometry()
{
	m_vertexBuffer											=	NULL;
	m_indexBuffer											=	NULL;

	m_isIndexed												=	false;
	m_indexCount											=	0;
	m_verticeCount											=	0;

}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
StaticGeometry::~StaticGeometry()
{
	SAFE_DELETE( m_vertexBuffer );
	SAFE_DELETE( m_indexBuffer );
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
void StaticGeometry::Init( RhiGraphicDevice* a_device , RhiPrimitiveType a_type , void* a_vertexBuffer, TUint32 a_vertexSize , TUint32 a_vertexCount )
{
	m_primitiveType											=	a_type;
	SetVertexBuffer( a_device , a_vertexSize , a_vertexCount , a_vertexBuffer );
}
//-----------------------------------------------------------------------------------------------
	
//-----------------------------------------------------------------------------------------------
void StaticGeometry::Init( RhiGraphicDevice* a_device , RhiPrimitiveType a_type , void* a_vertexBuffer, TUint32 a_vertexSize , TUint32 a_vertexCount , RhiIndexBufferType a_indexType , void* a_indiceDatas , TUint32 a_indexCount )
{
	m_primitiveType											=	a_type;
	SetVertexBuffer( a_device , a_vertexSize , a_vertexCount , a_vertexBuffer );
	SetIndexBuffer( a_device , a_indexType , a_indexCount , a_indiceDatas );
}
//-----------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------
void StaticGeometry::SetVertexBuffer( RhiGraphicDevice* a_device , TUint32 a_vertexSize , TUint32 a_vertexCount , void* a_vertexBuffer )
{
	// Create the VertexBuffer
	m_vertexBuffer											=	a_device->CreateVertexBuffer( RHI_BUFFER_USAGE_IMMUTABLE , a_vertexSize * a_vertexCount , a_vertexSize , a_vertexBuffer );

	m_verticeCount											=	a_vertexCount;
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
void StaticGeometry::SetIndexBuffer( RhiGraphicDevice* a_device , RhiIndexBufferType a_type , TUint32 a_count , void* a_datas )
{
	// Create the Index Buffer
	m_indexBuffer											=	a_device->CreateIndexBuffer( RHI_BUFFER_USAGE_IMMUTABLE , a_count , a_type , a_datas );

	// save the number of indices
	m_indexCount											=	a_count;
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
void StaticGeometry::Apply( RhiGraphicContext* a_context )
{
	a_context->SetPrimitiveType( m_primitiveType );
	a_context->SetIndexBuffer( m_indexBuffer );
	a_context->SetVertexStream( 0 , m_vertexBuffer );
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
void StaticGeometry::Draw( RhiGraphicContext* a_context )
{
	Apply( a_context );

	if( m_isIndexed )
	{
		a_context->DrawIndexedPrimitive( m_indexCount );
	}
	else
	{
		a_context->DrawPrimitive( m_verticeCount );
	}
}
//-----------------------------------------------------------------------------------------------
