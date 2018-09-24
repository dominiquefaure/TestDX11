#include "GeometryRenderElement.h"

//-------------------------------------------------------------------------------------------------
GeometryRenderElement::GeometryRenderElement()
{
	m_elementVertexParameters								=	nullptr;
	m_geometry												=	nullptr;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
GeometryRenderElement::~GeometryRenderElement()
{
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void GeometryRenderElement::SetupGeometry( StaticGeometry* a_geometry , TUint32 a_startIndex , TUint32 a_count )
{
	m_geometry												=	a_geometry;
	m_startIndex											=	a_startIndex;
	m_indexCount											=	a_count;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void GeometryRenderElement::SetupMaterial( const ReferenceCountedPtr<Material>& a_material , TUint32 a_customFlags )
{
	m_material												=	a_material;
	m_materialFlags											=	a_customFlags;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void GeometryRenderElement::SetVertexParameters( const RhiConstantBuffer* a_constantBuffer )
{
	m_elementVertexParameters								=	a_constantBuffer;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void GeometryRenderElement::Render( RhiGraphicContext* a_context )
{
	if( ( m_material != nullptr ) && ( m_geometry != nullptr ) && ( m_elementVertexParameters != nullptr ) )
	{
		a_context->SetConstantBuffer( RHI_SHADER_TYPE_VERTEX_SHADER , VS_PARAMETER_SLOT_PER_DRAW , m_elementVertexParameters );

		// Setup the Material Correctly
		m_material->Apply( a_context , m_geometry->GetVertexLayout()->GetLayoutType() , m_materialFlags );
	
		m_geometry->Draw( a_context ,m_startIndex , m_indexCount );
	}
}
//-------------------------------------------------------------------------------------------------
