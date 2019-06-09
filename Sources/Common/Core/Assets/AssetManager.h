#ifndef __CORE_ASSETS_MANAGER_H__
#define __CORE_ASSETS_MANAGER_H__

#include "Core/CoreMacros.h"
#include "Core/Base/Includes.h"
#include "Core/DesignPatterns/Singleton.h"

#include "Asset.h"

class AssetManager : public Singleton<AssetManager>
{


public:

	/*
	* Get an asset , load it if needed
	*/
	//AssetRef GetAsset( const std::string& a_filePath );
	template<class T> static ReferenceCountedPtr<T> GetAsset( const std::string& a_filePath )
	{
		return LoadAsset<T>( a_filePath );
	}

private:

	/*
	* Load an Asset
	*/
	//AssetRef LoadAsset( const std::string& a_filePath );

	template<class T> static ReferenceCountedPtr<T> LoadAsset( const std::string& a_filePath )
	{
		T* t_asset	=	new T();
		t_asset->Load( a_filePath );

		return t_asset;
	}
};

#endif