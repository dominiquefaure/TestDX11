#ifndef __CORE_ASSETS_MANAGER_H__
#define __CORE_ASSETS_MANAGER_H__

#include "Core/CoreMacros.h"
#include "Core/Base/Includes.h"
#include "Core/DesignPatterns/Singleton.h"

#include "Asset.h"
#include "AssetRegistry.h"


class AssetManager : public Singleton<AssetManager>
{


public:

	/*
	* Get an asset , load it if needed
	*/
	//AssetRef GetAsset( const std::string& a_filePath );
	template<class T> ReferenceCountedPtr<T> GetAsset( const std::string& a_filePath )
	{
		
		// Check if the asset is already present in the registry
		Asset* t_asset										=	Find( a_filePath );
		// if found return it
		if( t_asset )
		{
			return (T*)( t_asset );
		}

		return LoadAsset<T>( a_filePath );
	}

private:

	/*
	* Load an Asset
	*/
	template<class T> ReferenceCountedPtr<T> LoadAsset( const std::string& a_filePath )
	{
		T* t_asset	=	new T();
		t_asset->Load( a_filePath );

		return t_asset;
	}

// Methods
private:

	/*
	* Internal Method to get an asset
	*/
	Asset* Find( const std::string& a_filePath );


// Fields
private:

	// store al the Assets already loaded
	AssetRegistry	m_assetRegistry;

};

#endif