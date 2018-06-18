#ifndef __RENDEREDER_MESH_PART_H__
#define __RENDEREDER_MESH_PART_H__

#include "../../Core/CoreIncludes.h"
#include "../../RHI/Includes.h"



class GeometryDataset;
class StaticGeometry;
class ShaderProgram;

class MeshPart
{
public:

	MeshPart();
	~MeshPart();



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

private:

	// index in the MaterialSet of the material to use
	TUint32				m_materialIndex;

	// does this part cast shadow?
	TBool				m_castShadow;

	// object that store the raw data. in runime mode, used only during loading time
	GeometryDataset*	m_sourceData;

	// store the Vb and IB created from the raw data
	StaticGeometry*		m_renderGeometry;
};


#endif