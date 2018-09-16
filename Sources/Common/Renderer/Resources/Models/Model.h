#ifndef __RENDERER_RSOURCES_MODEL_H__
#define __RENDERER_RSOURCES_MODEL_H__

#include "Core/CoreIncludes.h"

#include "../Meshes/Includes.h"
#include"../Materials/Includes.h"


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
	* Draw this Model
	*/
	virtual void Draw( RhiGraphicContext* a_context );


private:

	// the Mesh to use
	ReferenceCountedPtr<BaseMesh>	m_mesh;

	// reference to the Material to use
	ReferenceCountedPtr<Material>	m_material;

};

#endif