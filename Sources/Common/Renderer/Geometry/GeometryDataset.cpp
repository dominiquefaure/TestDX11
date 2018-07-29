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

///////
// Load Methods
///////


//---------------------------------------------------------------------------------------------------------
void GeometryDataset::LoadFromJSon(const char* a_filePath )
{
	// Load the Json File
	JSonReader t_reader;
	t_reader.Load( a_filePath );

	LoadFromJSon( t_reader.GetRootNode() );

}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryDataset::LoadFromJSon( const JSonNode* a_rootNode )
{
	// check if there is a Vertex buffer property
	const JSonNode* t_vertexBufferNode						=	a_rootNode->GetNodeProperty( "VertexBuffer" );

	// check the property is valid
	if( t_vertexBufferNode != nullptr )
	{
		LoadVertexBuffer( t_vertexBufferNode );
	}
	else
	{
		// invalid geometry
		assert( false );
		return;
	}

	// check if there is an Index buffer property
	const JSonNode* t_indexBufferNode						=	a_rootNode->GetNodeProperty( "IndexBuffer" );

	// if the property is valid
	if( t_indexBufferNode != nullptr )
	{
		LoadIndexBuffer( t_indexBufferNode );
	}

	// get the primitive type. if not specified use Triangle List
	m_primitiveType											=	(RhiPrimitiveType)a_rootNode->GetIntProperty("PrimitiveType" , (int) RHI_PRIMITIVE_TYPE_TRIANGLE_LIST );

	// Get the Layout 
	m_vertexLayoutType										=	(RhiVertexLayoutType)a_rootNode->GetIntProperty( "VertexLayout" );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryDataset::LoadIndexBuffer( const JSonNode* a_indexBufferNode )
{
	// we have an index buffer
	m_isIndexed												=	true;

	// Get the number of Index
	m_indexCount											=	(TUint32)a_indexBufferNode->GetIntProperty( "IndexCount" );

	// Get the Property that store the Index buffer datas
	const JSonIntArrayProperty* t_datas					=	a_indexBufferNode->GetIntArray( "Datas" );


	if( t_datas != nullptr )
	{
		if( m_indexCount < 65535 )
		{
			m_indexType										=	INDEX_BUFFER_TYPE_16;

			// Allocate the Index buffer
			m_indexBuffer16									=	new TUint16[ m_indexCount ];

			// read the Datas
			t_datas->GetValues16( m_indexBuffer16  );
		}
		else
		{
			m_indexType										=	INDEX_BUFFER_TYPE_32;

			// Allocate the Index buffer
			m_indexBuffer32									=	new TUint32[ m_indexCount ];
			
			// read the Datas
			t_datas->GetValues32( m_indexBuffer32 );

		}
	}
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryDataset::LoadVertexBuffer( const JSonNode* a_vertexBufferNode )
{
	// Get the size of 1 vertex
	m_vertexSize											=	(TUint32)a_vertexBufferNode->GetIntProperty( "VertexSize" );

	// Get the number of Vertex
	m_vertexCount											=	(TUint32)a_vertexBufferNode->GetIntProperty( "VertexCount" );

	// Get the Property that store the Vertex buffer datas
	const JSonFloatArrayProperty* t_vertices				=	a_vertexBufferNode->GetFloatArray( "Datas" );
	if( t_vertices != nullptr )
	{
		int t_size											=	t_vertices->GetCount();

		// allocate the VertexBuffer
		m_vertexBuffer										=	new float[ t_size ];

		// read the Datas
		t_vertices->GetValues32( m_vertexBuffer );
	}
}
//---------------------------------------------------------------------------------------------------------


///////
// Serialize Methods
///////


//---------------------------------------------------------------------------------------------------------
void GeometryDataset::Serialize( JSonNode* a_partNode )
{
	a_partNode->AddIntProperty( "PrimitiveType" , (int) m_primitiveType );
	a_partNode->AddIntProperty( "VertexLayout" , (int) m_vertexLayoutType );

	SerializeIndexBuffer( a_partNode );
	SerializeVertexBuffer( a_partNode );
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryDataset::SerializeIndexBuffer( JSonNode* a_node )
{
	if( IsIndexed() )
	{
		JSonNode* t_node									=	a_node->AddNodeProperty( "IndexBuffer" );
		t_node->AddIntProperty( "IndexCount" , m_indexCount );

		if( m_indexCount < 65535 )
		{
			t_node->AddIntArray( "Datas" , m_indexCount , m_indexBuffer16 );
		}
		else
		{
			t_node->AddIntArray( "Datas" , m_indexCount , m_indexBuffer32 );
		}
	}
}
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
void GeometryDataset::SerializeVertexBuffer( JSonNode* a_node )
{
	if( m_vertexBuffer != nullptr )
	{
		JSonNode* t_node									=	a_node->AddNodeProperty( "VertexBuffer" );

		t_node->AddIntProperty( "VertexSize" , m_vertexSize );
		t_node->AddIntProperty( "VertexCount" , m_vertexCount );

		int t_floatCount									=	m_vertexCount * m_vertexSize / sizeof( float );
		t_node->AddFloatArray( "Datas" , t_floatCount , m_vertexBuffer );
	}
}
//---------------------------------------------------------------------------------------------------------
