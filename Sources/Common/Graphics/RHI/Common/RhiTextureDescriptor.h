
#ifndef __RHI_TEXTURE_DESCRIPTOR_H__
#define __RHI_TEXTURE_DESCRIPTOR_H__

#include "Enums/Includes.h"


/*
* Describe a Texture to be created
*/
struct RhiTextureDescriptor
{
	TUint32				m_width;		// Width of the Texture
	TUint32				m_height;			// Height of the Texture
	RhiTextureFormat	m_format;		// Pixel Format

	RhiBufferUsage		m_usage;		// intended usage of the Texture, how much time it will be updated. Selecting the most appropriate mode can increase performances a lot
	RhiShaderUsage		m_shaderUsage;	// how the texture can be acceced by the Shaders
};



#endif