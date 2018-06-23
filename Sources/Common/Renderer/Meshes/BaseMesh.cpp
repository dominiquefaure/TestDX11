#include "BaseMesh.h"
#include "MeshPart.h"

#include "../Geometry/Geometrydataset.h"
#include "../Geometry/StaticGeometry.h"


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
void BaseMesh::Draw( RhiGraphicContext* a_context  , ShaderProgram* a_program , TUint64 a_customFlags )
{
	if( m_renderGeometry != NULL )
	{
		m_renderGeometry->Draw( a_context , a_program , a_customFlags );
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::DrawPart( TUint32 a_partIndex , RhiGraphicContext* a_context  , ShaderProgram* a_program , TUint64 a_customFlags )
{
	if( m_renderGeometry != NULL )
	{
		MeshPart* t_part									=	&m_partList[ a_partIndex ];

		m_renderGeometry->Draw( a_context , a_program , t_part->GetStartIndex() , t_part->GetIndexCount() ,a_customFlags );
	}

}
//-------------------------------------------------------------------------------------------------


/////////////
// Loading Methods
/////////////


//-------------------------------------------------------------------------------------------------
void BaseMesh::LoadFromJSon( const char* a_filePath )
{
	// Load the Json File
	JsonDocument t_document;
	t_document.Load(a_filePath);

	LoadFromJSon( t_document.GetRootNode() );

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::LoadFromJSon( JSonNode& a_rootNode )
{
	LoadParts( a_rootNode );
	LoadGeometryDatas( a_rootNode );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::LoadParts( JSonNode& a_rootNode )
{
	// Get the Property that store the MeshPartss
	JSonProperty t_parts									=	a_rootNode.GetProperty( "MeshParts" );

	// validate it's an Array
	if( t_parts.IsArray() )
	{
		// get the number of Parts
		m_partCount											=	t_parts.GetArraySize();

		// allocate the part aray
		m_partList											=	new MeshPart[ m_partCount ];

		// Load all the parts contents
		for( TUint32 i = 0 ; i < m_partCount ; i ++ )
		{
			m_partList[ i ].LoadFromJSon( t_parts.GetSubNodeAt( i ) );
		}
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::LoadGeometryDatas( JSonNode& a_rootNode )
{

	if( a_rootNode.Contains ("GeometryDatas" ) )
	{
		JSonNode t_geometryDatas							=	a_rootNode.GetNodeProperty( "GeometryDatas" );
		m_sourceData										=	new GeometryDataset();

		m_sourceData->LoadFromJSon( t_geometryDatas );
	}
}
//-------------------------------------------------------------------------------------------------
