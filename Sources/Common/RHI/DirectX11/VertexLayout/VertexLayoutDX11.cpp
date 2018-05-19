#include "VertexLayoutDX11.h"
#include "VertexElementDX11.h"

#include "../GraphicDeviceDX11.h"


#ifdef _DEBUG
#include "VertexLayoutDX11.inl"
#endif


static const char g_dummyShaderHeader[] =
	"struct VSIN {                      \n \
	";

static const char g_dummyShaderFooter[] =
	"};                                 \n \
	struct VSOUT                        \n \
	{                                   \n \
	float4 pos : SV_POSITION;			\n \
	};                                  \n \
	VSOUT VSMain(VSIN input)            \n \
	{                                   \n \
	VSOUT output;						\n \
	output.pos = float4(0,0,0,0);		\n \
	return output;						\n \
	}                                   \n \
	";



//-----------------------------------------------------------------------------------------------
VertexLayoutDX11::VertexLayoutDX11()
{
	m_inputLayout											=	NULL;
	m_streamSizes											=	NULL;
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
VertexLayoutDX11::~VertexLayoutDX11()
{
	// Get the Number of Elements
	int t_count												=	m_elements.size();
	for( int i = 0 ; i < t_count ; i ++ )
	{
		SAFE_DELETE( m_elements[ i ] );
	}
	m_elements.clear();


	SAFE_DELETE_ARRAY( m_streamSizes );
	SAFE_DELETE_ARRAY( m_inputElementDesc );
	SAFE_RELEASE( m_inputLayout );

}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
void VertexLayoutDX11::Build( RhiVertexLayoutTypeKey a_key , GraphicDeviceDX11* a_device )
{
	m_key													=	a_key;

	InitStreams( VERTEX_LAYOUT_MAX_STREAM );

	for( int i = 0 ; i < RHI_VERTEX_ELEMENT_TYPE_COUNT ; i ++ )
	{
		if( ISBITSET( a_key , i ) )
		{
			PushElement( 0 , (RhiVertexElementType) i );
		}
	}

	Build( a_device );
}
//-----------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------
void VertexLayoutDX11::InitStreams( int a_count )
{
	m_streamCount											=	a_count;

	m_streamSizes											=	new TUint32[ m_streamCount ];
	for( int i = 0 ; i < m_streamCount ; i ++ )
	{
		m_streamSizes[ i ]									=	0;
	}
}
//-----------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------
void VertexLayoutDX11::PushElement( TUint32 a_slot , RhiVertexElementType a_type )
{
	// Setupt the vertex element
	VertexElementDX11* t_element							=	new VertexElementDX11();
	t_element->Init( a_slot , a_type , m_streamSizes[ a_slot ] );

	// increase the matching stream size
	m_streamSizes[ a_slot ]									+=	t_element->GetSize();

	// Add the Element to the List
	m_elements.push_back( t_element );
}
//-----------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------
void VertexLayoutDX11::Build( GraphicDeviceDX11* a_device )
{
	ComputeInputElementDesc();
	GenerateShaderByteCode();
	GenerateInputLayout( a_device );
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
void VertexLayoutDX11::ComputeInputElementDesc()
{
	// Get the Number of Elements
	int t_count												=	m_elements.size();

	// Create the Array
	m_inputElementDesc										=	new D3D11_INPUT_ELEMENT_DESC[ t_count ];

	for( int i = 0 ; i < t_count ; i ++ )
	{
		m_elements[ i ]->SetInputDescriptor( &m_inputElementDesc[ i ] );
	}
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
void VertexLayoutDX11::GenerateShaderByteCode()
{
	// Get the Number of Elements
	int t_count												=	m_elements.size();

	std::string t_sourceCode								=	g_dummyShaderHeader;

	for( int i = 0 ; i < t_count ; i ++ )
	{
		t_sourceCode										+=	m_elements[ i ]->GetShaderDeclaration();
	}

	t_sourceCode											+=	g_dummyShaderFooter;

	// Compile the Shader
	m_byteCode.Compile( RHI_SHADER_TYPE_VERTEX_SHADER , t_sourceCode , 0 , "VSMain" );

}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
void VertexLayoutDX11::GenerateInputLayout( GraphicDeviceDX11* a_device )
{
	m_inputLayout											=	a_device->CreateInputLayout( m_inputElementDesc , m_elements.size() , m_byteCode );
}
//-----------------------------------------------------------------------------------------------
