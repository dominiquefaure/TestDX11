#ifndef __RENDERER_AMESH_H__
#define __RENDERER_AMESH_H__

#include "Core/CoreIncludes.h"
#include "Graphics/RHI/Includes.h"

//#include "MeshPart.h"

class MeshPart;
class ShaderProgram;

class GeometryDataset;
class StaticGeometry;

class FbxMeshImporter;

class GeometryRenderElement;

/*
* Base class for all meshes
*/

class BaseMesh : public Asset
{
	friend class FbxMeshImporter;

public:

	BaseMesh();
	virtual ~BaseMesh();

	/*
	* Draw this Part
	*/
	void Draw( RhiGraphicContext* a_context );

	/*
	* Draw on;ly 1 part of this Mesh
	*/
	void DrawPart( TUint32 a_partIndex , RhiGraphicContext* a_context );


	/*
	* Setup the RenderElement
	*/
	void Setup( GeometryRenderElement* a_element );

	/*
	* Serialize this Mesh to a JSON file
	*/
	void SerializeToJSon( const char* a_path );

	void BuildRenderData( RhiGraphicDevice* a_device , bool a_freeSourceData = true );

protected:
	/*
	 * Load the Geometry data from a JSon node
	 */
	virtual void LoadFromJSon( const JSonNode* a_rootNode );



// Methods
private:

	/*
	* Create the Array that store the different parts
	*/
	void CreateParts( TUint32 a_count );

	/*
	* Load all the parts that define the mesh geometry
	*/
	void LoadParts( const JSonNode* a_rootNode );

	/*
	* Load the Geometry data from JSon file
	*/
	void LoadGeometryDatas( const JSonNode* a_rootNode );


	/*
	* Serialize all the Parts to a Root Node
	*/
	void SerializeParts( JSonNode* a_rootNode );

	/*
	* Serialize the Geometry datas
	*/
	void SerializeGeometryDatas( JSonNode* a_rootNode );


// Fields
private:

	// number of Parts that compose this mesh
	TUint32				m_partCount;

	// list of mesh part that compose this mesh
	MeshPart*			m_partList;


	// object that store the raw data. in runime mode, used only during loading time
	GeometryDataset*	m_sourceData;

	// store the Vb and IB created from the raw data
	StaticGeometry*		m_renderGeometry;

};

#endif