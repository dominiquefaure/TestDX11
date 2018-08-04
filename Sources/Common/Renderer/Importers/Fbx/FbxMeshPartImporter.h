#ifndef __ASSET_IMPORTERS_FBX_MESH_PART_IMPORTER_H__
#define __ASSET_IMPORTERS_FBX_MESH_PART_IMPORTER_H__

#include "fbxsdk.h"

#include "../../Resources/Geometry/Includes.h"

class MeshPart;
class FbxMeshVertex;


class FbxMeshPartImporter
{
	
public:

	FbxMeshPartImporter();
	~FbxMeshPartImporter();

	TUint32 GetIndiceCount();
	TUint32 GetVerticeCount();
	RhiVertexLayout* GetVertexLayout();

	void Parse( FbxMesh* a_meshPart );

	void PopulateIndexBuffer( GeometryDataset* a_datas , int a_startIndex );
	void PopulateVertexBuffer( GeometryDataset* a_datas , int a_startIndex );

private:

	void ComputeVertexFormat( );

	void ProcessVertice( int a_controlPointIndex );

	/*
	* Create the Index and Vertex buffer
	*/
	void CreateBuffers();

	/*
	*  poupulate the content of the Index and Vertex Buffer
	*/
	void PopulateBufferContents();


	void GenerateVertexBuffer();




	TUint32 AddVertex( TUint32 a_polygonIndex , TUint32 a_edgeIndex );

private:

	FbxMesh*		m_meshPart;


	TUint32				m_indexBufferSize;
	TUint32*			m_indexBuffer;


	RhiVertexLayout*	m_vertexLayout;
	TUint32				m_vertexCount;
/*	TUint32				m_vertexSize;
	TUint32				m_vertexFloatCount;
	float*				m_vertexBuffer;
*/

	std::vector<FbxMeshVertex*>m_vertexList;

};

#endif