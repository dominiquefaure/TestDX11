#include "BaseMesh.h"
#include "MeshPart.h"

#include "../Geometry/Geometrydataset.h"
#include "../Geometry/StaticGeometry.h"

#include "Renderer/Scene/Rendering/Includes.h"


//-------------------------------------------------------------------------------------------------
BaseMesh::BaseMesh()
{
	m_partList												=	nullptr;
	m_sourceData											=	nullptr;
	m_renderGeometry										=	nullptr;

	m_partCount												=	0;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
BaseMesh::~BaseMesh()
{
	SAFE_DELETE_ARRAY( m_partList );
	SAFE_DELETE( m_sourceData );
	SAFE_DELETE( m_renderGeometry );

}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void BaseMesh::BuildRenderData( RhiGraphicDevice* a_device , bool a_freeSourceData  )
{
	if( m_sourceData != nullptr )
	{
		m_renderGeometry									=	new StaticGeometry();

		m_renderGeometry->Build( a_device , m_sourceData );

		// Free the Soruce data
		if( a_freeSourceData )
		{
			SAFE_DELETE( m_sourceData );
		}
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::Draw( RhiGraphicContext* a_context )
{
	if( m_renderGeometry != NULL )
	{
		m_renderGeometry->Draw( a_context );
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::DrawPart( TUint32 a_partIndex , RhiGraphicContext* a_context   )
{
	if( m_renderGeometry != NULL )
	{
		MeshPart* t_part									=	&m_partList[ a_partIndex ];

		m_renderGeometry->Draw( a_context , t_part->GetStartIndex() , t_part->GetIndexCount() );
	}

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::Setup( GeometryRenderElement* a_element )
{
	a_element->SetupGeometry( m_renderGeometry , m_partList[ 0 ].GetStartIndex() , m_partList[ 0 ].GetIndexCount() );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::CreateParts( TUint32 a_count )
{
	m_partCount												=	a_count;

	// allocate the part aray
	m_partList												=	new MeshPart[ m_partCount ];

}
//-------------------------------------------------------------------------------------------------


/////////////
// Loading Methods
/////////////


//-------------------------------------------------------------------------------------------------
void BaseMesh::LoadFromJSon( const char* a_filePath )
{
	// Load the Json File
	JSonReader t_reader;
	t_reader.Load( a_filePath );

	LoadFromJSon( t_reader.GetRootNode() );

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::LoadFromJSon( const JSonNode* a_rootNode )
{
	LoadParts( a_rootNode );
	LoadGeometryDatas( a_rootNode );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::LoadParts( const JSonNode* a_rootNode )
{
	// Get the Property that store the MeshPartss
	const JSonNodeArrayProperty* t_parts					=	a_rootNode->GetNodeArray( "MeshParts" );

	// validate it's an Array
	if( t_parts != nullptr )
	{
		// get the number of Parts
		m_partCount											=	t_parts->GetCount();

		// allocate the part aray
		m_partList											=	new MeshPart[ m_partCount ];

		// Load all the parts contents
		for( TUint32 i = 0 ; i < m_partCount ; i ++ )
		{
			m_partList[ i ].LoadFromJSon( t_parts->GetNodeAt( i ) );
		}
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::LoadGeometryDatas( const JSonNode* a_rootNode )
{
	const JSonNode* t_geometryDatas							=	a_rootNode->GetNodeProperty( "GeometryDatas" );

	if( t_geometryDatas != nullptr )
	{
		m_sourceData										=	new GeometryDataset();

		m_sourceData->LoadFromJSon( t_geometryDatas );
	}
}
//-------------------------------------------------------------------------------------------------



/////////////
// Serialization Methods
/////////////

//-------------------------------------------------------------------------------------------------
void BaseMesh::SerializeToJSon( const char* a_path )
{
	// Create the Writer
	JSonWriter t_writer;

	JSonNode* t_rootNode									=	t_writer.GetRootNode();

	// Serialize the Mesh content
	SerializeParts( t_rootNode );
	SerializeGeometryDatas( t_rootNode );

	// Write to File
	t_writer.Save( a_path );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::SerializeParts( JSonNode* a_rootNode )
{
	// Create the sub node that store all the parts
	JSonNodeArrayProperty* t_parts							=	a_rootNode->AddNodeArrayProperty("MeshParts");

	for( int i = 0 ; i < m_partCount ; i ++ )
	{
		// add a new json node
		JSonNode* t_node									=	t_parts->AddNode();

		m_partList[ i ].Serialize( t_node );
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::SerializeGeometryDatas( JSonNode* a_rootNode )
{
	JSonNode* t_node										=	a_rootNode->AddNodeProperty( "GeometryDatas" );

	if( m_sourceData != nullptr )
	{
		m_sourceData->Serialize( t_node );
	}
}
//-------------------------------------------------------------------------------------------------
