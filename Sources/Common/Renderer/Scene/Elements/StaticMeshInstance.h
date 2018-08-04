#ifndef __STATIC_MESH_INSTANCE_H__
#define __STATIC_MESH_INSTANCE_H__

#include "RenderSceneElement.h"
#include "../../Resources/Includes.h"
#include "../../../Core/CoreIncludes.h"

struct StaticMeshVertexConstants
{
	// The Mesh World Transform
	Matrix44	m_worldTransform;
};

class StaticMeshInstance : public RenderSceneElement
{
public:

	StaticMeshInstance();
	virtual ~StaticMeshInstance();

	/*
	* Init the Instance Properties
	*/
	void Init( RhiGraphicDevice* a_device , StaticMesh* a_mesh );

	/*
	* Set the Mesh to Diplay
	*/
	void SetMesh( const ReferenceCountedPtr<StaticMesh>& a_mesh );

	void SetMaterial( Material* a_material );

	/*
	* Get the Material Instance present at the given Index
	*/
//	MaterialInstance* GetMaterial( int a_index );

	/*
	* Draw this Object
	*/
	virtual void Draw( RhiGraphicContext* a_context );

private:

	//Reference to the Mesh instanced
	ReferenceCountedPtr<StaticMesh>	m_mesh;

	// reference to the Material to use
	ReferenceCountedPtr<Material>	m_material;

	StaticMeshVertexConstants					m_vertexConstants;
	SConstantBuffer<StaticMeshVertexConstants>	m_vertexConstantBuffer;
};

#endif