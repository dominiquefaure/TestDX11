#ifndef __RHI_VERTEX_ELEMENT_DX11_H__
#define __RHI_VERTEX_ELEMENT_DX11_H__

#include "../../RhiEnums.h"
#include "../../../Core/CoreIncludes.h"

#include <d3d11.h>

#include "../../../Core/Base/BaseDataTypes.h"
#include "../../../Core/CoreMacros.h"
#include "../../RhiEnums.h"

class VertexLayoutManagerDX11;
class VertexLayoutDX11;

/*
* Struct that store all the common properties for a VeterElement Type
*/
struct VertexElementTypeProperties
{
	//Name of the semantic used in HLSL
	std::string				m_semanticName;
	
	// Index if more than 1 element has the same semantic ( 4x4 Matric has 4 elements with the SemanticName Matrix and different index )
	TUint32					m_semanticIndex;

	// format of the element in th Vertex Buffer
	DXGI_FORMAT				m_dataFormat;

	// Size in Bytes of the Element
	TUint32					m_size;

	//get the String representing the declaration of the element in a VertexShader
	std::string				m_shaderDeclaration;
};

/*
* Represent 1 Element of a Vertex
*/
class VertexElementDX11 
{
	friend class VertexLayoutManagerDX11;
	friend class VertexLayoutDX11;

public:

	/*
	* Get the Size in bytes of the Vertex Element
	*/
	FORCE_INLINE TUint32 GetSize()const;

	/*
	* Get the String representing this Element Declaration inside Vertex Shader input
	*/
	FORCE_INLINE const std::string& GetShaderDeclaration()const;

private:

	VertexElementDX11();
	
	~VertexElementDX11();

	/*
	* Set the Type that Identify this VertexElement
	*/
	void Init( TUint32 a_inputSlot , RhiVertexElementType a_type , TUint32 a_offset );

	/*
	* Set the common properties of the Input Element Desc, that will represent this VertexElement
	*/
	void SetInputDescriptor( D3D11_INPUT_ELEMENT_DESC* a_desc );



private:

	// Type of this Element
	RhiVertexElementType			m_type;

	// Stream Input Slot
	TUint32							m_inputSlot;

	// Start Offset in the VertexStream of the Element
	TUint32							m_offset;

	// VertexElement Properties
	VertexElementTypeProperties*	m_typeProperties;
};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "VertexElementDX11.inl"
#endif


#endif