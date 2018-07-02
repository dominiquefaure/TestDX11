#include "FbxAssetImporter.h"
#include "FbxImporter_Imp.h"
//---------------------------------------------------------------------------------------------
FbxAssetImporter::FbxAssetImporter()
{
	m_implementation										=	new FbxImporter_Imp();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FbxAssetImporter::~FbxAssetImporter()
{
	if( m_implementation )
	{
		delete m_implementation;
		m_implementation									=	nullptr;
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool FbxAssetImporter::LoadFBX( const char* a_file )
{
	return m_implementation->LoadFBX( a_file );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
StaticMesh* FbxAssetImporter::ImportStaticMesh( )
{
	return m_implementation->ImportStaticMesh( );
}
//---------------------------------------------------------------------------------------------
