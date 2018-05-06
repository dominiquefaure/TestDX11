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



///////////////
// Loading Methods
//////////////

//-----------------------------------------------------------------------------------------------
void StaticGeometry::LoadFromJSon( RhiGraphicDevice* a_device , const char* a_path )
{
	// Load the Json File
	JsonDocument t_document;
	t_document.Load( a_path );

	LoadFromJSon( a_device , t_document.GetRootNode() );
}
//-----------------------------------------------------------------------------------------------
			
//-----------------------------------------------------------------------------------------------
void StaticGeometry::LoadFromJSon( RhiGraphicDevice* a_device , JSonNode& a_rootNode )
{
	TryLoadVertexBuffer( a_device , a_rootNode );

	TryLoadIndexBuffer( a_device , a_rootNode );

	m_primitiveType											=	(RhiPrimitiveType)a_rootNode.GetInt64Property( "PrimitiveType" , RHI_PRIMITIVE_TYPE_TRIANGLE_LIST );
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
TBool StaticGeometry::TryLoadVertexBuffer( RhiGraphicDevice* a_device , JSonNode& a_rootNode )
{
	// check if there is an Index buffer property
	JSonProperty t_vertexBufferProperty						=	a_rootNode.GetProperty( "VertexBuffer" );

	// if the property is valid
	if( t_vertexBufferProperty.GetType() ==  JSON_PROPERTY_TYPE_NODE )
	{
		// Get the JSon Object
		JSonNode t_obj										=	t_vertexBufferProperty.GetJSonObject();

		LoadVertexBufferContent( a_device , t_obj );
	}
	else
	{
		return false;
	}

	return true;
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
void StaticGeometry::LoadVertexBufferContent( RhiGraphicDevice* a_device , JSonNode& a_vertexBufferNode )
{
	// get the number of Vertex
	TUint64 t_vertexCount									=	a_vertexBufferNode.GetInt64Property( "VertexCount" );

	// get the Size in bytes of 1 vertice
	TUint64 t_vertexSize									=	a_vertexBufferNode.GetInt64Property( "VertexSize" );

	// Get the Property that store the vertex buffer datas
	JSonProperty t_vertices									=	a_vertexBufferNode.GetProperty( "Datas" );
	if( t_vertices.IsArray() )
	{
		int t_size											=	t_vertices.GetArraySize();
		float* t_vertexBuffer								=	new float[ t_size ];

		// read the Datas
		t_vertices.GetFloatArray( t_vertexBuffer , t_size );

		SetVertexBuffer( a_device , t_vertexSize , t_vertexCount , t_vertexBuffer );

		delete[]t_vertexBuffer;
	}
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
void StaticGeometry::TryLoadIndexBuffer( RhiGraphicDevice* a_device , JSonNode& a_rootNode )
{
	// check if there is an Index buffer property
	JSonProperty t_indexBufferProperty						=	a_rootNode.GetProperty( "IndexBuffer" );

	// if the property is valid
	if( t_indexBufferProperty.GetType() ==  JSON_PROPERTY_TYPE_NODE )
	{
		// Get the JSon Object
		JSonNode t_obj										=	t_indexBufferProperty.GetJSonObject();

		LoadIndexBufferContent( a_device , t_obj );
	}
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
void StaticGeometry::LoadIndexBufferContent( RhiGraphicDevice* a_device , JSonNode& a_indexBufferNode )
{
	// we have an index buffer
	m_isIndexed												=	true;

	// Get the number of Index
	TUint64 t_indexCount									=	a_indexBufferNode.GetInt64Property( "IndexCount" );
	int16_t* t_indexBuffer									=	new int16_t[ t_indexCount ];

	// Get the Property that store the Index buffer datas
	JSonProperty t_datas									=	a_indexBufferNode.GetProperty( "Datas" );
	if( t_datas.IsArray() )
	{
		// read the Datas
		t_datas.GetShortArray( t_indexBuffer , t_indexCount );
	}

	RhiIndexBufferType t_type								=	INDEX_BUFFER_TYPE_16;

	if( t_indexCount > 65535 )
	{
		t_type												=	INDEX_BUFFER_TYPE_32;
	}

	SetIndexBuffer( a_device , t_type , t_indexCount , t_indexBuffer );

	delete[] t_indexBuffer;

}
//-----------------------------------------------------------------------------------------------
