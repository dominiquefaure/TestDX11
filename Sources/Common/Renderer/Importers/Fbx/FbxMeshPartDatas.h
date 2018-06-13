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

	void ProcessVertex( TUint32 a_controlPointIndex , int t_polygonIndex , int t_edgeIndex );

	/*
	* Set the position values of 1 vertex
	*/
	void SetVertexPosition( TUint32 a_controlPointIndex , TUint32 a_offset );
	void SetVertexColor( TUint32 a_controlPointIndex , TUint32 a_offset );
	void SetVertexNormal( TUint32 a_offset , TUint32 a_controlPointIndex , int t_polygonIndex , int t_edgeIndex );


private:

	FbxMesh*		m_meshPart;
	GeometryDataset	m_dataset;


	bool				m_haveColor;
	bool				m_haveNormal;

	TUint32				m_indexBufferSize;
	TUint32*			m_indexBuffer;

	RhiVertexLayout*	m_vertexLayout;
	TUint32				m_vertexCount;
	TUint32				m_vertexSize;
	TUint32				m_vertexFloatCount;
	float*				m_vertexBuffer;

};

#endif