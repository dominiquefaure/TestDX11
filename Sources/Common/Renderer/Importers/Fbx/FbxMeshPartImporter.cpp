#include "FbxMeshPartImporter.h"

#include "../../Meshes/MeshPart.h"

//---------------------------------------------------------------------------------------------
FbxMeshPartImporter::FbxMeshPartImporter()
{
	m_vertexBuffer											=	nullptr;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FbxMeshPartImporter::~FbxMeshPartImporter()
{
	SAFE_DELETE_ARRAY( m_vertexBuffer );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartImporter::Parse( FbxMesh* a_meshPart )
{
	m_meshPart												=	a_meshPart;

	a_meshPart->RemoveBadPolygons();

	// compute the format of the vertex
	ComputeVertexFormat( );
	
	// 
	CreateBuffers();

	PopulateBufferContents();

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void FbxMeshPartImporter::ComputeVertexFormat( )
{

	TUint64 t_key											=	0;
	
	// always has position
	SETBIT( t_key , RHI_VERTEX_ELEMENT_TYPE_POSITION );

	m_haveColor												=	false;
	m_haveNormal											=	false;

	// if the mesh define vertex color
	if( m_meshPart->GetElementVertexColorCount() > 0 )
	{
		SETBIT( t_key , RHI_VERTEX_ELEMENT_TYPE_COLOR );

		m_haveColor											=	true;
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
void FbxMeshPartImporter::CreateBuffers()
{
	int t_polygonCount										=	m_meshPart->GetPolygonCount();

	// Get the number of indices
	m_indexBufferSize										=	t_polygonCount * 3;

	m_indexBuffer											=	new TUint32[ m_indexBufferSize ];


	// Get the number of Vertices that compose this Mesh
	m_vertexCount											=	m_meshPart->GetControlPointsCount();

	// size in bytes of 1 vertex
	m_vertexSize											=	m_vertexLayout->GetVertexSize();
	m_vertexFloatCount										=	m_vertexSize / sizeof( float );

	m_vertexBuffer											=	new float[ m_vertexCount * m_vertexFloatCount ];

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartImporter::PopulateBufferContents()
{
	int t_polygonCount										=	m_meshPart->GetPolygonCount();


	TUint32 t_offset										=	0;

	TUint32 t_indice;

	std::map<TUint32 , bool>	t_processedIndices;

	// parse all the polygon
	for( int t_polyIndex = 0 ; t_polyIndex < t_polygonCount ; t_polyIndex ++ )
	{
		for( int i = 0 ; i < 3 ; i ++ )
		{
			// Get the vertex Index
			t_indice										=	m_meshPart->GetPolygonVertex( t_polyIndex, i );

			// if it's the 1st time we encounter this vertice
			if( t_processedIndices.find(t_indice) == t_processedIndices.end() )
			{
				ProcessVertex( t_indice , t_polyIndex , i );

				//Add entry to the map
				t_processedIndices[ t_indice ]				=	true;
			}

			// Get the Control Point index
			m_indexBuffer[ t_offset ]						=	t_indice;

			t_offset ++;

			
		}
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartImporter::ProcessVertex( TUint32 a_controlPointIndex , int t_polygonIndex , int t_edgeIndex )
{
	// conpute the vertex start offset
	int t_offset											=	a_controlPointIndex * m_vertexFloatCount;

	int t_key												=	m_vertexLayout->GetLayoutKey();

	// set the position
	SetVertexPosition( a_controlPointIndex , t_offset );
	t_offset												+=	3;

	// if the vertex have colors
	if( ISBITSET( t_key , RHI_VERTEX_ELEMENT_TYPE_COLOR ) )
	{
		SetVertexColor( a_controlPointIndex , t_offset );
		t_offset											+=	4;
	}

	// if the vertex have Normals
	if( ISBITSET( t_key , RHI_VERTEX_ELEMENT_TYPE_NORMAL ) )
	{
		SetVertexNormal( t_offset , a_controlPointIndex , t_polygonIndex , t_edgeIndex );
		t_offset											+=	3;
	}

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartImporter::SetVertexPosition( TUint32 a_controlPointIndex , TUint32 a_offset )
{
	FbxVector4& t_position									=	m_meshPart->GetControlPointAt( a_controlPointIndex );

	TUint32 t_offset										=	a_offset;

	m_vertexBuffer[ t_offset ++ ]							=	t_position[ 0 ];
	m_vertexBuffer[ t_offset ++ ]							=	t_position[ 1 ];
	m_vertexBuffer[ t_offset ++ ]							=	t_position[ 2 ];

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartImporter::SetVertexColor( TUint32 a_controlPointIndex , TUint32 a_offset )
{
/*
	FbxGeometryElementVertexColor* t_vertexColor		=	m_meshPart->GetElementVertexColor( 0 );

	if( t_vertexColor != NULL )
	{
		FbxGeometryElement::EMappingMode t_mappingMode		=	t_vertexColor->GetMappingMode();
		FbxColor t_color								=	t_vertexColor->GetDirectArray().GetAt( a_controlPointIndex );
	}
*/
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartImporter::SetVertexNormal( TUint32 a_offset , TUint32 a_controlPointIndex , int t_polygonIndex , int t_edgeIndex )
{
	FbxVector4 t_normal;
	m_meshPart->GetPolygonVertexNormal( t_polygonIndex, t_edgeIndex, t_normal);

	TUint32 t_offset										=	a_offset;
	m_vertexBuffer[ t_offset ++ ]							=	t_normal[ 0 ];
	m_vertexBuffer[ t_offset ++ ]							=	t_normal[ 1 ];
	m_vertexBuffer[ t_offset ++ ]							=	t_normal[ 2 ];
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------

GeometryDataset* FbxMeshPartImporter::BuildGeometry()
{
	
	GeometryDataset* t_geometry								=	new GeometryDataset();

	t_geometry->CreateIndexBuffer( m_indexBufferSize , m_indexBuffer );

	t_geometry->CreateVertexBuffer( m_vertexLayout->GetLayoutType() , m_vertexSize , m_vertexCount , m_vertexBuffer );

	return t_geometry;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
MeshPart* FbxMeshPartImporter::GenerateMeshPart()
{
	// Create a new MeshPart
	MeshPart* t_meshPart									=	new MeshPart();

	t_meshPart->m_castShadow								=	true;
	t_meshPart->m_materialIndex								=	0;

	// set the Geometry data
//	t_meshPart->m_sourceData								=	BuildGeometry();

	// return the Mesh part created
	return t_meshPart;
}
//---------------------------------------------------------------------------------------------
