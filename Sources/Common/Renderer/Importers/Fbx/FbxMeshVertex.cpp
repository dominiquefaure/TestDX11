#include "FbxMeshVertex.h"

#include "../../../RHI/Includes.h"

//---------------------------------------------------------------------------------------------
FbxMeshVertex::FbxMeshVertex()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FbxMeshVertex::FbxMeshVertex(const FbxMeshVertex& a_vertex )
{
	m_position												=	a_vertex.m_position;
	m_normal												=	a_vertex.m_normal;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FbxMeshVertex::~FbxMeshVertex()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshVertex::Set( FbxMesh* a_mesh , int a_polygonIndex , int a_edgeIndex , TUint32 a_vertexFormatKey )
{
	m_formatKey												=	a_vertexFormatKey;

	ProcessPosition( a_mesh , a_polygonIndex , a_edgeIndex );

	if( ISBITSET( m_formatKey , RHI_VERTEX_ELEMENT_TYPE_NORMAL ) )
	{
		ProcessNormal( a_mesh , a_polygonIndex , a_edgeIndex );
	}

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshVertex::ProcessPosition( FbxMesh* a_mesh , int a_polygonIndex , int a_edgeIndex )
{
	TUint32 t_index											=	a_mesh->GetPolygonVertex( a_polygonIndex , a_edgeIndex );

	FbxVector4& t_position									=	a_mesh->GetControlPointAt( t_index );

	m_position.x											=	t_position[ 0 ];
	m_position.y											=	t_position[ 1 ];
	m_position.z											=	t_position[ 2 ];
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshVertex::ProcessNormal( FbxMesh* a_mesh , int a_polygonIndex , int a_edgeIndex )
{
	FbxVector4 t_normal;
	a_mesh->GetPolygonVertexNormal( a_polygonIndex, a_edgeIndex, t_normal);

	m_normal.x												=	t_normal[ 0 ];
	m_normal.y												=	t_normal[ 1 ];
	m_normal.z												=	t_normal[ 2 ];
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
TBool FbxMeshVertex::IsSame( const FbxMeshVertex& a_vertex )
{
	if( m_position != a_vertex.m_position )
	{
		return false;
	}

	if( m_normal != a_vertex.m_normal )
	{
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
TUint32 FbxMeshVertex::Write( float* a_geometryBuffer , TUint32 a_offset )
{
	TUint32 t_offset										=	a_offset;

	a_geometryBuffer[ t_offset ++ ]							=	m_position.x;
	a_geometryBuffer[ t_offset ++ ]							=	m_position.y;
	a_geometryBuffer[ t_offset ++ ]							=	m_position.z;


	a_geometryBuffer[ t_offset ++ ]							=	m_normal.x;
	a_geometryBuffer[ t_offset ++ ]							=	m_normal.y;
	a_geometryBuffer[ t_offset ++ ]							=	m_normal.z;

	return t_offset;
}
//---------------------------------------------------------------------------------------------
