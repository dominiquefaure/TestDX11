#include "VertexElementDX11.h"

#include <assert.h>

#ifdef _DEBUG
#include "VertexElementDX11.inl"
#endif

VertexElementTypeProperties g_vertexElementTypeProperties[]
{
	{"POSITION", 0 , DXGI_FORMAT_R32G32B32_FLOAT , 12 , "float3 position : POSITION;\n" },
	{"COLOR", 0 , DXGI_FORMAT_R32G32B32A32_FLOAT , 16 , "float4 color: COLOR;\n" },
	{"TEXTCOORD", 0 , DXGI_FORMAT_R8G8_UNORM , 8 , "float2 texCoord: TEXTCOORD;\n" },

};


//-------------------------------------------------------------------------------------------------
VertexElementDX11::VertexElementDX11()
{
	m_typeProperties										=	NULL;
	m_inputSlot												=	0;
}
//-------------------------------------------------------------------------------------------------
	
//-------------------------------------------------------------------------------------------------
VertexElementDX11::~VertexElementDX11()
{
	m_typeProperties										=	NULL;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void VertexElementDX11::Init( TUint32 a_inputSlot , RhiVertexElementType a_type , TUint32 a_offset )
{
	m_type													=	a_type;
	m_inputSlot												=	a_inputSlot;
	m_offset												=	a_offset;

	m_typeProperties										=	&g_vertexElementTypeProperties[ a_type ];
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void VertexElementDX11::SetInputDescriptor( D3D11_INPUT_ELEMENT_DESC* a_desc )
{
	a_desc->SemanticName									=	m_typeProperties->m_semanticName.c_str();
	a_desc->SemanticIndex									=	m_typeProperties->m_semanticIndex;
	a_desc->Format											=	m_typeProperties->m_dataFormat;

	// Hard Coded for the Moment , used for Instancing
	a_desc->InputSlotClass									=	D3D11_INPUT_PER_VERTEX_DATA;
	a_desc->InstanceDataStepRate							=	0;

	a_desc->InputSlot										=	m_inputSlot;
	a_desc->AlignedByteOffset								=	m_offset;
}
//-----------------------------------------------------------------------------------------------
