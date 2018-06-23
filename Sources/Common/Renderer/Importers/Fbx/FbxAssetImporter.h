#ifndef __ASSET_IMPORTERS_FBX_IMPORTER_H__
#define __ASSET_IMPORTERS_FBX_IMPORTER_H__

#include "../../Geometry/Includes.h"


class FbxImporter_Imp;

class MeshPart;

class FbxAssetImporter
{
	
public:

	FbxAssetImporter();
	~FbxAssetImporter();

	/*
	 * Load an Fbx File
	 */
	bool LoadFBX( const char* a_file );


	MeshPart* ImportMesh(  );

// Fields
private:

	FbxImporter_Imp*	m_implementation;
};

#endif