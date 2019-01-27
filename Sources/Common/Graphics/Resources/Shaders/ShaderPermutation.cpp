#include "ShaderPermutation.h"


#ifdef _DEBUG
#include "ShaderPermutation.inl"
#endif


//---------------------------------------------------------------------------------------------
ShaderPermutation::ShaderPermutation()
{
	m_shaderType											=	RHI_SHADER_TYPE_NOT_SET;
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
		case RHI_SHADER_TYPE_VERTEX_SHADER:
			m_vertexShader									=	a_device->CreateVertexShader( a_byteCode );
		break;
		case RHI_SHADER_TYPE_PIXEL_SHADER:
			m_pixelShader									=	a_device->CreatePixelShader( a_byteCode );
		break;
	}

	// generate the reflection info specifics to this Permutation
	m_relectionInfos										=	a_byteCode.GenerateRelectionInfos();
}
//---------------------------------------------------------------------------------------------
