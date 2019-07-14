#include "Asset.h"

#ifdef _DEBUG
#include "Asset.inl"
#endif

//------------------------------------------------------------------------------------
Asset::Asset() : ReferenceCounted(false)
{
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void Asset::Load( const std::string& a_filePath )
{
	// Save the File Path
	m_filePath													=	a_filePath;

	// Load the Json File
	JSonReader t_reader;
	t_reader.Load( a_filePath );

	LoadFromJSon( t_reader.GetRootNode() );
}
//------------------------------------------------------------------------------------
