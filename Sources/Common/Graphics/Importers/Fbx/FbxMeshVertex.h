#ifndef __FBX_MESH_VERTEX_H__
#define __FBX_MESH_VERTEX_H__

#include "../../../Core/CoreIncludes.h"

#include "fbxsdk.h"

class FbxMeshVertex
{
public:
	FbxMeshVertex();
	FbxMeshVertex(const FbxMeshVertex& a_vertex );

	~FbxMeshVertex();


	void Set( FbxMesh* a_mesh , int a_polygonIndex , int a_edgeIndex , TUint32 a_vertexFormatKey );


	TBool IsSame( const FbxMeshVertex& a_vertex );

	/*
	* Write the Content of this Vertex to the buffer
	*
	* @param a_geometryBuffer	Buffer to write the content
	* @param a_offset			Start offset in the buffer to write the vertex content
	* @return Out offset
	*/
	TUint32 Write( float* a_geometryBuffer , TUint32 a_offset );

private:

	void ProcessPosition( FbxMesh* a_mesh , int a_polygonIndex , int a_edgeIndex );
	void ProcessNormal( FbxMesh* a_mesh , int a_polygonIndex , int a_edgeIndex );

private:

	TUint32		m_formatKey;

	Vector3F	m_position;
	Vector3F	m_normal;
};

#endif