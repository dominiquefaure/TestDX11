#ifndef __FBX_MESH_IMPORTER_H__
#define __FBX_MESH_IMPORTER_H__

#include "fbxsdk.h"

#include "FbxMeshPartImporter.h"

#include "../../Meshes/BaseMesh.h"

class StaticMesh;

class FbxMeshImporter
{
public:

	FbxMeshImporter();
	~FbxMeshImporter();

	/*
	* Parse an FbxNode storing a Mesh
	*/
	void Parse( FbxNode* a_meshNode );

	StaticMesh* CreateStaticMesh();

private:

	GeometryDataset* BuildGeometry();


private:

	// The Fbx node storing info about this mesh
	FbxNode*				m_node;

	TUint32					m_partCount;
	FbxMeshPartImporter*	m_fbxPartList;

};

#endif