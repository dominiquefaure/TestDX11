#include "MaterialInstance.h"

#include "Renderer/Scene/Rendering/Includes.h"

#ifdef _DEBUG
#include "MaterialInstance.inl"
#endif


//------------------------------------------------------------------------------------
MaterialInstance::MaterialInstance()
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
MaterialInstance::~MaterialInstance()
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void MaterialInstance::SetMaterial( const ReferenceCountedPtr<Material>& a_material )
{
	m_material												=	a_material;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void MaterialInstance::Apply( RhiGraphicContext* a_context , RhiVertexLayoutType a_layoutType , TUint64 a_customFlags )
{
	if( m_material != nullptr )
	{
		m_material->Apply( a_context ,  a_layoutType , a_customFlags );
	}
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void MaterialInstance::Setup( GeometryRenderElement* a_element )
{
	a_element->SetupMaterial( m_material , 0 );
}
//------------------------------------------------------------------------------------
