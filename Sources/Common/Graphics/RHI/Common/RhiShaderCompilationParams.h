#ifndef __RHI_SHADER_COMPILATION_PARAMS_H__
#define __RHI_SHADER_COMPILATION_PARAMS_H__

#include <string>
#include "../RhiEnums.h"
#include "../../../Core/CoreIncludes.h"

enum RhiShaderCompilationMacros
{
	SHADER_MACRO_NONE	=	-1,

	// Macro for VertexLayouts
	SHADER_MACRO_VERTEX_COLOR = 0,
	SHADER_MACRO_VERTEX_TEXTURED,

	// start of Engine options
	SHADER_MACRO_DUMMY_COLOR =8,
	SHADER_MACRO_USE_PRE_MULTIPLY	=	9,
	SHADER_MACRO_COUNT
};


// Struct that store the different parameters to provide to the Compiler
struct RhiShaderCompilationParams
{
	RhiShaderType	m_shaderType;

	std::string		m_entryPoint;

	TUint64			m_permutationFlags;
};


#endif