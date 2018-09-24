#ifndef __RENDERER_GEOMETRY_RENDER_ELEMENT_H__
#define __RENDERER_GEOMETRY_RENDER_ELEMENT_H__

#include "Core/CoreIncludes.h"
#include "RHI/Includes.h"

#include "Renderer/Resources/Includes.h"


/*
* Store all the required informations to render a Geometry
*/
class GeometryRenderElement
{
public:

	GeometryRenderElement();
	~GeometryRenderElement();

	/*
	* Set the Geometry Infos
	*/
	void SetupGeometry( StaticGeometry* a_geometry , TUint32 a_startIndex , TUint32 a_count );

	/*
	* Set the Material Infos
	*/
	void SetupMaterial( const ReferenceCountedPtr<Material>& a_material , TUint32 a_customFlags );

	/*
	* Set the Constant Buffer used in VertexShader
	*/
	void SetVertexParameters( const RhiConstantBuffer* a_constantBuffer );

	/*
	* Render the Geometry
	*/
	void Render( RhiGraphicContext* a_context );

private:

	// The Geometry to Render
	StaticGeometry*					m_geometry;

	// 1st index in the Geometry
	TUint32							m_startIndex;

	// number of indices to draw
	TUint32							m_indexCount;

	// reference to the Material to use
	ReferenceCountedPtr<Material>	m_material;

	// Custom flags for the Material
	TUint32							m_materialFlags;

	// Constant Buffer used for VertexShader
	const RhiConstantBuffer*		m_elementVertexParameters;
};

#endif