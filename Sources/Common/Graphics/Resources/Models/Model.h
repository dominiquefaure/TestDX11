#ifndef __RENDERER_RSOURCES_MODEL_H__
#define __RENDERER_RSOURCES_MODEL_H__

#include "Core/CoreIncludes.h"

#include "../Meshes/Includes.h"
#include"../Materials/Includes.h"

class GeometryRenderList;


struct StaticModelVertexConstants
{
	// The Mesh World Transform
	Matrix44	m_worldTransform;
};


/*
* Resource that represent a Model( Meshes + Materials )
*/
class Model : public ReferenceCounted
{
public:

	Model();
	virtual ~Model();

	/*
	* Set the Mesh to Diplay
	*/
	void SetMesh( const ReferenceCountedPtr<BaseMesh>& a_mesh );

	void SetMaterial( const ReferenceCountedPtr<Material>& a_material );

	/*
	* Prepare a 
	*/
	virtual void SetupDraw( GeometryRenderList* a_renderList , SConstantBuffer<StaticModelVertexConstants>* a_instanceCB );

private:

	// the Mesh to use
	ReferenceCountedPtr<BaseMesh>	m_mesh;

	// Instance of a Material
	MaterialInstance				m_material;
};

#endif