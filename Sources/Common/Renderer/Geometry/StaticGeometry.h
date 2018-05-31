#ifndef __RENDERER_GEOMETRY_STATIC_GEOMETRY_H__
#define __RENDERER_GEOMETRY_STATIC_GEOMETRY_H__

#include "../../Core/CoreIncludes.h"
#include "../../RHI/Includes.h"

class GeometryDataset;

/*
* Base class for the Different Geometry classes
*/
class StaticGeometry
{

public:

	StaticGeometry();
	~StaticGeometry();


	/*
	* Is this Geometry using index buffer?
	*/
	FORCE_INLINE TBool IsIndexed()const;

	/*
	* Number of indices if the geometry is indexed
	*/
	FORCE_INLINE TUint32 GetIndiceCount()const;

	/*
	* total number of vertices
	*/
	FORCE_INLINE TUint32 GetVertexCount()const;

	/*
	* Get the Type of primitive
	*/
	FORCE_INLINE RhiPrimitiveType GetPrimitiveType()const;

	/*
	* Get the VertexLayout to use with this Geometry
	*/
	FORCE_INLINE RhiVertexLayout* GetVertexLayout()const;


	/*
	 * Build this Static Geometry
	 */
	void Build( RhiGraphicDevice* a_device , const GeometryDataset* a_datas );


	/*
	* Set to the Graphic the information's stored inside this Geometry
	*
	* @param a_context		The Graphic context that will draw this Geometry
	*/
	void Apply( RhiGraphicContext* a_context );

	/*
	 * Draw the Geometry , Apply has to be called before
	 * Shader has to be set correctly before
	 */
	void ProcessDraw( RhiGraphicContext* a_context );


// Methods
private:

	/*
	 * Create the Index according to the Geometry data
	 */
	void CreateIndexBuffer( RhiGraphicDevice* a_device , const GeometryDataset* a_datas );

	/*
	 * Create the VertexBuffer according to the Geometry data
	 */
	void CreateVertexBuffer( RhiGraphicDevice* a_device , const GeometryDataset* a_datas );

// Fields
private:

	// is the geometry use index buffer?
	TBool					m_isIndexed;

	// data type of the Index Buffer
	RhiIndexBufferType		m_indexType;

	// number of vertices required to draw it using index buffer
	TUint32					m_indexCount;

	// number of different vertices
	TUint32					m_vertexCount;

	// Size of 1 vertex
	TUint32					m_vertexSize;

	// Buffers that store the Mesh datas.
	RhiVertexBuffer*		m_vertexBuffer;
	RhiIndexBuffer*			m_indexBuffer;

	// type used
	RhiPrimitiveType		m_primitiveType;

	RhiVertexLayout*		m_vertexLayout;

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "StaticGeometry.inl"
#endif



#endif