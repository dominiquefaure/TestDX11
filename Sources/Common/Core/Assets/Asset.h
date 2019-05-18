#ifndef __CORE_ASSETS_IASSET_H__
#define __CORE_ASSETS_IASSET_H__

#include "Core/CoreMacros.h"
#include "Core/Base/Includes.h"
#include "Core//IO/Includes.h"

/*
* Base class for all assets
*/
class Asset : public ReferenceCounted
{

public:

	FORCE_INLINE const std::string& GetFilePath()const;

	/*
	* Load the Asset definition from a JSON File
	*/
	void Load( const std::string& a_filePath );


protected:

	virtual void LoadFromJSon( const JSonNode* a_rootNode ){}

private:

	std::string	m_filePath;

};

// The inline is included in the Header only if not in debug mode
#ifndef _DEBUG
#include "Asset.inl"
#endif



#endif