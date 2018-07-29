#ifndef __RENDERER_GEOMETRY_DATASET_H__
#define __RENDERER_GEOMETRY_DATASET_H__

#include "../../Core/CoreIncludes.h"
#include "../../RHI/Includes.h"

class FbxMeshPartImporter;
class BaseMesh;

class GeometryDataset
{
	friend class FbxMeshPartImporter;
	friend class BaseMesh;

public:

	GeometryDataset();
	~GeometryDataset();

	/*
	 * Get the Tyupe of Primitive used
	 */
	FORCE_INLINE RhiPrimitiveType GetPrimitiveType()const;

	/*
	* Is this Geometry using index buffer?
	*/
	FORCE_INLINE TBool IsIndexed()const;

	/*
	* Get the number of Indices
	*/
	FORCE_INLINE TUint32 GetIndiceCount()const;

	/*
	 *Get the Data type used to store index buffer
	 */
	FORCE_INLINE RhiIndexBufferType GetIndexBufferType()const;

	/*
	* Get the IndexBuffer
	*/
	FORCE_INLINE void* GetIndexBuffer()const;



	/*
	 * Get the Type of Vertices
	 */
	FORCE_INLINE RhiVertexLayoutType GetVerticeType()const;

	/*
	* Get the number of vertices
	*/
	FORCE_INLINE TUint32 GetVerticeCount()const;

	/*
	* Get the Size of 1 Vertice
	*/
	FORCE_INLINE TUint32 GetVerticeSize()const;

	/*
	* Get the VertexBuffer
	*/
	FORCE_INLINE TFloat32* GetVertexBuffer()const;




	void LoadFromJSon( const char* a_path );

	/*
	 * Load the Geometry data from a JSon node
	 */
	void LoadFromJSon( const JSonNode* a_rootNode );


	/*
	 * Create the Index Buffer
	 * if data is not null, they will be copied, else all the indices are initialized to 0
	 */
	void CreateIndexBuffer( TUint32 a_size , TUint32* a_datas = NULL );

	/*
	 * Update an indice into the index Buffer
	 */
	void SetIndiceAt( TUint32 a_index , TUint32 a_indice );



	/*
	 * Create the VertexBuffer
	 */
	void CreateVertexBuffer( RhiVertexLayoutType a_layout , TUint32 a_vetexSize , TUint32 a_vertexCount , TFloat32* a_initialDatas = NULL );

	/*
	 * Create the VertexBuffer
	 */
	void CreateVertexBuffer( RhiVertexLayout* a_layout , TUint32 a_vertexCount , TFloat32* a_initialDatas = NULL );

	/*
	 * Set a Vertice Content. the Array has to be at the same size of a Vertice
	 */
	void SetVerticeAt( int a_vertice , float* a_data );

	/*
	 * Set the Full Vertex Buffer content. Size has to be the same as the VertexBuffer created
	 */
	void SetVertices( float* a_datas , int a_size );

// Methods
private:


	/*
	* Load the IndexBuffer content from a JSon Node
	*
	* @param a_indexBufferNode	Node that store the indexbuffer informations
	*/
	void LoadIndexBuffer( const JSonNode* a_indexBufferNode );

	/*
	* Load the VertexBuffer content from a JSon Node
	*
	* @param a_vertexBufferNode	Node that store the vertexBuffer informations
	*/
	void LoadVertexBuffer( const JSonNode* a_vertexBufferNode );

	/*
	* Serialize the data to the given JSon node
	*/
	void Serialize( JSonNode* a_partNode );

	/*
	* Serialize the IndexBuffer content to the JSonNode
	*/
	void SerializeIndexBuffer( JSonNode* a_node );

	/*
	* Serialize the VertexBuffer content to the JSonNode
	*/
	void SerializeVertexBuffer( JSonNode* a_node );


// Fields
private:

	// is the geometry use index buffer?
	TBool					m_isIndexed;

	// Primitive type used
	RhiPrimitiveType		m_primitiveType;

	// data type of the Index Buffer
	RhiIndexBufferType		m_indexType;

	// number of vertices required to draw it using index buffer
	TUint32					m_indexCount;

	// The index buffer, either int16 or int32 depending of the type
	TUint16*				m_indexBuffer16;
	TUint32*				m_indexBuffer32;


	RhiVertexLayoutType		m_vertexLayoutType;

	// number of different vertices
	TUint32					m_vertexCount;

	// Size of 1 vertex
	TUint32					m_vertexSize;

	// Array that store the Vertex data
	float*					m_vertexBuffer;
};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "GeometryDataset.inl"
#endif


#endif