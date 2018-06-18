#include "BaseMesh.h"
#include "MeshPart.h"


//-------------------------------------------------------------------------------------------------
BaseMesh::BaseMesh()
{
	m_partList												=	NULL;
	m_partCount												=	0;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
BaseMesh::~BaseMesh()
{
	SAFE_DELETE_ARRAY( m_partList );
}
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
void BaseMesh::BuildRenderData( RhiGraphicDevice* a_device , bool a_freeSourceData  )
{
	for( TUint32 i = 0 ; i < m_partCount ; i ++ )
	{
		m_partList[ i ].BuildRenderData( a_device , a_freeSourceData );
	}
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void BaseMesh::Draw( RhiGraphicContext* a_context  , ShaderProgram* a_program , TUint64 a_customFlags )
{
	for( TUint32 i = 0 ; i < m_partCount ; i ++ )
	{
		m_partList[ i ].Draw( a_context , a_program , a_customFlags );
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
void BaseMesh::LoadParts( JSonNode& a_rootNode )
{
}
//-------------------------------------------------------------------------------------------------
