#include "AssetRegistry.h"


//------------------------------------------------------------------------------------
AssetRegistry::AssetRegistry()
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
AssetRegistry::~AssetRegistry()
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void AssetRegistry::Add( Asset* a_asset )
{
	m_assetList.Add( a_asset );
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void AssetRegistry::Remove( Asset* a_asset )
{
	m_assetList.Remove( a_asset );
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void AssetRegistry::Remove( const std::string& a_filePath )
{
	TUint32 t_index											=	IndexOf( a_filePath );
	if( t_index != -1 )
	{
		m_assetList.RemoveAt( t_index );
	}
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
Asset* AssetRegistry::Get( const std::string& a_filePath )
{
	Asset* t_asset;

	TUint32 t_count											=	m_assetList.Count();
	for( TUint32 i = 0 ; i < t_count ; i ++ )
	{
		t_asset												=	m_assetList[ i ];
		if( t_asset->GetFilePath() == a_filePath )
		{
			return t_asset;
		}
	}

	return nullptr;
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
TUint32 AssetRegistry::IndexOf( const std::string& a_filePath  )
{
	Asset* t_asset;
	TUint32 t_count											=	m_assetList.Count();

	for( TUint32 i = 0 ; i < t_count ; i ++ )
	{
		t_asset												=	m_assetList[ i ];
		if( t_asset->GetFilePath() == a_filePath )
		{
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------------------------
