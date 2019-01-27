#include "FbxMeshImporter.h"
#include "../../Resources/Meshes/Includes.h"

//---------------------------------------------------------------------------------------------
FbxMeshImporter::FbxMeshImporter()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FbxMeshImporter::~FbxMeshImporter()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxMeshImporter::Parse( FbxNode* a_meshNode )
{
	m_node													=	a_meshNode;

	m_partCount												=	m_node->GetNodeAttributeCount();

	m_fbxPartList											=	new FbxMeshPartImporter[ m_partCount ];

	for( int i = 0 ; i < m_partCount ; i ++ )
	{
		FbxNodeAttribute* t_attribute						=	m_node->GetNodeAttributeByIndex( i );

		m_fbxPartList[ i ].Parse( (FbxMesh*)t_attribute  );
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
StaticMesh* FbxMeshImporter::CreateStaticMesh()
{
	StaticMesh* t_staticMesh							=	new StaticMesh();

	t_staticMesh->m_sourceData							=	BuildGeometry();

	t_staticMesh->CreateParts( m_partCount );

	int t_indice										=	0;
	for( int i = 0 ; i < m_partCount ; i ++ )
	{
		t_staticMesh->m_partList[i].SetIndexRange( t_indice , m_fbxPartList[ i ].GetIndiceCount() );

		t_indice										+=	m_fbxPartList[ i ].GetIndiceCount();
	}


	return t_staticMesh;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
GeometryDataset* FbxMeshImporter::BuildGeometry()
{
	// compute the total number of Indices and vertices
	int t_indiceCount									=	0;
	int t_verticeCount									=	0;
	for( int i = 0 ; i < m_partCount ; i ++ )
	{
		t_indiceCount									+=	m_fbxPartList[ i ].GetIndiceCount();
		t_verticeCount									+=	m_fbxPartList[ i ].GetVerticeCount();
	}

	// Setup the geometry dataset
	GeometryDataset* t_dataset							=	new GeometryDataset();
	t_dataset->CreateIndexBuffer( t_indiceCount );
	t_dataset->CreateVertexBuffer( m_fbxPartList[ 0 ].GetVertexLayout() , t_verticeCount );

	// populate the geometry dataset

	int t_indice										=	0;
	int t_vertice										=	0;
	for( int i = 0 ; i < m_partCount ; i ++ )
	{
		m_fbxPartList[ i ].PopulateIndexBuffer( t_dataset , t_indice );
		m_fbxPartList[ i ].PopulateVertexBuffer( t_dataset , t_vertice );

		t_indice										+=	m_fbxPartList[ i ].GetIndiceCount();
		t_vertice										+=	m_fbxPartList[ i ].GetVerticeCount();
	}

	return t_dataset;
}
//---------------------------------------------------------------------------------------------
