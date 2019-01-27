#include "FbxImporter_Imp.h"

#include "FbxMeshImporter.h"

//---------------------------------------------------------------------------------------------
FbxImporter_Imp::FbxImporter_Imp()
{
	
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FbxImporter_Imp::~FbxImporter_Imp()
{
	if(m_fbxImporter)
	{
		m_fbxImporter->Destroy();
		m_fbxImporter										=	nullptr;
	}

	if( m_fbxScene )
	{
		m_fbxScene->Destroy();
		m_fbxScene											=	nullptr;
	}

	if( m_manager )
	{
		m_manager->Destroy();
		m_manager											=	nullptr;
	}	
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool FbxImporter_Imp::LoadFBX( const char* a_file )
{
	if(! InitializeSdkObjects() )
	{
		return false;
	}

	if( !ImportScene( a_file ) )
	{
		return false;
	}

	ParseScene( );



	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool FbxImporter_Imp::InitializeSdkObjects()
{
	// Create the Fbx Manager
	m_manager												=	FbxManager::Create();

	if(!m_manager )
	{
		FBXSDK_printf("Error: Unable to create FBX Manager!\n");
		return false;
	}

	//Create an IOSettings object. This object holds all import/export settings.
	FbxIOSettings* t_settings								=	FbxIOSettings::Create( m_manager, IOSROOT );
	m_manager->SetIOSettings( t_settings );

	//Load plugins from the executable directory (optional)
	FbxString t_directoryPath								=	FbxGetApplicationDirectory();
	m_manager->LoadPluginsDirectory( t_directoryPath.Buffer() );

    //Create an FBX scene. This object holds most objects imported/exported from/to files.
    m_fbxScene												=	FbxScene::Create( m_manager, "My Scene");
	if( !m_fbxScene )
	{
		FBXSDK_printf("Error: Unable to create FBX scene!\n");
		return false;
	}

	// Create the importer.
	m_fbxImporter											=	FbxImporter::Create(m_manager,"");

	if( m_fbxImporter == NULL )
	{
		return false;
	}

	// Init succeed
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool FbxImporter_Imp::ImportScene( const char* a_file )
{
	int lFileFormat = -1;
	if (!m_manager->GetIOPluginRegistry()->DetectReaderFileFormat(a_file, lFileFormat) )
	{
		// Unrecognizable file format. Try to fall back to FbxImporter::eFBX_BINARY
		lFileFormat											=	m_manager->GetIOPluginRegistry()->FindReaderIDByDescription( "FBX binary (*.fbx)" );;
	}


     // Initialize the importer by providing a filename.
    if( m_fbxImporter->Initialize(a_file, lFileFormat) == false )
    {
		return false;
    }
  
	// Load the FBX content to the Scene
	if( m_fbxImporter->Import( m_fbxScene ) == false )
	{
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxImporter_Imp::ParseScene()
{
	Triangulate( m_fbxScene->GetRootNode() );

	FbxGeometryConverter lGeomConverter( m_manager );

	// Split meshes per material, so that we only have one material per mesh (for VBO support)
	bool t_res	=	lGeomConverter.SplitMeshesPerMaterial( m_fbxScene , /*replace*/true);

	Parse( m_fbxScene->GetRootNode() );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxImporter_Imp::Triangulate( FbxNode* a_node )
{
	FbxNodeAttribute* t_nodeAttribute						=	a_node->GetNodeAttribute();

    if( t_nodeAttribute )
    {
        if (t_nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh ||
            t_nodeAttribute->GetAttributeType() == FbxNodeAttribute::eNurbs ||
            t_nodeAttribute->GetAttributeType() == FbxNodeAttribute::eNurbsSurface ||
            t_nodeAttribute->GetAttributeType() == FbxNodeAttribute::ePatch)
        {
			FbxGeometryConverter lConverter( a_node->GetFbxManager() );
			lConverter.Triangulate( m_fbxScene, true );
        }
    }

	const int t_childCount = a_node->GetChildCount();
    for (int i = 0; i < t_childCount; i ++ )
    {
		// Žqƒm[ƒh‚ð’Tõ
        Triangulate( a_node->GetChild(i) );
    }	
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FbxImporter_Imp::Parse( FbxNode* a_node )
{
	// if the node store a Mesh, add it to the list
	FbxMesh* t_mesh											=	a_node->GetMesh();
	if( t_mesh )
	{
		m_meshNodes.push_back( a_node );
	}

	// Parse the Childs
	const int t_childCount = a_node->GetChildCount();
    for (int i = 0; i < t_childCount; i ++ )
    {
        Parse( a_node->GetChild(i) );
    }	
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
StaticMesh* FbxImporter_Imp::ImportStaticMesh( )
{
	FbxNode* t_node											=	m_meshNodes[ 0 ];

	FbxMeshImporter t_meshImporter;

	t_meshImporter.Parse( t_node );


	return t_meshImporter.CreateStaticMesh();
}
//---------------------------------------------------------------------------------------------
