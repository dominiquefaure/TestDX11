#ifndef __CORE_ASSET_REGISTRY_H__
#define __CORE_ASSET_REGISTRY_H__

#include "Core/Base/Includes.h"
#include "Core/Containers/TArray.h"

#include "Asset.h"

/*
* Register a Collection of Assets
*/
class AssetRegistry
{
public:

	AssetRegistry();
	~AssetRegistry();

	/*
	* Add an Asset to the Registery
	*/
	void Add( Asset* a_asset );

	/*
	* Remove the Given Asset from the Registery
	*/
	void Remove( Asset* a_asset );

	/*
	* Remove the Given Asset from the Registery
	*/
	void Remove( const std::string& a_filePath );

	/*
	* Try to get the Asset with the Given name
	*/
	Asset* Get( const std::string& a_filePath );

private:

	/*
	* Index of the Asset with the Given Path
	*/
	TUint32 IndexOf( const std::string& a_filePath  );


private:

	TArray<Asset*>	m_assetList;

};

#endif