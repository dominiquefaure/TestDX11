#include "DDSHeaderHelper.h"

#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)\
	((uint32)(uint8)(ch0) | ((uint32)(uint8)(ch1) << 8) |\
	((uint32)(uint8)(ch2) << 16) | ((uint32)(uint8)(ch3) << 24 ))
#endif

enum DDSPixelFormat
{
	DDSPF_FourCC		= 0x00000004,
	DDSPF_RGB			= 0x00000040,
	DDSPF_DXT1			= MAKEFOURCC('D','X','T','1'),
	DDSPF_DXT3			= MAKEFOURCC('D','X','T','3'),
	DDSPF_DXT5			= MAKEFOURCC('D','X','T','5')
};


//------------------------------------------------------------------------------------
DDSHeaderHelper::DDSHeaderHelper( )
{
	m_header												=	nullptr;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
DDSHeaderHelper::~DDSHeaderHelper( )
{
	m_header												=	nullptr;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
TUint32 DDSHeaderHelper::GetWidth( )const
{
	assert( m_header != nullptr );
	return m_header->width;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
TUint32 DDSHeaderHelper::GetHeight( )const
{
	assert( m_header != nullptr );
	return m_header->height;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
RhiTextureFormat DDSHeaderHelper::GetTextureFormat( )const
{
	assert( m_header != nullptr );

	RhiTextureFormat t_format								=	TEXTURE_FORMAT_UNKNOWN;

	if((m_header->ddspf.flags & DDSPF_RGB) != 0 &&
		m_header->ddspf.RGBBitCount == 32 &&
		m_header->ddspf.RBitMask == 0x00ff0000 &&
		m_header->ddspf.GBitMask == 0x0000ff00 &&
		m_header->ddspf.ABitMask == 0x000000ff)
	{
		t_format											=	TEXTURE_FORMAT_B8G8R8A8;
	}

	if( ( m_header->ddspf.flags & DDSPF_FourCC) != 0 )
	{
		if( m_header->ddspf.fourCC == DDSPF_DXT1 )
		{
			t_format										=	TEXTURE_FORMAT_DXT1;
		}
		else if( m_header->ddspf.fourCC == DDSPF_DXT3 )
		{
			t_format										=	TEXTURE_FORMAT_DXT3;
		}
		else if( m_header->ddspf.fourCC == DDSPF_DXT5 )
		{
			t_format										=	TEXTURE_FORMAT_DXT5;
		}
		else if( m_header->ddspf.fourCC == MAKEFOURCC('A','T','I','2') ||
			m_header->ddspf.fourCC == MAKEFOURCC('B','C','5','S') )
		{
			t_format										=	TEXTURE_FORMAT_BC5;
		}
		else if( m_header->ddspf.fourCC == MAKEFOURCC('B','C','4','U') ||
			m_header->ddspf.fourCC == MAKEFOURCC('B','C','4','S') )
		{
			t_format										=	TEXTURE_FORMAT_BC5;
		}
		else if( m_header->ddspf.fourCC == 0x71 )
		{
			t_format										=	TEXTURE_FORMAT_FLOAT_RGBA;
		}

	}
	return t_format;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
TUint32 DDSHeaderHelper::GetMipMapCount()const
{
	assert( m_header != nullptr );

	if( m_header->mipMapCount > 0 )
	{
		return m_header->mipMapCount;
	}

	return 1;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
TBool DDSHeaderHelper::Init( const TUint8* a_buffer , TUint32 a_size )
{
	// check the file have DDS chuck and the size is greater than the header size
	if( ( a_size >= sizeof(DDSHeader) + 4 ) && CheckFileChunk( a_buffer ) )
	{
		const DDSHeader* t_header							=	(DDSHeader*)( a_buffer + 4 );

		if( ValidateHeader( t_header ) )
		{
			m_header										=	t_header;
		}
	}

	return IsValid();
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
TBool DDSHeaderHelper::IsValid( )const
{
	return ( m_header != nullptr );
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
TBool DDSHeaderHelper::CheckFileChunk( const TUint8* a_buffer )const
{
	return ( a_buffer[0]=='D' && a_buffer[1]=='D' && a_buffer[2]=='S' && a_buffer[3]==' ' );
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
TBool DDSHeaderHelper::ValidateHeader( const DDSHeader* a_header )
{
	if( a_header->size != sizeof( DDSHeader) )
	{
		return false;
	}

	if( a_header->ddspf.size != sizeof( DDSHeaderPixelFormat ) )
	{
		return false;
	}

	TUint32 t_requiredFlags									=	DDS_FLAGS_Caps | DDS_FLAGS_Height | DDS_FLAGS_Width | DDS_FLAGS_PixelFormat;


	if( ( a_header->flags & t_requiredFlags ) != t_requiredFlags )
	{
		return false;
	}

	return true;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
const TUint8* DDSHeaderHelper::GetDataStartPointer( )
{
	const TUint8* t_ptr = (const TUint8*)m_header + sizeof(DDSHeader);

	return t_ptr;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
size_t DDSHeaderHelper::ComputeTextureSize( TUint32 a_width , TUint32 a_height , RhiTextureFormat a_format , TUint32 a_mipmapCount )
{
	size_t t_size											=	0;
	for( int  i = 0; i < a_mipmapCount; i ++ )
	{
		t_size												+=	ComputeTextureMipMapSize( a_width , a_height , a_format , i );
	}

	return t_size;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
size_t DDSHeaderHelper::ComputeTextureMipMapSize( TUint32 a_width , TUint32 a_height , RhiTextureFormat a_format , TUint32 a_mipmapIndex )
{
	return 0;
}
//------------------------------------------------------------------------------------

