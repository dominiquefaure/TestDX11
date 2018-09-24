#include "Model.h"

#include "Renderer/Scene/Rendering/GeometryRenderElement.h"

//------------------------------------------------------------------------------------
Model::Model()
{
	m_mesh													=	nullptr;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
Model::~Model()
{
	m_mesh													=	nullptr;
	m_material.SetMaterial( nullptr );
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void Model::SetMesh( const ReferenceCountedPtr<BaseMesh>& a_mesh )
{
	m_mesh													=	a_mesh;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void Model::SetMaterial( const ReferenceCountedPtr<Material>& a_material )
{
	m_material.SetMaterial( a_material );
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void Model::Draw( RhiGraphicContext* a_context , SConstantBuffer<StaticModelVertexConstants>* a_instanceCB )
{
	if( ( m_material.IsMaterialSet() ) && ( m_mesh != nullptr ) )
	{
		GeometryRenderElement t_element;
		m_material.Setup( &t_element );
		m_mesh->Setup( &t_element );

		t_element.SetVertexParameters( a_instanceCB->GetRhiConstantBuffer() );

		t_element.Render( a_context );
	}

}
//------------------------------------------------------------------------------------
