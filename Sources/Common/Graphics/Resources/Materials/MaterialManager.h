#ifndef __RENDERER_MATERIAL_MANAGER_H__
#define __RENDERER_MATERIAL_MANAGER_H__

#include "Core/CoreIncludes.h"
#include "Material.h"


class MaterialManager
{



public:

	MaterialManager();
	~MaterialManager();

	/*
	* Get the Material with the given file path.
	* Load it if necessary
	*/
	MaterialRef GetMaterial( const char* a_filePath );


private:

	/*
	* Load a new Material
	*/
	MaterialRef LoadMaterial( const char* a_filePath );


private:

	TArray<Material*>	m_materialList;
};

#endif