#ifndef __RHI_TEXTURE_ENUMS_H__
#define __RHI_TEXTURE_ENUMS_H__


// The different Textures Formats supported
enum RhiTextureFormat
{
	TEXTURE_FORMAT_R8G8B8A8						=	0, //standard RGBA 0.1
	TEXTURE_FORMAT_DEPTH_STENCIL,

	TEXTURE_FORMAT_DXT1,
	TEXTURE_FORMAT_DXT3,
	TEXTURE_FORMAT_DXT5,

	TEXTURE_FORMAT_UNKNOWN,
	TEXTURE_FORMAT_COUNT
/*
	TEXTURE_FORMAT_R32G32B32A32_TYPELESS       = 1,
	TEXTURE_FORMAT_R32G32B32A32_FLOAT          = 2,
	TEXTURE_FORMAT_R32G32B32A32_UINT           = 3,
	TEXTURE_FORMAT_R32G32B32A32_SINT           = 4,
	TEXTURE_FORMAT_R32G32B32_TYPELESS          = 5,
	TEXTURE_FORMAT_R32G32B32_FLOAT             = 6,
	TEXTURE_FORMAT_R32G32B32_UINT              = 7,
	TEXTURE_FORMAT_R32G32B32_SINT              = 8,
	TEXTURE_FORMAT_R16G16B16A16_TYPELESS       = 9,
	TEXTURE_FORMAT_R16G16B16A16_FLOAT          = 10,
	TEXTURE_FORMAT_R16G16B16A16_UNORM          = 11,
	TEXTURE_FORMAT_R16G16B16A16_UINT           = 12,
	TEXTURE_FORMAT_R16G16B16A16_SNORM          = 13,
	TEXTURE_FORMAT_R16G16B16A16_SINT           = 14,
	TEXTURE_FORMAT_R32G32_TYPELESS             = 15,
	TEXTURE_FORMAT_R32G32_FLOAT                = 16,
	TEXTURE_FORMAT_R32G32_UINT                 = 17,
	TEXTURE_FORMAT_R32G32_SINT                 = 18,
	TEXTURE_FORMAT_R32G8X24_TYPELESS           = 19,
	TEXTURE_FORMAT_D32_FLOAT_S8X24_UINT        = 20,
	TEXTURE_FORMAT_R32_FLOAT_X8X24_TYPELESS    = 21,
	TEXTURE_FORMAT_X32_TYPELESS_G8X24_UINT     = 22,
	TEXTURE_FORMAT_R10G10B10A2_TYPELESS        = 23,
	TEXTURE_FORMAT_R10G10B10A2_UNORM           = 24,
	TEXTURE_FORMAT_R10G10B10A2_UINT            = 25,
	TEXTURE_FORMAT_R11G11B10_FLOAT             = 26,
	TEXTURE_FORMAT_R8G8B8A8_TYPELESS           = 27,
	TEXTURE_FORMAT_R8G8B8A8_UNORM              = 28,
	TEXTURE_FORMAT_R8G8B8A8_UNORM_SRGB         = 29,
	TEXTURE_FORMAT_R8G8B8A8_UINT               = 30,
	TEXTURE_FORMAT_R8G8B8A8_SNORM              = 31,
	TEXTURE_FORMAT_R8G8B8A8_SINT               = 32,
	TEXTURE_FORMAT_R16G16_TYPELESS             = 33,
	TEXTURE_FORMAT_R16G16_FLOAT                = 34,
	TEXTURE_FORMAT_R16G16_UNORM                = 35,
	TEXTURE_FORMAT_R16G16_UINT                 = 36,
	TEXTURE_FORMAT_R16G16_SNORM                = 37,
	TEXTURE_FORMAT_R16G16_SINT                 = 38,
	TEXTURE_FORMAT_R32_TYPELESS                = 39,
	TEXTURE_FORMAT_D32_FLOAT                   = 40,
	TEXTURE_FORMAT_R32_FLOAT                   = 41,
	TEXTURE_FORMAT_R32_UINT                    = 42,
	TEXTURE_FORMAT_R32_SINT                    = 43,
	TEXTURE_FORMAT_R24G8_TYPELESS              = 44,
	TEXTURE_FORMAT_D24_UNORM_S8_UINT           = 45,
	TEXTURE_FORMAT_R24_UNORM_X8_TYPELESS       = 46,
	TEXTURE_FORMAT_X24_TYPELESS_G8_UINT        = 47,
	TEXTURE_FORMAT_R8G8_TYPELESS               = 48,
	TEXTURE_FORMAT_R8G8_UNORM                  = 49,
	TEXTURE_FORMAT_R8G8_UINT                   = 50,
	TEXTURE_FORMAT_R8G8_SNORM                  = 51,
	TEXTURE_FORMAT_R8G8_SINT                   = 52,
	TEXTURE_FORMAT_R16_TYPELESS                = 53,
	TEXTURE_FORMAT_R16_FLOAT                   = 54,
	TEXTURE_FORMAT_D16_UNORM                   = 55,
	TEXTURE_FORMAT_R16_UNORM                   = 56,
	TEXTURE_FORMAT_R16_UINT                    = 57,
	TEXTURE_FORMAT_R16_SNORM                   = 58,
	TEXTURE_FORMAT_R16_SINT                    = 59,
	TEXTURE_FORMAT_R8_TYPELESS                 = 60,
	TEXTURE_FORMAT_R8_UNORM                    = 61,
	TEXTURE_FORMAT_R8_UINT                     = 62,
	TEXTURE_FORMAT_R8_SNORM                    = 63,
	TEXTURE_FORMAT_R8_SINT                     = 64,
	TEXTURE_FORMAT_A8_UNORM                    = 65,
	TEXTURE_FORMAT_R1_UNORM                    = 66,
	TEXTURE_FORMAT_R9G9B9E5_SHAREDEXP          = 67,
	TEXTURE_FORMAT_R8G8_B8G8_UNORM             = 68,
	TEXTURE_FORMAT_G8R8_G8B8_UNORM             = 69,
	TEXTURE_FORMAT_BC1_TYPELESS                = 70,
	TEXTURE_FORMAT_BC1_UNORM                   = 71,
	TEXTURE_FORMAT_BC1_UNORM_SRGB              = 72,
	TEXTURE_FORMAT_BC2_TYPELESS                = 73,
	TEXTURE_FORMAT_BC2_UNORM                   = 74,
	TEXTURE_FORMAT_BC2_UNORM_SRGB              = 75,
	TEXTURE_FORMAT_BC3_TYPELESS                = 76,
	TEXTURE_FORMAT_BC3_UNORM                   = 77,
	TEXTURE_FORMAT_BC3_UNORM_SRGB              = 78,
	TEXTURE_FORMAT_BC4_TYPELESS                = 79,
	TEXTURE_FORMAT_BC4_UNORM                   = 80,
	TEXTURE_FORMAT_BC4_SNORM                   = 81,
	TEXTURE_FORMAT_BC5_TYPELESS                = 82,
	TEXTURE_FORMAT_BC5_UNORM                   = 83,
	TEXTURE_FORMAT_BC5_SNORM                   = 84,
	TEXTURE_FORMAT_B5G6R5_UNORM                = 85,
	TEXTURE_FORMAT_B5G5R5A1_UNORM              = 86,
	TEXTURE_FORMAT_B8G8R8A8_UNORM              = 87,
	TEXTURE_FORMAT_B8G8R8X8_UNORM              = 88,
	TEXTURE_FORMAT_R10G10B10_XR_BIAS_A2_UNORM  = 89,
	TEXTURE_FORMAT_B8G8R8A8_TYPELESS           = 90,
	TEXTURE_FORMAT_B8G8R8A8_UNORM_SRGB         = 91,
	TEXTURE_FORMAT_B8G8R8X8_TYPELESS           = 92,
	TEXTURE_FORMAT_B8G8R8X8_UNORM_SRGB         = 93,
	DXGI_FORMAT_BC6H_TYPELESS               = 94,
	DXGI_FORMAT_BC6H_UF16                   = 95,
	DXGI_FORMAT_BC6H_SF16                   = 96,
	DXGI_FORMAT_BC7_TYPELESS                = 97,
	DXGI_FORMAT_BC7_UNORM                   = 98,
	DXGI_FORMAT_BC7_UNORM_SRGB              = 99,
	DXGI_FORMAT_AYUV                        = 100,
	DXGI_FORMAT_Y410                        = 101,
	DXGI_FORMAT_Y416                        = 102,
	DXGI_FORMAT_NV12                        = 103,
	DXGI_FORMAT_P010                        = 104,
	DXGI_FORMAT_P016                        = 105,
	DXGI_FORMAT_420_OPAQUE                  = 106,
	DXGI_FORMAT_YUY2                        = 107,
	DXGI_FORMAT_Y210                        = 108,
	DXGI_FORMAT_Y216                        = 109,
	DXGI_FORMAT_NV11                        = 110,
	DXGI_FORMAT_AI44                        = 111,
	DXGI_FORMAT_IA44                        = 112,
	DXGI_FORMAT_P8                          = 113,
	DXGI_FORMAT_A8P8                        = 114,
	DXGI_FORMAT_B4G4R4A4_UNORM              = 115,
	DXGI_FORMAT_FORCE_UINT                  = 0xffffffff
*/

};


#endif