#include "FbxMeshPartDatas.h"


//---------------------------------------------------------------------------------------------
FbxMeshPartDatas::FbxMeshPartDatas()
{
	m_vertexBuffer											=	nullptr;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FbxMeshPartDatas::~FbxMeshPartDatas()
{
	SAFE_DELETE_ARRAY( m_vertexBuffer );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartDatas::Parse( FbxMesh* a_meshPart )
{
	m_meshPart												=	a_meshPart;

	a_meshPart->RemoveBadPolygons();

	GenerateIndexBuffer();

	GenerateVertexBuffer();

/*	//Get the base layer of the mesh
	FbxLayer* BaseLayer = a_meshPart->GetLayer(0);

	FbxLayerElementVertexColor* LayerElementVertexColor = BaseLayer->GetVertexColors();
	int t_normalCount	=	a_meshPart->GetElementNormalCount();

	FbxLayerElement::EReferenceMode VertexColorReferenceMode(FbxLayerElement::eDirect);
	FbxLayerElement::EMappingMode VertexColorMappingMode(FbxLayerElement::eByControlPoint);
	if (LayerElementVertexColor)
	{
		VertexColorReferenceMode = LayerElementVertexColor->GetReferenceMode();
		VertexColorMappingMode = LayerElementVertexColor->GetMappingMode();
	}

	FbxLayerElementNormal* LayerElementNormal = BaseLayer->GetNormals();
	FbxLayerElementTangent* LayerElementTangent = BaseLayer->GetTangents();
	FbxLayerElementBinormal* LayerElementBinormal = BaseLayer->GetBinormals();
*/

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartDatas::GenerateIndexBuffer()
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
			m_indexBuffer[ t_offset ]						=	m_meshPart->GetPolygonVertex( t_polyIndex, i );

			t_offset ++;
		}
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartDatas::GenerateVertexBuffer()
{
	m_vertexLayout											=	ComputeVertexFormat( );

	// Get teh number of Vertices that compose this Mesh
	m_vertexCount											=	m_meshPart->GetControlPointsCount();

	// size in bytes of 1 vertex
	m_vertexSize											=	28;
	m_vertexFloatCount										=	7;

	m_vertexBuffer											=	new float[ m_vertexCount * m_vertexFloatCount ];

	for( int i = 0 ; i < m_vertexCount ; i ++ )
	{
		ProcessVertice( i );
	}

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
RhiVertexLayoutType FbxMeshPartDatas::ComputeVertexFormat( )
{
	m_haveColor												=	false;
	m_haveNormal											=	false;

	// if the mesh define vertex color
	if( m_meshPart->GetElementVertexColorCount() > 0 )
	{
		m_haveColor											=	true;
	}	

	// if the mesh define Normals
	if( m_meshPart->GetElementNormalCount() > 0 )
	{
		m_haveNormal										=	true;
	}
	// end so on

	//

	if( m_haveColor )
	{
		return RHI_VERTEX_LAYOUT_POSITION_COLOR;
	}

	return RHI_VERTEX_LAYOUT_INVALID;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshPartDatas::ProcessVertice( int a_controlPointIndex )
{
	FbxGeometryElementVertexColor* t_vertexColor		=	m_meshPart->GetElementVertexColor( 0 );
	FbxGeometryElement::EMappingMode t_mappingMode		=	t_vertexColor->GetMappingMode();
	FbxColor t_color								=	t_vertexColor->GetDirectArray().GetAt( a_controlPointIndex );


	FbxVector4& t_position									=	m_meshPart->GetControlPointAt( a_controlPointIndex );


	int t_offset												=	a_controlPointIndex * m_vertexFloatCount;


	m_vertexBuffer[ t_offset ++ ]							=	t_position[ 0 ];
	m_vertexBuffer[ t_offset ++ ]							=	t_position[ 1 ];
	m_vertexBuffer[ t_offset ++ ]							=	t_position[ 2 ];



}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
GeometryDataset* FbxMeshPartDatas::BuildGeometry()
{
	
	GeometryDataset* t_geometry								=	new GeometryDataset();

	t_geometry->CreateIndexBuffer( m_indexBufferSize , m_indexBuffer );

	t_geometry->CreateVertexBuffer( m_vertexLayout , m_vertexSize , m_vertexCount , m_vertexBuffer );

	return t_geometry;
}
//---------------------------------------------------------------------------------------------
