#ifndef __RHI_VERTEX_LAYOUT_DX11_H__
#define __RHI_VERTEX_LAYOUT_DX11_H__

#include <d3d11.h>

#include "../../../Core/CoreIncludes.h"
#include "../../Common/Includes.h"
#include "../../RhiEnums.h"

#include "../Shaders/ShaderByteCodeDX11.h"

// number max of Stream that canb e used to generate a layout
#define VERTEX_LAYOUT_MAX_STREAM	4


class GraphicDeviceDX11;
class VertexElementDX11;
class VertexLayoutManagerDX11;

class VertexLayoutDX11
{
	friend class VertexLayoutManagerDX11;

protected:

	VertexLayoutDX11();
	virtual ~VertexLayoutDX11();
	
// Methods
public:

	/*
	* Get the number of Elements present in this Vertex Layout
	*/
	FORCE_INLINE TUint32 GetElementCount()const;

	/*
	* Get the type of the Vertex Layout
	*/
	FORCE_INLINE RhiVertexLayoutType GetLayoutType()const;

	/*
	* Get the Key that identify this layout and the elements that compose it
	*/
	FORCE_INLINE RhiVertexLayoutTypeKey	GetLayoutKey()const;

	/*
	* Get the DX11 Input Layout matching this VertexLayout
	*/
	FORCE_INLINE ID3D11InputLayout* GetInputLayout();


	/*
	* Build the Vertex Layout
	*
	* @param a_key		Unique key identifier to generate a VertexLayout
	* @param a_device	The device that allow to create the input layout on GPU
	*/
	void Build( RhiVertexLayoutType a_type , RhiVertexLayoutTypeKey a_key , GraphicDeviceDX11* a_device );

// Methods
private:

	void InitStreams( int a_count );


	/*
	* Add a Vertex Element to the Layout
	*/
	void PushElement( TUint32 a_inputSlot , RhiVertexElementType a_type );

	/*
	* Build the Vertex Layout
	*
	* @param a_device	The device that allow to create the input layout on GPU
	*/
	void Build( GraphicDeviceDX11* a_device );

	/*
	* Compute the Dx InputElement Desc according to the different elemetns pushed
	*/
	void ComputeInputElementDesc();

	/*
	* Generate the Vertex Shader Byte code matching this Layout
	*/
	void GenerateShaderByteCode();

	/*
	* Generate the Input Layout from the Input DEclaration and compiled byte code
	*/
	void GenerateInputLayout( GraphicDeviceDX11* a_device );

// Fields
private:

	// Get the vertex Layout type
	RhiVertexLayoutType				m_type;

	// Key that identify this Layout
	RhiVertexLayoutTypeKey			m_key;

	// List of Vertex elements that compose this Layout
	std::vector<VertexElementDX11*>	m_elements;

	// Number of Vertex Stream used
	TUint32							m_streamCount;

	// Size of the Different vertex Stream used
	TUint32*						m_streamSizes;

	// The Vertex Elements Desc in DX format
	D3D11_INPUT_ELEMENT_DESC*		m_inputElementDesc;

	// shader byte code mathcing this layout
	ShaderByteCodeDX11				m_byteCode;

	// DX input Layout to use for this VertexLayout
	ID3D11InputLayout*				m_inputLayout;
};


// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "VertexLayoutDX11.inl"
#endif


#endif
