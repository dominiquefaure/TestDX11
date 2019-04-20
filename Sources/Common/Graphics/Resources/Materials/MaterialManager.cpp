
#include "MaterialManager.h"

//------------------------------------------------------------------------------------
MaterialManager::MaterialManager()
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
MaterialManager::~MaterialManager()
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
MaterialRef MaterialManager::GetMaterial( const char* a_filePath )
{

	return LoadMaterial( a_filePath );
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
MaterialRef MaterialManager::LoadMaterial( const char* a_filePath )
{
	// Load a new material
	Material* t_newMaterial									=	new Material();
	t_newMaterial->Load( a_filePath );

	m_materialList.Add( t_newMaterial );

	return t_newMaterial;
}
//------------------------------------------------------------------------------------
