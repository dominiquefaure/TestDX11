#include "FbxMeshPartImporter.h"

#include "../../Meshes/MeshPart.h"

#include "FbxMeshVertex.h"

//---------------------------------------------------------------------------------------------
FbxMeshPartImporter::FbxMeshPartImporter()
{
	m_vertexLayout											=	nullptr;
	m_indexBuffer											=	nullptr;
	m_indexBufferSize										=	0;

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FbxMeshPartImporter::~FbxMeshPartImporter()
{
	SAFE_DELETE_ARRAY( m_indexBuffer );
	//todo free the VertexList
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
TUint32 FbxMeshPartImporter::GetIndiceCount()
{
	return m_indexBufferSize;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
TUint32 FbxMeshPartImporter::GetVerticeCount()
{
	return m_vertexList.size();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
RhiVertexLayout* FbxMeshPartImporter::GetVertexLayout()
{
	return m_vertexLayout;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartImporter::Parse( FbxMesh* a_meshPart  )
{
	m_meshPart												=	a_meshPart;

	a_meshPart->RemoveBadPolygons();

	// compute the format of the vertex
	ComputeVertexFormat( );
	
	// 
//	CreateBuffers();

	PopulateBufferContents();

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FbxMeshPartImporter::ComputeVertexFormat( )
{

	TUint64 t_key											=	0;
	
	// always has position
	SETBIT( t_key , RHI_VERTEX_ELEMENT_TYPE_POSITION );

	// if the mesh define vertex color
	if( m_meshPart->GetElementVertexColorCount() > 0 )
	{
		SETBIT( t_key , RHI_VERTEX_ELEMENT_TYPE_COLOR );
	}	

	// if the mesh define Normals
	if( m_meshPart->GetElementNormalCount() > 0 )
	{
		SETBIT( t_key , RHI_VERTEX_ELEMENT_TYPE_NORMAL );
	}
	// end so on

	// Get the vertex Layout
	m_vertexLayout											=	RhiManager::GetInstance()->GetGraphicDevice()->GetVertexLayout((RhiVertexLayoutTypeKey) t_key );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartImporter::PopulateBufferContents()
{
	int t_polygonCount										=	m_meshPart->GetPolygonCount();
	// Get the number of indices
	m_indexBufferSize										=	t_polygonCount * 3;

	m_indexBuffer											=	new TUint32[ m_indexBufferSize ];

	TUint32 t_offset										=	0;

	// parse all the polygon
	for( int t_polyIndex = 0 ; t_polyIndex < t_polygonCount ; t_polyIndex ++ )
	{
		for( int i = 0 ; i < 3 ; i ++ )
		{
			// Get the Control Point index
			m_indexBuffer[ t_offset ]						=	AddVertex( t_polyIndex , i );
			t_offset ++;
		}
	}

	m_vertexCount											=	m_vertexList.size();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
TUint32 FbxMeshPartImporter::AddVertex( TUint32 a_polygonIndex , TUint32 a_edgeIndex )
{
	// Setup a tmp vertex
	FbxMeshVertex t_vertex;
	t_vertex.Set( m_meshPart , a_polygonIndex , a_edgeIndex , m_vertexLayout->GetLayoutKey() );

	// parse the Vertex already created
	int t_count												=	m_vertexList.size();
	for( int i = 0 ; i < t_count ; i ++ )
	{
		// if it's the same return the index
		if( m_vertexList[ i ]->IsSame( t_vertex ) )
		{
			return i;
		}
	}

	// not found so create a new one
	m_vertexList.push_back( new FbxMeshVertex( t_vertex ) );

	return t_count;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartImporter::PopulateIndexBuffer( GeometryDataset* a_datas , int a_startIndex )
{
	int t_index												=	a_startIndex;
	for( int i = 0 ; i < m_indexBufferSize ; i ++ )
	{
		a_datas->SetIndiceAt( t_index , m_indexBuffer[ i ] );

		t_index ++;
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartImporter::PopulateVertexBuffer( GeometryDataset* a_datas , int a_startIndex )
{
	int t_offset											=	a_startIndex * m_vertexLayout->GetVertexSize();

	int t_offsetInc											=	m_vertexLayout->GetVertexSize() / sizeof(float);

	int t_count												=	m_vertexList.size();
	for( int i = 0 ; i < t_count ; i ++ )
	{
		m_vertexList[ i ]->Write( a_datas->m_vertexBuffer , t_offset );

		t_offset											+=	t_offsetInc;
	}

}
//---------------------------------------------------------------------------------------------
