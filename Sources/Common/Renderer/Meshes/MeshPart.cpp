#include "MeshPart.h"

#include "../../RHI/Includes.h"
#include "../Geometry/Geometrydataset.h"
#include "../Geometry/StaticGeometry.h"

#include "../Shaders/ShaderProgram.h"


//-------------------------------------------------------------------------------------------------
MeshPart::MeshPart()
{
	m_sourceData											=	NULL;
	m_renderGeometry										=	NULL;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
MeshPart::~MeshPart()
{
	SAFE_DELETE( m_sourceData );
	SAFE_DELETE( m_renderGeometry );
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void MeshPart::LoadFromJSon( const char* a_filePath )
{
	// Load the Json File
	JsonDocument t_document;
	t_document.Load(a_filePath);

	LoadFromJSon( t_document.GetRootNode() );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void MeshPart::LoadFromJSon( JSonNode& a_rootNode )
{
	JSonNode t_geometryDatas								=	a_rootNode.GetNodeProperty( "Datas" );

	m_sourceData											=	new GeometryDataset();

	m_sourceData->LoadFromJSon( t_geometryDatas );

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void MeshPart::BuildRenderData( RhiGraphicDevice* a_device ,  bool a_freeSourceData )
{
	m_renderGeometry										=	new StaticGeometry();

	m_renderGeometry->Build( a_device , m_sourceData );

	// Free the Soruce data
	if( a_freeSourceData )
	{
		SAFE_DELETE( m_sourceData );
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void MeshPart::Draw( RhiGraphicContext* a_context  , ShaderProgram* a_program , TUint64 a_customFlags )
{
	if( m_renderGeometry != NULL )
	{
		m_renderGeometry->Draw( a_context , a_program , a_customFlags );
	}
}
//-------------------------------------------------------------------------------------------------
