#ifndef __CORE_IO_JSON_READER_H__
#define __CORE_IO_JSON_READER_H__

#include "../../../Core/Base/Includes.h"

class JSonNode;

class JSonReader
{
public:
	JSonReader();
	~JSonReader();

	/*
	* Get the root node of the JSon document loaded
	*/
	const JSonNode* GetRootNode();

	/*
	* Load a Json file
	*/
	void Load( const std::string& a_filePath );

private:

	JSonNode*	m_rootNode;
};

#endif