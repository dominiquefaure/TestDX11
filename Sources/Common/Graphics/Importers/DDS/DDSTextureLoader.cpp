
#include "DDSTextureLoader.h"

#include "DDSHeaderHelper.h"

//-----------------------------------------------------------------------------------------------
Texture2D* DDSTextureLoader::CreateTexture( RhiGraphicDevice* a_device , void* a_datas , TUint32 a_length )
{
	Texture2D* t_texture									=	NULL;

	//use the helper to check if everything is ok
	DDSHeaderHelper t_helper;
	if( t_helper.Init( (TUint8*)a_datas , a_length) )
	{
		RhiTextureDescriptor t_desc;

		t_desc.m_width										=	t_helper.GetWidth();
		t_desc.m_height										=	t_helper.GetHeight();
		t_desc.m_format										=	t_helper.GetTextureFormat();
		t_desc.m_mipmapCount								=	t_helper.GetMipMapCount();
		t_desc.m_usage										=	RHI_BUFFER_USAGE_IMMUTABLE;
		t_desc.m_shaderUsage								=	SHADER_USAGE_RESOURCE_READ;

		t_texture											=	new Texture2D();
		t_texture->Init( t_desc , t_helper.GetDataStartPointer() );
	}

	return t_texture;
}
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
Texture2D* DDSTextureLoader::CreateTexture( RhiGraphicDevice* a_device ,  const std::string& a_path )
{
	Texture2D* t_texture									=	NULL;

	// Load the File content
	FileHandle* t_handle									=	FileSystem::GetInstance()->OpenRead( a_path );

	// fit eh file is found
	if(t_handle != nullptr )
	{
		int t_size											=	t_handle->GetSize();
		char* t_buffer										=	new char[ t_size ];
		int t_readCount										=	t_handle->Read( t_buffer , t_size );

		t_handle->Close();

		// create the Texture
		t_texture											=	CreateTexture( a_device , t_buffer , t_readCount );

		// free the Buffer
		delete[] t_buffer;
	}

	return t_texture;
}
//-----------------------------------------------------------------------------------------------

/*
//-----------------------------------------------------------------------------------------------
RhiTextureFormat DDSTextureLoader::GetFormat( DDS_PIXELFORMAT ddpf )
{
	#define ISBITMASK( r,g,b,a ) ( ddpf.RBitMask == r && ddpf.GBitMask == g && ddpf.BBitMask == b && ddpf.ABitMask == a )

    if (ddpf.flags & DDS_RGB)
    {
        switch( ddpf.RGBBitCount )
        {
			case 32:
				if (ISBITMASK(0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000))
				{
					return TEXTURE_FORMAT_R8G8B8A8;
				}

			break;
		}
	}
    else if (ddpf.flags & DDS_FOURCC)
    {
        if (MAKEFOURCC('D', 'X', 'T', '1') == ddpf.fourCC)
        {
            return TEXTURE_FORMAT_DXT1;
        }
        if (MAKEFOURCC('D', 'X', 'T', '3') == ddpf.fourCC)
        {
            return TEXTURE_FORMAT_DXT3;
        }
        if (MAKEFOURCC('D', 'X', 'T', '5') == ddpf.fourCC)
        {
            return TEXTURE_FORMAT_DXT5;
        }
	}
	


	return TEXTURE_FORMAT_UNKNOWN;
}
//-----------------------------------------------------------------------------------------------

/*
//-----------------------------------------------------------------------------------------------
TextureFormat GetFormat( DDS_PIXELFORMAT ddpf )
{
	#define ISBITMASK( r,g,b,a ) ( ddpf.RBitMask == r && ddpf.GBitMask == g && ddpf.BBitMask == b && ddpf.ABitMask == a )

    if (ddpf.flags & DDS_RGB)
    {
        // Note that sRGB formats are written using the "DX10" extended header

        switch( ddpf.RGBBitCount )
        {
        case 32:
            if (ISBITMASK(0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000))
            {
                return TEXTURE_FORMAT_R8G8B8A8_UNORM;
            }

            if (ISBITMASK(0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000))
            {
                return TEXTURE_FORMAT_B8G8R8A8_UNORM;
            }

            if (ISBITMASK(0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000))
            {
                return TEXTURE_FORMAT_B8G8R8X8_UNORM;
            }

            // No DXGI format maps to ISBITMASK(0x000000ff,0x0000ff00,0x00ff0000,0x00000000) aka D3DFMT_X8B8G8R8

            // Note that many common DDS reader/writers (including D3DX) swap the
            // the RED/BLUE masks for 10:10:10:2 formats. We assume
            // below that the 'backwards' header mask is being used since it is most
            // likely written by D3DX. The more robust solution is to use the 'DX10'
            // header extension and specify the DXGI_FORMAT_R10G10B10A2_UNORM format directly

            // For 'correct' writers, this should be 0x000003ff,0x000ffc00,0x3ff00000 for RGB data
            if (ISBITMASK(0x3ff00000, 0x000ffc00, 0x000003ff, 0xc0000000))
            {
                return TEXTURE_FORMAT_R10G10B10A2_UNORM;
            }

            // No DXGI format maps to ISBITMASK(0x000003ff,0x000ffc00,0x3ff00000,0xc0000000) aka D3DFMT_A2R10G10B10

            if (ISBITMASK(0x0000ffff, 0xffff0000, 0x00000000, 0x00000000))
            {
                return TEXTURE_FORMAT_R16G16_UNORM;
            }

            if (ISBITMASK(0xffffffff, 0x00000000, 0x00000000, 0x00000000))
            {
                // Only 32-bit color channel format in D3D9 was R32F
                return TEXTURE_FORMAT_R32_FLOAT; // D3DX writes this out as a FourCC of 114
            }
            break;



        case 16:
            if (ISBITMASK(0x7c00, 0x03e0, 0x001f, 0x8000))
            {
                return TEXTURE_FORMAT_B5G5R5A1_UNORM;
            }
            if (ISBITMASK(0xf800, 0x07e0, 0x001f, 0x0000))
            {
                return TEXTURE_FORMAT_B5G6R5_UNORM;
            }

            // No DXGI format maps to ISBITMASK(0x7c00,0x03e0,0x001f,0x0000) aka D3DFMT_X1R5G5B5

            if (ISBITMASK(0x0f00, 0x00f0, 0x000f, 0xf000))
            {
                return TEXTURE_FORMAT_B4G4R4A4_UNORM;
            }

            // No DXGI format maps to ISBITMASK(0x0f00,0x00f0,0x000f,0x0000) aka D3DFMT_X4R4G4B4

            // No 3:3:2, 3:3:2:8, or paletted DXGI formats aka D3DFMT_A8R3G3B2, D3DFMT_R3G3B2, D3DFMT_P8, D3DFMT_A8P8, etc.
            break;
        }
    }


    return TEXTURE_FORMAT_UNKNOWN;

}
//-----------------------------------------------------------------------------------------------
*/