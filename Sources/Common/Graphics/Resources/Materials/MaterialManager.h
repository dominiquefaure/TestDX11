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
	* Get the MaterialTemplate with the given file path.
	* Load it if necessary
	*/
//	MaterialTemplateRef GetTemplate( const std::string& a_filePath );

	/*
	* Get the Material with the given file path.
	* Load it if necessary
	*/
	MaterialRef GetMaterial( const char* a_filePath );


private:

	/*
	* Load a MaterialTemplate from file
	*/
//	MaterialTemplate LoadMaterialTemplate( const std::string& a_filePath );

	/*
	* Load a new Material
	*/
	MaterialRef LoadMaterial( const char* a_filePath );


private:

//	TArray<MaterialTemplate*>	m_materialTemplateList;
	TArray<Material*>			m_materialList;
};

#endif