#ifndef __DDS_TEXTURE_LOADER_H__

#include "Core/CoreIncludes.h"
#include "Graphics/RHI/Includes.h"

#include "../Texture2D.h"


/*
* inspired by Microsoft DDSTextureLoader : 
*/


struct DDS_PIXELFORMAT
{
	uint32_t    size;
	uint32_t    flags;
	uint32_t    fourCC;
	uint32_t    RGBBitCount;
	uint32_t    RBitMask;
	uint32_t    GBitMask;
	uint32_t    BBitMask;
	uint32_t    ABitMask;
};

#define DDS_FOURCC      0x00000004  // DDPF_FOURCC
#define DDS_RGB         0x00000040  // DDPF_RGB
#define DDS_RGBA        0x00000041  // DDPF_RGB | DDPF_ALPHAPIXELS
#define DDS_LUMINANCE   0x00020000  // DDPF_LUMINANCE
#define DDS_LUMINANCEA  0x00020001  // DDPF_LUMINANCE | DDPF_ALPHAPIXELS
#define DDS_ALPHA       0x00000002  // DDPF_ALPHA
#define DDS_PAL8        0x00000020  // DDPF_PALETTEINDEXED8
#define DDS_BUMPDUDV    0x00080000  // DDPF_BUMPDUDV


struct DDS_HEADER
{
	uint32_t        size;
	uint32_t        flags;
	uint32_t        height;
	uint32_t        width;
	uint32_t        pitchOrLinearSize;
	uint32_t        depth; // only if DDS_HEADER_FLAGS_VOLUME is set in flags
	uint32_t        mipMapCount;
	uint32_t        reserved1[11];
	DDS_PIXELFORMAT ddspf;
	uint32_t        caps;
	uint32_t        caps2;
	uint32_t        caps3;
	uint32_t        caps4;
	uint32_t        reserved2;
};


class DDSTextureLoader : public Singleton<DDSTextureLoader>
{
	friend class Singleton<DDSTextureLoader>;


public:

	/*
	* Create a new Texture and Return it
	*/
	Texture2D* CreateTexture( RhiGraphicDevice* a_device , DDS_HEADER* a_header , void* a_datas );


private:

	RhiTextureFormat GetFormat( DDS_PIXELFORMAT a_format );
};

#endif // !__DDS_TEXTURE_LOADER_H__
