#include "MeshPart.h"

#include "../../RHI/Includes.h"

#include "../Shaders/ShaderProgram.h"

#ifdef _DEBUG
#include "MeshPart.inl"
#endif

//-------------------------------------------------------------------------------------------------
MeshPart::MeshPart()
{
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
void MeshPart::LoadFromJSon( const JSonNodeWriter* a_partNode )
{
	m_startIndex											=	a_partNode->GetIntProperty( "StartIndex" );
	m_indexCount											=	a_partNode->GetIntProperty( "IndexCount" );

	m_castShadow											=	a_partNode->GetIntProperty( "CastShadow" );
	m_materialIndex											=	a_partNode->GetIntProperty( "MaterialIndex" );
}
//-------------------------------------------------------------------------------------------------

