#include "MeshPart.h"

#include "RHI/Includes.h"

#include "../Shaders/ShaderProgram.h"

#ifdef _DEBUG
#include "MeshPart.inl"
#endif

//-------------------------------------------------------------------------------------------------
MeshPart::MeshPart()
{
	m_startIndex											=	0;
	m_indexCount											=	0;
	m_materialIndex											=	0;
	m_castShadow											=	true;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
MeshPart::~MeshPart()
{
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void MeshPart::SetIndexRange( TUint32 a_startIndex , TUint32 a_count )
{
	m_startIndex											=	a_startIndex;
	m_indexCount											=	a_count;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void MeshPart::LoadFromJSon( const JSonNode* a_partNode )
{
	m_startIndex											=	a_partNode->GetIntProperty( "StartIndex" );
	m_indexCount											=	a_partNode->GetIntProperty( "IndexCount" );

	m_castShadow											=	a_partNode->GetBoolProperty( "CastShadow" );
	m_materialIndex											=	a_partNode->GetIntProperty( "MaterialIndex" );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void MeshPart::Serialize( JSonNode* a_partNode )
{
	a_partNode->AddIntProperty( "StartIndex" , m_startIndex );
	a_partNode->AddIntProperty( "IndexCount" , m_indexCount );
	a_partNode->AddIntProperty( "MaterialIndex" , m_materialIndex );

	a_partNode->AddBoolProperty( "CastShadow" , m_castShadow );
}
//-------------------------------------------------------------------------------------------------
