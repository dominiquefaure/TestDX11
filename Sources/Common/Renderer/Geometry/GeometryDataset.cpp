#include "GeometryDataset.h"

#ifdef _DEBUG
#include "GeometryDataset.inl"
#endif

//---------------------------------------------------------------------------------------------------------
GeometryDataset::GeometryDataset()
{
	m_isIndexed												=	false;

	m_indexCount											=	0;
	m_vertexCount											=	0;
	m_vertexSize											=	0;

	m_primitiveType											=	RHI_PRIMITIVE_TYPE_INVALID;
	m_indexType												=	INDEX_BUFFER_TYPE_INVALID;
	m_vertexLayoutType										=	RHI_VERTEX_LAYOUT_INVALID;

	m_indexBuffer16											=	nullptr;
	m_indexBuffer32											=	nullptr;
	m_vertexBuffer											=	nullptr;
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
GeometryDataset::~GeometryDataset()
{
	SAFE_DELETE_ARRAY( m_indexBuffer16 );
	SAFE_DELETE_ARRAY( m_indexBuffer32 );
	SAFE_DELETE_ARRAY( m_vertexBuffer );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryDataset::LoadFromJSon(const char* a_filePath )
{
	// Load the Json File
	JsonDocument t_document;
	t_document.Load(a_filePath);

	LoadFromJSon( t_document.GetRootNode() );

}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryDataset::LoadFromJSon( JSonNode& a_rootNode )
{
	// check if there is a Vertex buffer property
	JSonProperty t_vertexBufferProprty						=	a_rootNode.GetProperty( "VertexBuffer" );


	// check the property is valid
	if( t_vertexBufferProprty.GetType() ==  JSON_PROPERTY_TYPE_NODE )
	{
		// Get the JSon Object
		JSonNode t_obj										=	t_vertexBufferProprty.GetJSonObject();

		LoadVertexBuffer( t_obj );
	}
	else
	{
		// invalid geometry
		assert( false );
		return;
	}

	// check if there is an Index buffer property
	JSonProperty t_indexBufferProprty						=	a_rootNode.GetProperty( "IndexBuffer" );

	// if the property is valid
	if( t_indexBufferProprty.GetType() ==  JSON_PROPERTY_TYPE_NODE )
	{
		// Get the JSon Object
		JSonNode t_obj										=	t_indexBufferProprty.GetJSonObject();

		LoadIndexBuffer( t_obj );
	}

	// get the primitive type. if not specified use Triangle List
	m_primitiveType											=	(RhiPrimitiveType)a_rootNode.GetInt64Property("PrimitiveType" , (int) RHI_PRIMITIVE_TYPE_TRIANGLE_LIST );

	// Get the Layout 
	m_vertexLayoutType										=	(RhiVertexLayoutType)a_rootNode.GetInt64Property( "VertexLayout" );
}
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
void GeometryDataset::LoadIndexBuffer( JSonNode& a_indexBufferNode )
{
	// we have an index buffer
	m_isIndexed												=	true;

	// Get the number of Index
	m_indexCount											=	(TUint32)a_indexBufferNode.GetInt64Property( "IndexCount" );

	// Get the Property that store the Index buffer datas
	JSonProperty t_datas									=	a_indexBufferNode.GetProperty( "Datas" );


	if( t_datas.IsArray() )
	{
		if( m_indexCount < 65535 )
		{
			m_indexType										=	INDEX_BUFFER_TYPE_16;

			// Allocate the Index buffer
			m_indexBuffer16									=	new TUint16[ m_indexCount ];

			// read the Datas
			t_datas.GetShortArray( (int16_t*)m_indexBuffer16 , m_indexCount );
		}
		else
		{
			m_indexType										=	INDEX_BUFFER_TYPE_32;

			// Allocate the Index buffer
			m_indexBuffer32									=	new TUint32[ m_indexCount ];
			
			// read the Datas
			t_datas.GetInt32Array( (int*)m_indexBuffer32 , m_indexCount );

		}
	}
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryDataset::LoadVertexBuffer( JSonNode& a_vertexBufferNode )
{
	// Get the size of 1 vertex
	m_vertexSize											=	(TUint32)a_vertexBufferNode.GetInt64Property( "VertexSize" );

	// Get the number of Vertex
	m_vertexCount											=	(TUint32)a_vertexBufferNode.GetInt64Property( "VertexCount" );

	// Get the Property that store the Vertex buffer datas
	JSonProperty t_vertices									=	a_vertexBufferNode.GetProperty( "Datas" );
	if( t_vertices.IsArray() )
	{
		int t_size											=	t_vertices.GetArraySize();

		// allocate the VertexBuffer
		m_vertexBuffer										=	new float[ t_size ];

		// read the Datas
		t_vertices.GetFloatArray( m_vertexBuffer , t_size );
	}
}
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
void GeometryDataset::CreateIndexBuffer( TUint32 a_size , TUint32* a_datas )
{
	// use triangle list by default
	m_primitiveType											=	RHI_PRIMITIVE_TYPE_TRIANGLE_LIST;
	m_isIndexed												=	true;
	m_indexCount											=	a_size;
	if( m_indexCount < 65535 )
	{
		m_indexType											=	INDEX_BUFFER_TYPE_16;

		// Allocate the Index buffer
		m_indexBuffer16										=	new TUint16[ m_indexCount ];

		if( a_datas != NULL )
		{
			for( int i = 0 ; i < a_size ; i ++ )
			{
				m_indexBuffer16[ i ]						=	(TUint16)a_datas[ i ];
			}
		}
		else
		{
			memset( m_indexBuffer16 , 0 , sizeof(TUint16) * m_indexCount );
		}
	}
	else
	{
		m_indexType											=	INDEX_BUFFER_TYPE_32;

		// Allocate the Index buffer
		m_indexBuffer32										=	new TUint32[ m_indexCount ];

		if( a_datas != NULL )
		{
			memcpy( m_indexBuffer32 , a_datas , sizeof(TUint32) * m_indexCount );
		}
		else
		{
			memset( m_indexBuffer32 , 0 , sizeof(TUint32) * m_indexCount );
		}
	}
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryDataset::SetIndiceAt( TUint32 a_index , TUint32 a_indice )
{
	if( m_indexType == INDEX_BUFFER_TYPE_16 )
	{
		m_indexBuffer16[ a_index ]							=	(TUint16)a_indice;
	}
	else
	{
		m_indexBuffer32[ a_index ]							=	a_indice;
	}
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryDataset::CreateVertexBuffer( RhiVertexLayoutType a_layout , TUint32 a_vetexSize , TUint32 a_vertexCount , TFloat32* a_initialDatas )
{
	m_vertexLayoutType										=	a_layout;
	m_vertexSize											=	a_vetexSize;
	m_vertexCount											=	a_vertexCount;

	m_vertexBuffer											=	new float[ m_vertexCount * m_vertexSize ];

	if( a_initialDatas != NULL )
	{
		memcpy( m_vertexBuffer , a_initialDatas , m_vertexCount * m_vertexSize );
	}
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryDataset::CreateVertexBuffer( RhiVertexLayout* a_layout , TUint32 a_vertexCount , TFloat32* a_initialDatas )
{
	m_vertexLayoutType										=	a_layout->GetLayoutType();
	m_vertexSize											=	a_layout->GetVertexSize();
	m_vertexCount											=	a_vertexCount;

	m_vertexBuffer											=	new float[ m_vertexCount * m_vertexSize ];

	if( a_initialDatas != NULL )
	{
		memcpy( m_vertexBuffer , a_initialDatas , m_vertexCount * m_vertexSize );
	}
}
//---------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------
void GeometryDataset::SetVerticeAt( int a_vertice , float* a_data )
{
	assert( m_vertexBuffer != NULL );
	assert( a_vertice < m_vertexCount );

	TUint32 t_offset										=	a_vertice * m_vertexSize;

	float* t_arrayOffset									=	&m_vertexBuffer[ t_offset ];
	memcpy( t_arrayOffset , a_data , m_vertexSize );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryDataset::SetVertices( float* a_datas , int a_size )
{
	assert( a_size == ( m_vertexCount * m_vertexSize ) );
	
	memcpy( m_vertexBuffer , a_datas , a_size );
}
//---------------------------------------------------------------------------------------------------------
