#ifndef __CORE_IO_JSON_DOCUMENT_H__
#define __CORE_IO_JSON_DOCUMENT_H__

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "JsonNode.h"

using namespace rapidjson;


class JsonDocument
{

public:

	/*
	* Default Constructor
	*/
	JsonDocument();

	/*
	* Destructor
	*/
	~JsonDocument();


	inline JSonNode& GetRootNode()
	{
		return m_rootNode;
	}

	/*
	* Load the Json Document
	*/
	void Load( const std::string& a_filePath );


private:

	Document	m_jsonDocument;

	JSonNode	m_rootNode;
};




#endif