#ifndef __RENDERER_GEOMETRY_STATIC_GEOMETRY_H__
#define __RENDERER_GEOMETRY_STATIC_GEOMETRY_H__

#include "../../Core/CoreIncludes.h"
#include "../../RHI/Includes.h"


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
	FORCE_INLINE TUint32 GetVerticeCount()const;

	/*
	* Get the Type of primitive
	*/
	FORCE_INLINE RhiPrimitiveType GetPrimityveType()const;


	/*
	* Get the Vertex layout used
	*/
	FORCE_INLINE RhiVertexLayout* GetVertexLayout()const;

// Methods
public:

	/*
	* Init a Static non indexed Geometry
	*/
	void Init( RhiGraphicDevice* a_device , RhiPrimitiveType a_type , void* a_vertexBuffer, TUint32 a_vertexSize , TUint32 a_vertexCount );
	
	/*
	* Init an Indexed Geometry
	*/
	void Init( RhiGraphicDevice* a_device , RhiPrimitiveType a_type , void* a_vertexBuffer, TUint32 a_vertexSize , TUint32 a_vertexCount , RhiIndexBufferType a_indexType , void* a_indiceDatas , TUint32 a_indexCount );


	/*
	* Apply this Geometry settings but not display it
	*/
	void Apply( RhiGraphicContext* a_context );

	/*
	* Draw the Geometry
	*/
	void Draw( RhiGraphicContext* a_context );

	/*
	* Load geometry content from a File
	*/
	void LoadFromJSon( RhiGraphicDevice* a_device , const char* a_path );
			
	/*
	* Load geometry content from a JSon node
	*/
	void LoadFromJSon( RhiGraphicDevice* a_device , JSonNode& a_rootNode );

// Methods
private:

	/*
	* Create teh VertexBuffer
	*/
	void SetVertexBuffer( RhiGraphicDevice* a_device , TUint32 a_vertexSize , TUint32 a_vertexCount , void* a_vertexBuffer );

	/*
	* Init the index buffer.
	*/
	void SetIndexBuffer( RhiGraphicDevice* a_device , RhiIndexBufferType a_type , TUint32 a_count , void* a_datas );

	/*
	* try Load vertexBuffer content from Geometry root JSon node
	*/
	bool TryLoadVertexBuffer( RhiGraphicDevice* a_device , JSonNode& a_rootNode );

	void LoadVertexBufferContent( RhiGraphicDevice* a_device , JSonNode& a_vertexBufferNode );

	/*
	* try to Load indexBuffer content from Geometry root JSon node
	*/
	void TryLoadIndexBuffer( RhiGraphicDevice* a_device , JSonNode& a_rootNode );

	/*
	* Load indexBuffer content from a JSon node storing the indexBuffer content
	*/
	void LoadIndexBufferContent( RhiGraphicDevice* a_device , JSonNode& a_indexBufferNode );

	/*
	* Load the VertexLayout from the JSon node
	*/
	void LoadVertexLayout( RhiGraphicDevice* a_device , JSonNode& a_rootNode );

// Fields
private:

	// is the geometry use index buffer?
	TBool					m_isIndexed;

	// number of vertices required to draw it using index buffer
	TUint32					m_indexCount;

	// number of different vertices
	TUint32					m_verticeCount;

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