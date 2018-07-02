#ifndef __RENDEREDER_MESH_PART_H__
#define __RENDEREDER_MESH_PART_H__

#include "../../Core/CoreIncludes.h"
#include "../../RHI/Includes.h"



class ShaderProgram;

class FbxMeshPartImporter;

class MeshPart
{
	friend class FbxMeshPartImporter;

public:

	MeshPart();
	~MeshPart();

	/*
	* Get the Start index of this part in the Mesh Geometry
	*/
	FORCE_INLINE TUint32 GetStartIndex()const;

	/*
	* Get the number of index that compose this part
	*/
	FORCE_INLINE TUint32 GetIndexCount()const;

	/*
	* Get the index of the Material to use
	*/
	FORCE_INLINE TUint32 GetMaterialIndex()const;

	/*
	* Does this Part cast shadow?
	*/
	FORCE_INLINE TBool IsCastShadow()const;

	/*
	* Set the Range of Index in the index buffer used to draw this Part
	*/
	void SetIndexRange( TUint32 a_startIndex , TUint32 a_count );

	/*
	 * Load the Geometry data from a JSon node
	 */
	void LoadFromJSon( JSonNode& a_partNode );

	/*
	* Draw this Part
	*/
	void Draw( RhiGraphicContext* a_context  , ShaderProgram* a_program , TUint64 a_customFlags );

private:

	// 1st index in the global index buffer of this part
	TUint32				m_startIndex;

	// number of Index representing this Part
	TUint32				m_indexCount;

	// index in the MaterialSet of the material to use
	TUint32				m_materialIndex;

	// does this part cast shadow?
	TBool				m_castShadow;

};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "MeshPart.inl"
#endif


#endif