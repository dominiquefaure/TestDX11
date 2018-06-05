#ifndef __ASSET_IMPORTERS_FBX_MESH_PART_DATAS_H__
#define __ASSET_IMPORTERS_FBX_MESH_PART_DATAS_H__

#include "fbxsdk.h"

#include "../../Geometry/Includes.h"

class FbxMeshPartDatas
{
	
public:

	FbxMeshPartDatas();
	~FbxMeshPartDatas();

	void Parse( FbxMesh* a_meshPart );


	GeometryDataset* BuildGeometry();

private:

	RhiVertexLayoutType ComputeVertexFormat( );

	void ProcessVertice( int a_controlPointIndex );

	void GenerateIndexBuffer();


	void GenerateVertexBuffer();

private:

	FbxMesh*		m_meshPart;
	GeometryDataset	m_dataset;


	bool				m_haveColor;
	bool				m_haveNormal;

	TUint32				m_indexBufferSize;
	TUint32*			m_indexBuffer;

	RhiVertexLayoutType	m_vertexLayout;
	TUint32				m_vertexCount;
	TUint32				m_vertexSize;
	TUint32				m_vertexFloatCount;
	float*				m_vertexBuffer;
};

#endif