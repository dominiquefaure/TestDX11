#include "ShaderPermutation.h"


#ifdef _DEBUG
#include "ShaderPermutation.inl"
#endif


//---------------------------------------------------------------------------------------------
ShaderPermutation::ShaderPermutation()
{
	m_shaderType											=	SHADER_TYPE_NOT_SET;
	m_permutationID											=	0;

	m_vertexShader											=	NULL;
	m_pixelShader											=	NULL;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
ShaderPermutation::~ShaderPermutation()
{
	SAFE_DELETE( m_vertexShader );
	SAFE_DELETE( m_pixelShader );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void ShaderPermutation::Init( RhiGraphicDevice* a_device , RhiShaderType a_type , RhiShaderByteCode& a_byteCode , TUint64 a_permitationID )
{
	m_shaderType											=	a_type;
	m_permutationID											=	a_permitationID;

	// Create the correct shader
	switch( a_type )
	{
		case VERTEX_SHADER:
			m_vertexShader									=	a_device->CreateVertexShader( a_byteCode );
		break;
		case PIXEL_SHADER:
			m_pixelShader									=	a_device->CreatePixelShader( a_byteCode );
		break;
	}
}
//---------------------------------------------------------------------------------------------
