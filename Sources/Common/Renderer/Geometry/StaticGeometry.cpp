#include "StaticGeometry.h"

#ifdef _DEBUG
#include "StaticGeometry.inl"
#endif

#include "GeometryDataset.h"


//-------------------------------------------------------------------------------------------------
StaticGeometry::StaticGeometry()
{
	m_indexBuffer											=	NULL;
	m_vertexBuffer											=	NULL;
	m_vertexLayout											=	NULL;

	m_isIndexed												=	false;
	m_indexCount											=	0;
	m_vertexCount											=	0;

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
StaticGeometry::~StaticGeometry()
{
	SAFE_DELETE( m_indexBuffer );
	SAFE_DELETE( m_vertexBuffer );

	m_vertexLayout											=	NULL;
}
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
void StaticGeometry::Apply( RhiGraphicContext* a_context )
{
	a_context->SetIndexBuffer( m_indexBuffer );
	a_context->SetPrimitiveType( m_primitiveType );

	a_context->SetVertexStream( 0 , m_vertexBuffer );

	a_context->SetVertexLayout( m_vertexLayout );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void StaticGeometry::ProcessDraw( RhiGraphicContext* a_context )
{
	if( IsIndexed() )
	{
		a_context->DrawIndexedPrimitive( GetIndiceCount() );
	}
	else
	{
		a_context->DrawPrimitive( GetVertexCount() );
	}
}
//-------------------------------------------------------------------------------------------------


/////////
// Build MEthods
////////



//---------------------------------------------------------------------------------------------------------
void StaticGeometry::Build( RhiGraphicDevice* a_device , const GeometryDataset* a_datas )
{

	m_primitiveType											=	a_datas->GetPrimitiveType();
	m_vertexLayout											=	a_device->GetVertexLayout( a_datas->GetVerticeType() );

	CreateVertexBuffer( a_device , a_datas );

	if( a_datas->IsIndexed() )
	{
		CreateIndexBuffer( a_device , a_datas );
	}

}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void StaticGeometry::CreateVertexBuffer( RhiGraphicDevice* a_device , const GeometryDataset* a_datas )
{
	
	// Save the informations
	m_vertexCount											=	a_datas->GetVerticeCount();
	m_vertexSize											=	a_datas->GetVerticeSize();

	m_vertexBuffer											=	a_device->CreateVertexBuffer( RHI_BUFFER_USAGE_IMMUTABLE ,
																								m_vertexCount * m_vertexSize ,
																								m_vertexSize,
																								a_datas->GetVertexBuffer() );

}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void StaticGeometry::CreateIndexBuffer( RhiGraphicDevice* a_device , const GeometryDataset* a_datas )
{
	// Save the informations
	m_isIndexed												=	true;
	m_indexType												=	a_datas->GetIndexBufferType();
	m_indexCount											=	a_datas->GetIndiceCount();

	m_indexBuffer											=	a_device->CreateIndexBuffer(	RHI_BUFFER_USAGE_IMMUTABLE ,
																								m_indexCount ,
																								m_indexType ,
																								a_datas->GetIndexBuffer() );

}
//---------------------------------------------------------------------------------------------------------

