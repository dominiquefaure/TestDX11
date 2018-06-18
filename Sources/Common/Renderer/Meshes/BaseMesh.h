#ifndef __RENDERER_AMESH_H__
#define __RENDERER_AMESH_H__

#include "../../Core/CoreIncludes.h"
#include "../../RHI/Includes.h"

//#include "MeshPart.h"

class MeshPart;
class ShaderProgram;

/*
* Base class for all meshes
*/

class BaseMesh
{

public:

	BaseMesh();
	virtual ~BaseMesh();


	void LoadFromJSon( const char* a_path );

	/*
	 * Load the Geometry data from a JSon node
	 */
	void LoadFromJSon( JSonNode& a_rootNode );


	void BuildRenderData( RhiGraphicDevice* a_device , bool a_freeSourceData = true );

	/*
	* Draw this Part
	*/
	void Draw( RhiGraphicContext* a_context  , ShaderProgram* a_program , TUint64 a_customFlags );

// Methods
private:

	/*
	* Load all the parts that define the mesh geometry
	*/
	void LoadParts( JSonNode& a_rootNode );


// Fields
private:

	// number of Parts that compose this mesh
	TUint32		m_partCount;

	// list of mesh part that compose this mesh
	MeshPart*	m_partList;

};

#endif