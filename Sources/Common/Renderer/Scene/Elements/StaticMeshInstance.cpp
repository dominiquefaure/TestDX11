#include "StaticMeshInstance.h"


//------------------------------------------------------------------------------------
StaticMeshInstance::StaticMeshInstance()
{
	m_mesh													=	nullptr;

	m_vertexConstants.m_worldTransform.SetIdentity();
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
StaticMeshInstance::~StaticMeshInstance()
{
	m_mesh													=	nullptr;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void StaticMeshInstance::Init( RhiGraphicDevice* a_device , StaticMesh* a_mesh )
{
	m_vertexConstantBuffer.Init( a_device );

	m_mesh													=	a_mesh;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void StaticMeshInstance::SetMesh( const ReferenceCountedPtr<StaticMesh>& a_mesh )
{
	m_mesh													=	a_mesh;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void StaticMeshInstance::SetMaterial( Material* a_material )
{
	m_material												=	a_material;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void StaticMeshInstance::Draw( RhiGraphicContext* a_context )
{
	if( ( m_mesh != nullptr ) && ( m_material != nullptr ) )
	{
		m_vertexConstants.m_worldTransform	=	m_worldTransform;
		m_vertexConstantBuffer.Update( a_context , &m_vertexConstants );
		m_vertexConstantBuffer.Bind( a_context , RHI_SHADER_TYPE_VERTEX_SHADER ,VS_PARAMETER_SLOT_PER_DRAW );

		m_material->Apply( a_context );

		m_mesh->DrawPart( 0 , a_context , m_material->GetShaderProgram() , 0 );
	}

}
//------------------------------------------------------------------------------------
