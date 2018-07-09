#ifndef __CORE_IO_JSON_NODE_ARRAY_PROPERTY_H__
#define __CORE_IO_JSON_NODE_ARRAY_PROPERTY_H__

#include "AJSonProperty.h"
#include "../../../Core/Base/BaseDataTypes.h"

class JSonNode;

class JSonNodeArrayProperty : public AJsonProperty
{
	friend class JSonNode;

public:

	JSonNodeArrayProperty();
	virtual ~JSonNodeArrayProperty();

	/*
	* Get the number of Elements
	*/
	TUint32 GetCount()const;

	/*
	* Get the node present at the given index
	*/
	const JSonNode* GetNodeAt( TUint32 a_index )const;

	/*
	* Add a new node and return pointer to it
	*/
	JSonNode* AddNode();

protected:



	/*
	* Serialize the Property value
	*/
	virtual void SerializeValue( rapidjson::PrettyWriter<rapidjson::StringBuffer> & a_writer );

private:

	std::vector<JSonNode*>	m_subNodes;

};
#endif