#ifndef __GRAPHICS_IMPORTERS_DDS_FILE_H__
#define __GRAPHICS_IMPORTERS_DDS_FILE_H__

#include "Core/CoreIncludes.h"
#include "../../Resources/Textures/Includes.h"



struct DDSHeaderPixelFormat
{
	TUint32    size;
	TUint32    flags;
	TUint32    fourCC;
	TUint32    RGBBitCount;
	TUint32    RBitMask;
	TUint32    GBitMask;
	TUint32    BBitMask;
	TUint32    ABitMask;
};

struct DDSHeader
{
	TUint32					size;
	TUint32					flags;
	TUint32					height;
	TUint32					width;
	TUint32					pitchOrLinearSize;
	TUint32					depth; // only if DDS_HEADER_FLAGS_VOLUME is set in flags
	TUint32					mipMapCount;
	TUint32					reserved1[11];
	DDSHeaderPixelFormat	ddspf;
	TUint32					caps;
	TUint32					caps2;
	TUint32					caps3;
	TUint32					caps4;
	TUint32					reserved2;
};


enum DDSFlags
{
	DDS_FLAGS_Caps			= 0x00000001,
	DDS_FLAGS_Height		= 0x00000002,
	DDS_FLAGS_Width			= 0x00000004,
	DDS_FLAGS_PixelFormat	= 0x00001000
};


class DDSHeaderHelper
{

public:

	DDSHeaderHelper( );
	~DDSHeaderHelper();

	/*
	* Get Width property
	*/
	TUint32 GetWidth( )const;

	/*
	* Get Height property
	*/
	TUint32 GetHeight( )const;

	/*
	* Ge the Format to use
	*/
	RhiTextureFormat GetTextureFormat( )const;

	/*
	* Get the numer of MipMap
	*/
	TUint32 GetMipMapCount()const;

	/*
	*
	*/
	TBool Init( const TUint8* a_buffer , TUint32 a_size );

	/*
	* Is it a valid DDS file?
	*/
	TBool IsValid( )const;

	/*
	* Get the Start Address of the data
	*/
	const TUint8* GetDataStartPointer( );


private:

	/*
	* Cehck the file contains the DDS chunck
	*/
	TBool CheckFileChunk( const TUint8* a_buffer )const;

	TBool ValidateHeader( const DDSHeader* a_header );



	size_t ComputeTextureSize( TUint32 a_width , TUint32 a_height , RhiTextureFormat a_format , TUint32 a_mipmapCount );
	size_t ComputeTextureMipMapSize( TUint32 a_width , TUint32 a_height , RhiTextureFormat a_format , TUint32 a_mipmapIndex );


// Fields
private:


	//pointer to the portion of the buffer storing the Header
	const DDSHeader*	m_header;
};

#endif