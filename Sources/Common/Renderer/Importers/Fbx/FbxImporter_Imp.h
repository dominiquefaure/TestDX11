#ifndef __ASSET_IMPORTERS_FBX_IMPORTER_IMP_H__
#define __ASSET_IMPORTERS_FBX_IMPORTER_IMP_H__

#include "../../Geometry/Includes.h"
#include "fbxsdk.h"

class MeshPart;

class FbxImporter_Imp
{
	
public:

	FbxImporter_Imp();
	~FbxImporter_Imp();

	/*
	 * Load an Fbx File
	 */
	bool LoadFBX( const char* a_file );


	MeshPart* ImportMesh( );

// MEthods
private:

	/*
	 * Create required Fbx SDK objects
	 */
	bool InitializeSdkObjects();

	/*
	 * Import the Scene we want to load
	 */
	bool ImportScene( const char* a_file );

	/*
	 * Preprare the Scene to be used: Triangulate + split per material
	 */
	void ParseScene();

	/*
	 * Triangulate recursively the scene
	 */
	void Triangulate( FbxNode* a_node );

	/*
	 * Parse a Scene Node.
	 * Function called recursively
	 */
	void Parse( FbxNode* a_node );



// Fields
private:

	FbxManager*		m_manager;
	FbxImporter*	m_fbxImporter;

	FbxScene*		m_fbxScene;

	// List fo nodes taht store an FbxMesh
	std::vector<FbxNode*>	m_meshNodes;

};

#endif