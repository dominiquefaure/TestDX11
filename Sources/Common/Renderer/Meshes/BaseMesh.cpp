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
void BaseMesh::LoadFromJSon( const JSonNodeWriter* a_rootNode )
{
	LoadParts( a_rootNode );
	LoadGeometryDatas( a_rootNode );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::LoadParts( const JSonNodeWriter* a_rootNode )
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
void BaseMesh::LoadGeometryDatas( const JSonNodeWriter* a_rootNode )
{
	const JSonNodeWriter* t_geometryDatas					=	a_rootNode->GetNodeProperty( "GeometryDatas" );

	if( t_geometryDatas != nullptr )
	{
		m_sourceData										=	new GeometryDataset();

		m_sourceData->LoadFromJSon( t_geometryDatas );
	}
}
//-------------------------------------------------------------------------------------------------
