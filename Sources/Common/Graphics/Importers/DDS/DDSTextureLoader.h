#ifndef __GRAPHICS_RESOURCES_DDS_TEXTURE_LOADER_H__
#define __GRAPHICS_RESOURCES_DDS_TEXTURE_LOADER_H__


#include "Core/CoreIncludes.h"
#include "Graphics/RHI/Includes.h"

#include "../../Resources/Textures/Includes.h"



class DDSTextureLoader : public Singleton<DDSTextureLoader>
{
	friend class Singleton<DDSTextureLoader>;


public:

	/*
	* Create a new Texture from a Buffer and Return it
	*/
	static Texture2D* CreateTexture( RhiGraphicDevice* a_device , void* a_datas , TUint32 a_length );

	/*
	* Load a Texture from File
	*/
	static Texture2D* CreateTexture( RhiGraphicDevice* a_device , const std::string& a_path );

private:

};

#endif // !__DDS_TEXTURE_LOADER_H__
