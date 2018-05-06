#ifndef __RHI_VERTEX_ELEMENT_DX11_H__
#define __RHI_VERTEX_ELEMENT_DX11_H__

#include "../../RhiEnums.h"
#include "../../../Core/CoreIncludes.h"

#include <d3d11.h>

/*
* Struct that store all the common properties for a VeterElement Type
*/
struct VertexElementTypeProperties
{
	//Name of the semantic used in HLSL
	std::string				m_semanticName;
	
	// Index if more than 1 element has the same semantic ( 4x4 Matric has 4 elements with the SemanticName Matrix and different index )
	unsigned int			m_semanticIndex;

	// format of the element in th Vertex Buffer
	DXGI_FORMAT				m_dataFormat;

	// Size in byte of the element
	TUint32					m_size;

	//get the String representing the declaration of the element in a VertexShader
	std::string				m_shaderDeclaration;
};


class VertexLayoutDX11;

/*
* Represent 1 Element of a Vertex
*/
class VertexElementDX11 
{
	friend class VertexLayoutDX11;

public:

	/*
	* get the Size in bytes of the element
	*/
	FORCE_INLINE TUint32 GetSize()const;

	/*
	* get teh Declaration for the vertex shader
	*/
	FORCE_INLINE std::string& GetShaderDeclaration()const;

private:

	VertexElementDX11();
	
	~VertexElementDX11();

	/*
	* Initialize this element properties
	*/
	void Init( RhiVertexElementType a_type , TUint32 a_slot , TUint32 a_offset );

	/*
	* Set an Input element descriptor properties according to this element values
	*/
	void SetElementDescriptor( D3D11_INPUT_ELEMENT_DESC* a_desc );

private:

	// Type of this Element
	RhiVertexElementType			m_type;

	// pointer to the Type property
	VertexElementTypeProperties*	m_typeProperties;

	// vertex Stream Slot the element is present
	TUint32							m_inputSlot;

	// Offset in the vertex Stram the element start
	TUint32							m_offset;
};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "VertexElementDX11.inl"
#endif


#endif