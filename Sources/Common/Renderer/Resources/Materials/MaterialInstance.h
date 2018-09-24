#ifndef __RENDERER_RESOURCES_MATERIAL_INSTANCE_H__
#define __RENDERER_RESOURCES_MATERIAL_INSTANCE_H__

/*
* Instance of a Material
* handle reference counting to the Material
* Allow to ovveride some parameters if needed
*/

#include "Core/CoreIncludes.h"

#include "Material.h"


class GeometryRenderElement;

class MaterialInstance
{

public:

	MaterialInstance();
	~MaterialInstance();

	/*
	* Is there a Material Set?
	*/
	FORCE_INLINE TBool IsMaterialSet()const;

	/*
	* Set the Owner Material
	*/
	void SetMaterial( const ReferenceCountedPtr<Material>& a_material );


	/*
	* Apply the Material to the Context
	*/
	void Apply( RhiGraphicContext* a_context , RhiVertexLayoutType a_layoutType , TUint64 a_customFlags );

	/*
	* Setup the RenderElement
	*/
	void Setup( GeometryRenderElement* a_element );

private:

	// reference to the Material to use
	ReferenceCountedPtr<Material>	m_material;


};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "MaterialInstance.inl"
#endif


#endif
