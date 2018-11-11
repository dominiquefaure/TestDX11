#ifndef __RHI_RESOURCES_ENUMS_H__
#define __RHI_RESOURCES_ENUMS_H__

enum RhiBufferUsage
{
	RHI_BUFFER_USAGE_IMMUTABLE	=	0,	// never Change
	RHI_BUFFER_USAGE_STATIC,			// CPU can update it time to time ( less than 1 per x ticks )
	RHI_BUFFER_USAGE_DYNAMIC,			// CPU will update it really frequently( every ticks )

	RHI_BUFFER_USAGE_COUNT
};

// how can a Resource be bind to a Shader
enum RhiResourceBindType
{
	RHI_RESOURCE_BIND_VERTEX_BUFFER = 0,
	RHI_RESOURCE_BIND_INDEX_BUFFER,
	RHI_RESOURCE_BIND_CONSTANT_BUFFER,

	RHI_RESOURCE_BIND_RESOURCE_READ,	// the resource be be only read
	RHI_RESOURCE_BIND_RENDER_TARGET, // Can be used as RenderTarget or as Resource Read

	RHI_RESOURCE_BIND_COUNT
};

enum RhiIndexBufferType
{
	INDEX_BUFFER_TYPE_INVALID	=	-1,
	INDEX_BUFFER_TYPE_16		=	0,
	INDEX_BUFFER_TYPE_32,
};

enum RhiPrimitiveType
{
	RHI_PRIMITIVE_TYPE_INVALID		=	-1,
	RHI_PRIMITIVE_TYPE_POINT_LIST	=	0,
	RHI_PRIMITIVE_TYPE_LINE_LIST,
	RHI_PRIMITIVE_TYPE_LINE_STRIP,
	RHI_PRIMITIVE_TYPE_TRIANGLE_LIST,
	RHI_PRIMITIVE_TYPE_TRIANGLE_STRIP,


	RHI_PRIMITIVE_TYPE_COUNT
};


// how can a Resource be bind to a Shader
enum RhiShaderUsage
{
	SHADER_USAGE_VERTEX_BUFFER = 0,
	SHADER_USAGE_INDEX_BUFFER,
	SHADER_USAGE_CONSTANT_BUFFER,

	SHADER_USAGE_RESOURCE_READ,	// the resource be be only read
	SHADER_USAGE_RENDER_TARGET, // Can be used as RenderTarget or as Resource Read
	SHADER_USAGE_DEPTH_STENCIL,

	SHADER_USAGE_COUNT
};


#endif