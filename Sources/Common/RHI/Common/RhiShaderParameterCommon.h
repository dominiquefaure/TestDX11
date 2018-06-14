#ifndef __RHI_SHADER_PARAMETER_COMMON_H__
#define __RHI_SHADER_PARAMETER_COMMON_H__

// witch slot of the VS Constant buffer to update
enum VSParameterSlot
{
	VS_PARAMETER_SLOT_PER_FRAME = 0,
	VS_PARAMETER_SLOT_PER_DRAW,

	VS_PARAMETER_SLOT_COUNT
};


// witch slot of the PS Constant buffer to update
enum PSParameterSlot
{
	PS_PARAMETER_SLOT_MATERIAL = 0,

	PS_PARAMETER_SLOT_COUNT
};


#define VS_PER_FRAME_CONSTANT_BUFFER_SIZE	256
#define VS_PER_DRAW_CONSTANT_BUFFER_SIZE	256

#define PS_MATERIAL_CONSTANT_BUFFER_SIZE	256

#endif